/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 00:31:23 by sydauria          #+#    #+#             */
/*   Updated: 2023/03/06 22:49:53 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execution(char **env, t_complete_command *elements)
{
	uint_8			ret;
	t_monitor		monitor;
	
	init_struct(envp, &monitor, &elements);
	if (elements->pipe_number)
		ret = forking(&elements, envp);
	else
		solo_cmd(&elements, envp);
	
	// free(elements.pid_register);
	// free_paths(elements.paths);
	// free_files(elements.files);
	// free_list(elements.first);
	return (ret);
}
