/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgauvrit <mgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 09:33:39 by abiddane          #+#    #+#             */
/*   Updated: 2023/05/31 02:45:52 by mgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_data_env(t_list *env, t_data *data, char **cmd, int toggle)
{
	(void)env;
	free_tab(data->av);
	if (toggle != 4)
		free_lst(env);
	if (toggle != 3)
		free(data->env);
	if (cmd)
		free_tab(cmd);
	if (toggle == 2 && data->path)
		free_tab(data->path);
	if (toggle == 4 || toggle == 2)
		free(data->here);
}

void	child_aux(t_list *env, t_data *data, char **cmd)
{
	ft_putstr_fd(cmd[0], STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	free(data->cmd);
	free_data_env(env, data, cmd, 2);
}

int	pipex_aux(t_data *data, char *read)
{
	if (count_quote(read, data) == -1 || !data->pid || !data->av)
	{
		if (data->av)
		{
			free_tab(data->av);
			if (data->pid)
				free(data->pid);
		}
		free(data->env);
		return (1);
	}
	return (0);
}

int	pipex_hd_aux(t_list *env, t_data *data)
{
	if (data->here_nb)
	{
		if (here_doc(env, data) || data->status == 130)
		{
			free(data->here);
			return (1);
		}
	}
	return (0);
}
