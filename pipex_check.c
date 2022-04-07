/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 16:11:06 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/04/07 11:25:56 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_dup2(int f1, int f2)
{
	dup2(f1, 0);
	dup2(f2, 1);
}

int	nocommand(void)
{
	exit(write(2, "Command not found\n", 19));
}

char	*what_valid(char **all, char *command)
{
	char	*s;

	if (!access(command, X_OK))
		return (command);
	while (*all)
	{
		s = ft_strjoin2(*all, "/", 1);
		s = ft_strjoin2(s, command, 1);
		if (!access(s, X_OK))
			return (s);
		all++;
	}
	return (NULL);
}

void	ft_close(int a, int b, int c)
{
	a > 0 && close(a);
	close(b);
	close(c);
}

char	*get_path(char	*s, char **envp)
{
	char	*d;
	char	**wt;

	if (!envp)
		exit(write(2, "Error: no env\n", 15));
	while (*envp)
	{
		if (ft_strnstr(*envp, "PATH=", 5))
			break ;
		envp++;
	}
	if (!envp)
		exit(write(2, "Error: what ?\n", 15));
	wt = ft_split(*envp, ':');
	d = what_valid(wt, s);
	free(wt);
	return (d);
}
