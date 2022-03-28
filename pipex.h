/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 18:24:15 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/02/21 10:10:05 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>

typedef struct s_data
{
	int	**pipes;
	int	*proc;
}	t_data;

char	*what_valid(char **all, char *command);
void	ft_close(int a, int b, int c);
char	*ft_strnstr(char *haystack, char *needle, size_t len);
void	*ft_calloc(size_t count, size_t size);
char	*get_path(char	*s, char **envp);
char	**ft_split(char *s, char c);
size_t	ft_strlcpy(char *dest, char *src, size_t size);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strlen(char *s);
void	ft_dup2(int f1, int f2);
void	nocommand(void);
void	dealwithit(char **av, char **envp, int flag, int *p);
void	init(t_data	*vars, int	num);
#endif