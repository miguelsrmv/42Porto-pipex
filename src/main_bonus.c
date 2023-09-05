/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 12:24:41 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/09/05 17:19:23 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

t_input_var	create_input_struct(int argc, char **argv)
{
	t_input_var	cl_input;

	cl_input.argc = argc;
	cl_input.argv = argv;
	cl_input.input_file = check_infile(argv[1]);
	cl_input.output_file = argv[argc - 1];
	cl_input.command_num = command_calc(argc, argv);
	if (ft_strncmp(argv[1], "here_doc", ft_strlen("here_doc")))
		cl_input.commands_start = &argv[1];
	else
		cl_input.commands_start = &argv[2];
	return (cl_input);
}

int	main(int argc, char **argv, char **envp)
{
	int			pipe_fd[2];
	int			pid;
	t_input_var	cl_input;
	int			last_read_fd;

	usage_check(argc, argv);
	cl_input = create_input_struct(argc, argv);
	last_read_fd = -1;
	while (cl_input.command_num-- > 3)
	{
		if (pipe(pipe_fd) == -1)
			return (ERROR);
		pid = fork();
		if (pid == -1)
			return (ERROR);
		if (pid == 0)
			child_process_main(pipe_fd, cl_input, envp, last_read_fd);
		else
			prepare_next_process(&last_read_fd, pipe_fd);
	}
	parent_process(pipe_fd, cl_input, envp, last_read_fd);
	return (SUCCESS);
}
