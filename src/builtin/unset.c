/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiddane <abiddane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 12:27:21 by abiddane          #+#    #+#             */
/*   Updated: 2023/06/02 13:37:56 by abiddane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_cmd(t_list *env, char **cmd, t_data *data)
{
	t_list	*tmp2;
	char	*name;
	int		i;

	i = 0;
	while (cmd[++i])
	{
		while (env->next)
		{
			name = get_var_name(env->next->var);
			if (!ft_strcmp(name, cmd[i]))
			{
				tmp2 = env->next->next;
				free(env->next->var);
				free(env->next);
				env->next = tmp2;
				free(name);
				break ;
			}
			free(name);
			env = env->next;
		}
	}
	data->status = 0;
}
