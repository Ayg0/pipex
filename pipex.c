/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 14:10:46 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/02/16 19:50:03 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strnstr(char *haystack, char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!haystack)
		return (NULL);
	while (haystack[i])
	{
		j = 0;
		while (haystack[i + j] == needle[j] && j + i < len)
		{
			if (needle[j + 1] == '\0')
				return ((char *)(haystack + i));
			j++;
		}
		i++;
	}
	return (0);
}

char	*get_path(char	*s, char **envp)
{
	char	*d;
	char	**wt;

	while (*envp)
	{
		if (ft_strnstr(*envp, "PATH=", 5))
			break ;
		envp++;
	}
	wt = ft_split(*envp, ':');
	d = what_valid(wt, s);
	return (d);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char		*s3;
	size_t		i;
	size_t		j;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	j = 0;
	s3 = (char *)ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	if (!s3)
		return (NULL);
	while (s1[i])
		s3[j++] = s1[i++];
	i = 0;
	while (s2[i])
		s3[j++] = s2[i++];
	return (s3);
}

void	get_and_do(char *command, char **envp)
{
	char	**parts;
	char	*excutable;

	parts = ft_split(command, ' ');
	excutable = get_path(parts[0], envp);
	if (!excutable)
	{
		write(2,"Command not found",18);
		exit(0);
	}
	execve(excutable, parts, envp);
}
void	nocommand(void)
{
	write(2,"Command not found\n",19);
	exit(0);
}

void	dealwithit(char **av, char **envp, int flag, int *p)
{
	char		*excutable;
	char		**parts;

	if (flag > 0)
	{
		ft_dup2(flag, p[1]);
		ft_close(flag, p[1], p[0]);
		parts = ft_split(av[2], ' ');
		excutable = get_path(parts[0], envp);
		if (!excutable)
			nocommand();
		execve(excutable, parts, envp);
	}
	else
	{
		parts = ft_split(av[3], ' ');
		excutable = get_path(parts[0], envp);
		if (!excutable)
			nocommand();
		flag = open(av[4], 1 | O_CREAT | O_TRUNC, 0777);
		ft_dup2(p[0], flag);
		ft_close(flag, p[0], p[1]);
		execve(excutable, parts, envp);
	}
}

int	main(int ac, char **av, char **envp)
{
	int	p[2];
	int	proc[2];
	int	fd;

	if (ac != 5)
		return (write(2, "Error, enter required elements only\n", 37));
	if (pipe(p) < 0)
		return (write(2, "Error, Pipes \?\?\n", 17));	
	proc[0] = fork();
	if(proc[0] == -1)
		return (write(2, "Error, couldn't create the proccess\n", 37));
	if (proc[0] == 0)
	{
		fd = open(av[1], 0);
		if (fd == -1)
			return (write(2, "Error, No such a file or directory\n",36));
		dealwithit(av, envp, fd, p);
	}
	proc[1] = fork();
	if(proc[1] == -1)
		return (write(2, "Error, couldn't create the proccess\n", 37));
	if (proc[1] == 0)
		dealwithit(av, envp, -1, p);
	wait(NULL);
}
