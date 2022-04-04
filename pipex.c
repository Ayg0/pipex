/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 14:10:46 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/04/04 13:03:23 by ted-dafi         ###   ########.fr       */
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

char	*ft_strjoin2(char *s1, char *s2, int flag)
{
	char		*s3;
	size_t		i;
	size_t		j;

	if (!s1)
		return (ft_strdup(s2));
	i = 0;
	j = 0;
	s3 = (char *)ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	if (!s3)
		return (NULL);
	while (s1[i])
		s3[j++] = s1[i++];
	i = 0;
	flag && my_free(&s1, NULL, 0);
	while (s2[i])
		s3[j++] = s2[i++];
	return (s3);
}

void	dealwithit(char **av, char **envp, int fd, int *p)
{
	char		*excutable;
	char		**parts;

	if (fd > 0)
	{
		ft_dup2(fd, p[1]);
		ft_close(fd, p[1], p[0]);
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
		fd = open(av[4], 1 | O_CREAT | O_TRUNC, 0644);
		ft_dup2(p[0], fd);
		ft_close(fd, p[0], p[1]);
		execve(excutable, parts, envp);
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
			return (write(2, "Error, No such a file or directory\n", 36));
		dealwithit(av, envp, fd, p);
	}
	proc[1] = fork();
	if (proc[1] == -1)
		return (write(2, "Error, couldn't create the proccess\n", 37));
	if (proc[1] == 0)
		dealwithit(av, envp, -1, p);
	wait(NULL);
	return (0);
}

// int	main(int ac, char **av, char **envp)
// {
// 	return (mandatory(ac, av, envp));
// }
