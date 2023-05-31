/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgauvrit <mgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 12:26:20 by abiddane          #+#    #+#             */
/*   Updated: 2023/05/30 18:07:03 by mgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd_cmd(t_data *data, int toggle)
{
	char	*buf;

	buf = (char *)malloc(BUFFER_SIZE);
	if (!buf)
		return ;
	if (getcwd(buf, BUFFER_SIZE) == NULL)
	{
		handle_perror("cd", data, buf, toggle);
		return ;
	}
	printf("%s\n", buf);
	free(buf);
	data->status = 0;
}
