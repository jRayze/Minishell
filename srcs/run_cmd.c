/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamerlin <jamerlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 11:38:35 by jamerlin          #+#    #+#             */
/*   Updated: 2017/10/26 11:39:14 by jamerlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_cmd(char *path, char **args, char **newenv)
{
	pid_t	pid;
	int		cmd_status;

	cmd_status = 0;
	signal(SIGINT, handle_signal);
	pid = fork();
	if (pid == 0)
		execve(path, args, newenv);
	if (pid > 0)
		wait(&cmd_status);
	ft_memdel((void **)&path);
	return (1);
}
