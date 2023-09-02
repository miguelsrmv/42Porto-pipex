/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 12:24:41 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/09/02 23:20:23 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	int	pipe_fd[2];
	int	pid;
	int	command_num;
	int	last_read_fd;

	usage_check(argc, argv);
	command_num = command_calc(argc, argv);
	last_read_fd = -1;
	while (command_num-- > 3)
	{
		if (pipe(pipe_fd) == -1)
			return (ERROR);
		pid = fork();
		if (pid == -1)
			return (ERROR);
		if (pid == 0)
			child_process_main(pipe_fd, last_read_fd,
				argv[argc - command_num], envp);
		else
			prepare_next_process(&last_read_fd, pipe_fd);
	}
	parent_process(pipe_fd, last_read_fd, argv[argc - command_num], envp);
	return (SUCCESS);
}
