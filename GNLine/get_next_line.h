/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 20:31:20 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/04/01 18:55:51 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>
# include "../pipex.h"

char	*ft_strjoin(char **s1, char *s2);
int		ft_newlchr(const char *s);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strdup(char *s1);
char	*get_next_line(int fd, int size);
char	*my_free(char **buff, char **temp, int flag);
#endif
