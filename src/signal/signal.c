/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiddane <abiddane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 10:50:29 by abiddane          #+#    #+#             */
/*   Updated: 2023/05/22 10:50:29 by abiddane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler_sig(int sig)
{
	t_data	*data;

	(void)sig;
	data = starton();
	write(2, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	data->status = 130;
}

void	handler_cmd(int sig)
{
	t_data	*data;

	(void)sig;
	data = starton();
	write(2, "\n", 1);
	data->status = 130;
}

void	handler_hd(int sig)
{
	t_data	*data;
	int		i;

	(void)sig;
	i = 0;
	data = starton();
	write(2, "\n", 1);
	while (i < data->here_nb)
	{
		safe_close(data->here[i].pipe[0]);
		safe_close(data->here[i].pipe[1]);
		free(data->here[i].delim);
		i++;
	}
	free_tab(data->av);
	free_tab(data->env);
	free(data->pid);
	free(data->here);
	exit(130);
}
