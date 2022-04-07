/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 14:10:46 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/04/07 10:56:23 by ted-dafi         ###   ########.fr       */
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

int	main(int ac, char **av, char **envp)
{
	t_data	data;

	if (ac != 5)
		return (write(2, "usage: ./pipex file1 command1 command2 file2\n", 46));
	ft_init(ac, &data, O_TRUNC);
	multiprocessing(&data, ac, av, envp);
}
