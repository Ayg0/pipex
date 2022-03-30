/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 09:59:54 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/03/30 16:12:30 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_error(int errnum)
{
	exit(errnum);	
}

void	ft_init(int ac, t_data *data)
{
	int	i;

	i = 0;
	data->pipes = (int **)ft_calloc(ac - 2, sizeof(int *));
	data->proc = (int *)ft_calloc(ac - 2, sizeof(int));
	while (i < ac - 3)
	{
		data->pipes[i] = (int *)ft_calloc(2, sizeof(int));
		if (pipe(data->pipes[i++]) != 0)
			ft_error(1);
	}
	// khadmat lm3agiz open o clozi hna;
}

void	switch_in_out(int ac, int i, t_data *data, char **av)
{
	int fd;
	if (i == 0)
	{
		fd = open(av[1], 0);
		if (fd == -1)
			exit(write(2, "Error, No such a file or directory\n", 36));
		dup2(fd, 0);
		dup2(data->pipes[0][1], 1);
		close(data->pipes[0][0]);
	}
	else if (i == ac - 4)
	{
		fd = open(av[ac - 1], 1 | O_TRUNC | O_CREAT, 0644);
		if (fd == -1)
		{
			perror("khoxkhox");
			exit(0);
		}
		dup2(fd, 1);
 		dup2(data->pipes[i - 1][0], 0);
		close(data->pipes[i - 1][1]);
	}
	else
	{
		dup2(data->pipes[i - 1][0], 0);
		dup2(data->pipes[i][1], 1);
		close(data->pipes[i][0]);
		close(data->pipes[i - 1][1]);
	}
}

void	my_free(t_data *data, int ac)
{
	int i;

	i = 0;
	while (i < ac - 2)
		free(data->pipes[i++]);
	free(data->pipes);
	free(data->proc);
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;
	char	*excutable;
	char	**parts;
	int		i;
	int		j;

	i = 0;
	ft_init(ac, &data);
	while (i < ac - 3)
	{
		data.proc[i] = fork();
		if (!data.proc[i])
		{
			switch_in_out(ac, i, &data, av);
			parts = ft_split(av[i + 2], ' ');
			excutable = get_path(parts[0], envp);
			if (!excutable)
				nocommand();
			execve(excutable, parts, envp);
		}
		j = 0;
		while (j < i)
		{
			close(data.pipes[j][1]);
			close(data.pipes[j][0]);
			j++;
		}
		i++;
	}
	while (i > 0)
	{
		wait(NULL);
		i--;
	}
	my_free(&data, ac);
}

// ./pipex file1 cmd1 cmd2 file2