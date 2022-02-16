/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 14:10:46 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/02/16 13:51:00 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <errno.h>
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

int	main(int ac, char **av, char **envp)
{
	int		f1[2];
	int		i;
	int		k;
	int		fd;

	if (ac != 5)
		return (write(2, "error, enter required elements only", 36));
	if (pipe(f1) < 0)
		return (write(1, "error, pipes \?\?!", 17));
	i = fork();
	if (i == -1)
		return (write(2, "couldn't create proccess", 25));
	if (i == 0)
	{
		fd = open(av[1], 0);
		if (fd < 0)
			return (write(2, "error no such a file or directory\n", 35));
		ft_dup2(fd, f1[1]);
		ft_close(fd, f1[0], f1[1]);
		get_and_do(av[2], envp);
	}
	k = fork();
	if (k == 0)
	{
		fd = open(av[4], 1 | O_CREAT | O_TRUNC, 0777);
		ft_dup2(f1[0], fd);
		ft_close(fd, f1[0], f1[1]);
		get_and_do(av[3], envp);
	}
	wait(NULL);
}
