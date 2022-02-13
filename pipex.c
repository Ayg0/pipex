#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while(s[i])
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dest, char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size != 0)
	{
		while (i < size - 1 && src[i] != '\0')
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (ft_strlen(src));
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*b;
	int		i;

	i = count * size;
	b = malloc(i);
	if (b == 0)
		return (0);
	while (i)
		((char *)b)[--i] = 0;
	return (b);
}

static size_t	tha_nambar(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (!*s)
			break ;
		while (*s != c && *s)
			s++;
		i++;
	}
	return (i);
}

static char	*ft_look_for(const char *s, int c)
{
	while (*s)
	{
		if (*s == (unsigned char )c)
			return ((char *)s);
		s++;
	}
	return ((char *)s);
}

static void	why_r_ya_running(char **d, int i)
{
	while (i >= 0)
	{
		free(*d);
		d++;
		i--;
	}
	free(d);
}

static void	doo_it(char **da, char *from, char c)
{
	size_t	w;
	int		i;

	i = 0;
	while (*from)
	{
		while (*from == c)
			from++;
		if (*from)
		{
			w = (size_t)(ft_look_for(from, c) - (char *)from);
			*da = (char *)ft_calloc((w + 1), sizeof(char));
			if (!da)
			{
				why_r_ya_running(da, i);
				return ;
			}
			ft_strlcpy(*da, from, w + 1);
			da++;
			i++;
			from += w;
		}
	}
}


char	**ft_split(char *s, char c)
{
	char	**p;

	if (!s)
		return (NULL);
	p = (char **)ft_calloc((tha_nambar(s, c) + 1), sizeof(char *));
	if (!p)
		return (NULL);
	doo_it(p, s, c);
	return (p);
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

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!haystack)
		return (NULL);
	if (*needle == '\0')
		return ((char *)haystack);
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

char	*what_valid(char **all, char *command)
{
	char	*s;
	char	*temp;

	while(*all)
	{
		s = ft_strjoin(*all,"/");
		temp = s;
		s = ft_strjoin(s, command);
		free(temp);
		if (!access(s, X_OK))
			return (s);
		free(s);
		(*all)++;
	}
	return (NULL);
}

char	*get_it(char *command, char **envp)
{
	char	*s;
	char	**wt;
	while(*envp)
	{
		if (ft_strnstr(*envp, "PATH=", 5))
			break ;
		(*envp)++;
	}
	wt = ft_split(*envp, ':');
	s = what_valid(wt, command);
	free(wt);
	return (s);
}

void	ft_close(int a, int b, int c)
{
	close(a);
	close(b);
	close(c);
}

int	main(int ac, char **av, char **envp)
{
	int 	f1[2];
	int 	i;
	int 	k;
	int fd;
	char **command1;
	char *s;

	pipe(f1);
	i = fork();
	if (i == 0)
	{
		fd = open(av[1], 0);
		dup2(fd, 0);
		dup2(f1[1], 1);
		ft_close(fd, f1[0], f1[1]);
		command1 = ft_split(av[2], ' ');
		s = get_it(command1[0], envp);
		execve(s, command1, envp);
	}
	wait(NULL);
	fd = open(av[4], 1 | O_CREAT | O_TRUNC,0777);
	dup2(fd, 1);
	dup2(f1[0], 0);
	ft_close(fd, f1[0], f1[1]);
	command1 = ft_split(av[3], ' ');
	s = get_it(command1[0], envp);
	execve(s, command1, envp);
	// /usr/bin/bash
	// "bash", "-c", "grep :",NULL
	// printf("%d\n", f1[0]);
	// printf("%d\n", f1[1]);
}
