/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 09:46:08 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/03/28 10:33:21 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_init(t_data *data, int ac)
{
	int	i;

	i = 0;
	data->proc = ft_calloc(     ac - 2, sizeof(int));
	data->pipes = ft_calloc(ac - 2, sizeof(int *));
	while (i < ac - 3)
	{
		data->pipes[i] = ft_calloc(2, sizeof(int));
		pipe(data->pipes[i++]);
	}
}

void	close_it(int fd, t_data *data, int ac)
{
	int	i;

	i = 0;
	while(i < ac - 3)
	{
		close(data->pipes[i][0]);
		close(data->pipes[i][1]);
		i++;
	}
	if (fd >= 0)
		close(fd);
}

void	in_out(int i, t_data *data, char **av, int ac)
{
	int	j;

	if (i == 0)
	{
		j = open(av[1], 0);
		if (j < 0)
			exit(write(2,"well, something is wrong.", 8));
		dup2(j, 0);
		dup2(data->pipes[i + 1][0], 1);
		
		//close_it(j, data, ac);
	}
	else
	{
		j = open(av[ac - 1], 1 | O_CREAT | O_TRUNC, 0644);
		if (j < 0)
			exit(write(2,"Well, something is wrong.", 8));
		dup2(j, 1);
		dup2(data->pipes[i][1], 0);
		//char b[1];
		//read(data->pipes[i][1], b, 1);
		//write(2, b, 1);
		//close_it(j, data, ac);
	}
}

int	main(int ac, char **av, char **envp)
{
	int	i;
	t_data	data;
	char		*excutable;
	char		**parts;

	i = 0;
}
