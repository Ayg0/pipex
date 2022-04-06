/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 09:59:54 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/04/05 14:52:30 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_it(t_data *data, int ac)
{
	int	i;

	i = 0;
	while (i < ac - 2)
		free(data->pipes[i++]);
	free(data->pipes);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void	get_data(char **av, int temp)
{
	char	*s;
	int		re;
	char	*i[3];

	re = 1;
	i[2] = ft_strjoin2(av[2], "\n", 0);
	while (re)
	{
		s = get_next_line(0, 7);
		re = ft_strcmp(s, i[2]);
		re && write(temp, s, ft_strlen(s));
		free(s);
	}
}

int	using_here_doc(int ac, char **av, char **envp)
{
	int		temp;
	t_data	all;

	temp = open(".hello_temp_herdoc", 1 | O_CREAT | O_TRUNC, 0644);
	get_data(av, temp);
	close(temp);
	av[2] = ft_strdup(".hello_temp_herdoc");
	ft_init(ac - 1, &all, O_APPEND);
	multiprocessing(&all, ac - 1, av + 1, envp);
	free(av[2]);
	unlink(".hello_temp_herdoc");
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_data	all_data;

	if (ac < 5)
		exit(77);
	ft_init(ac, &all_data, O_TRUNC);
	if (!ft_strcmp("here_doc", av[1]))
		using_here_doc(ac, av, envp);
	else
		multiprocessing(&all_data, ac, av, envp);
	return (0);
}
