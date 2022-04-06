/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 18:24:15 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/04/05 16:06:18 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "GNL/get_next_line.h"

typedef struct s_data
{
	int		**pipes;
	char	*excutable;
	char	**parts;
	int		mode;
}	t_data;

char	*what_valid(char **all, char *command);
void	ft_close(int a, int b, int c);
char	*ft_strnstr(char *haystack, char *needle, size_t len);
void	*ft_calloc(size_t count, size_t size);
char	*get_path(char	*s, char **envp);
char	**ft_split(char *s, char c);
size_t	ft_strlcpy(char *dest, char *src, size_t size);
char	*ft_strjoin2(char *s1, char *s2, int flag);
int		ft_strlen(char *s);
void	ft_dup2(int f1, int f2);
int		nocommand(void);
void	dealwithit(char **av, char **envp, int flag, int *p);
void	ft_init(int ac, t_data *data, int mode);
char	*ft_substr(char *s, unsigned int start, size_t len);
void	ft_error(int ac, t_data *data, int errnum, char *error);
void	switch_in_out(int ac, int i, t_data *data, char **av);
int		mandatory(int ac, char **av, char **envp);
void	multiprocessing(t_data *data, int ac, char **av, char **envp);
void	run_command(char **av, char **envp, int *pipe2, int *p);
void	free_it(t_data *data, int ac);
#endif