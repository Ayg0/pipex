/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 14:10:46 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/04/06 13:35:31 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	dealwithit(char **av, char **envp, int fd, int *p)
{
	t_data	all;

	if (fd > 0)
	{
		ft_dup2(fd, p[1]);
		ft_close(fd, p[1], p[0]);
		all.parts = ft_split(av[2], ' ');
		all.excutable = get_path(all.parts[0], envp);
		if (!all.excutable)
			nocommand();
		execve(all.excutable, all.parts, envp);
	}
	else
	{
		all.parts = ft_split(av[3], ' ');
		all.excutable = get_path(all.parts[0], envp);
		if (!all.excutable)
			nocommand();
		fd = open(av[4], 1 | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			exit(write(2, "Error: opening the file/permission\n", 36));
		ft_dup2(p[0], fd);
		ft_close(fd, p[0], p[1]);
		execve(all.excutable, all.parts, envp);
	}
}

void	wait_it(void)
{
	int	i;

	i = 0;
	while(i < 2)
	{
		wait(NULL);
		i++;
	}
}

int	mandatory(int ac, char **av, char **envp)
{
	int	p[2];
	int	proc[2];
	int	fd;

	if (ac != 5)
		return (write(2, "Error, enter required elements only\n", 37));
	if (pipe(p) < 0)
		return (write(2, "Error, Pipes \?\?\n", 17));
	proc[0] = fork();
	if (proc[0] == -1)
		return (write(2, "Error, couldn't create the proccess\n", 37));
	if (proc[0] == 0)
	{
		fd = open(av[1], 0);
		if (fd == -1)
			return (write(2, "Error, can't find file/permission\n", 35));
		dealwithit(av, envp, fd, p);
	}
	proc[1] = fork();
	if (proc[1] == -1)
		return (write(2, "Error, couldn't create the proccess\n", 37));
	if (proc[1] == 0)
		dealwithit(av, envp, -1, p);
	wait_it();
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	return (mandatory(ac, av, envp));
}
