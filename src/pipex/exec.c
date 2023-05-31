/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgauvrit <mgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 17:55:33 by abiddane          #+#    #+#             */
/*   Updated: 2023/05/31 03:12:55 by mgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_solo_built(t_list *env, t_data *data)
{
	char	**tab;
	int		fdin;
	int		fdout;

	fdin = dup(STDIN_FILENO);
	fdout = dup(STDOUT_FILENO);
	tab = start_cmd_tab(data, env, data->av[0], 1);
	exec_builtins(tab, data, env, 0);
	free_tab(tab);
	free(data->pid);
	free(data->env);
	free_tab(data->av);
	dup_n_close(fdin, STDIN_FILENO);
	dup_n_close(fdout, STDOUT_FILENO);
	return (0);
}

void	exec(t_list *env, t_data *data, int i)
{
	safe_piping(data->pipefd);
	data->pid[i] = fork();
	if (data->pid[i] == 0)
	{
		signal(SIGINT, &handler_cmd);
		child_process(data, env, i);
	}
	else if (data->pid[i] > 0)
	{
		signal(SIGINT, SIG_IGN);
		parent_process(data);
	}
}

int	is_a_built(t_list *env, t_data *data)
{
	char	**tab;
	int		ret;

	tab = start_cmd_tab(data, env, data->av[0], 0);
	ret = builtins_finder(tab);
	if (tab)
		free_tab(tab);
	return (ret);
}
