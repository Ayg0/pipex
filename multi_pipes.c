/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 13:15:26 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/04/07 11:29:19 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	multiprocessing(t_data *data, int ac, char **av, char **envp)
{
	int		i;
	int		j;

	i = -1;
	while (++i < ac - 3)
	{
		if (!fork())
		{
			switch_in_out(ac, i, data, av);
			data->parts = ft_split(av[i + 2], ' ');
			data->excutable = get_path(data->parts[0], envp);
			if (!data->excutable)
				nocommand();
			execve(data->excutable, data->parts, envp);
		}
		j = 0;
		while (j < i)
		{
			close(data->pipes[j][1]);
			close(data->pipes[j++][0]);
		}
	}
	while (i-- > 0)
		wait(NULL);
	free_it(data, ac);
}

void	ft_error(int ac, t_data *data, int errnum, char *error)
{
	if (error)
		write(2, error, ft_strlen(error));
	free_it(data, ac);
	exit(errnum);
}

void	switch_in_out(int ac, int i, t_data *data, char **av)
{
	int	fd;

	if (i == 0)
	{
		fd = open(av[1], 0);
		if (fd == -1)
			exit(write(2, "Error, No such a file or directory\n", 36));
		ft_dup2(fd, data->pipes[0][1]);
		close(data->pipes[0][0]);
	}
	else if (i == ac - 4)
	{
		fd = open(av[ac - 1], 1 | data->mode | O_CREAT, 0644);
		if (fd == -1)
			ft_error(ac, data, 7, "Error: opening the file/permission\n");
		ft_dup2(data->pipes[i - 1][0], fd);
		close(data->pipes[i - 1][1]);
	}
	else
	{
		ft_dup2(data->pipes[i - 1][0], data->pipes[i][1]);
		ft_close(-1, data->pipes[i][0], data->pipes[i - 1][1]);
	}
}

void	ft_init(int ac, t_data *data, int mode)
{
	int	i;

	i = 0;
	data->mode = mode;
	data->pipes = (int **)ft_calloc(ac - 2, sizeof(int *));
	while (i < ac - 3)
	{
		data->pipes[i] = (int *)ft_calloc(2, sizeof(int));
		if (pipe(data->pipes[i++]) != 0)
			ft_error(ac, data, 1, "error creating pipes ");
	}
}
