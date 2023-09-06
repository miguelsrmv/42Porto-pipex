/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 21:56:10 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/09/06 16:17:21 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	child_process_first(int *pipe_fd, t_input_var cl_input, char **envp,
				int last_read_fd)
{
	int		file_fd;

	if (close(pipe_fd[0]) == -1)
		error_exit(NULL, pipe_fd[0], pipe_fd[1], last_read_fd);
	file_fd = open_file(cl_input, IN_FILE);
	if (file_fd == -1)
		error_exit(&cl_input, 0, pipe_fd[1], last_read_fd);
	if (dup2(file_fd, STDIN_FILENO) == -1)
		error_exit(&cl_input, file_fd, pipe_fd[1], last_read_fd);
	if (close(file_fd) == -1)
		error_exit(&cl_input, file_fd, pipe_fd[1], last_read_fd);
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		error_exit(&cl_input, 0, pipe_fd[1], last_read_fd);
	if (!ft_strncmp(cl_input.argv[1], "/dev/urandom", ft_strlen("/dev/urandom")
			|| (!ft_strncmp(cl_input.argv[1], "here_doc",
					ft_strlen("here_doc")))))
	{
		unlink(cl_input.input_file);
		free(cl_input.input_file);
	}
	if (close(pipe_fd[1]) == -1)
		error_exit(NULL, 0, pipe_fd[1], last_read_fd);
	exec_command(cl_input.argv[cl_input.argc - cl_input.command_num], envp);
}

void	child_process_main(int *pipe_fd, t_input_var cl_input, char **envp,
			int last_read_fd)
{
	if (last_read_fd == -1)
		child_process_first(pipe_fd, cl_input, envp, last_read_fd);
	else
	{
		if (dup2(last_read_fd, STDIN_FILENO) == -1)
			error_exit(NULL, pipe_fd[0], pipe_fd[1], last_read_fd);
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
			error_exit(NULL, pipe_fd[0], pipe_fd[1], last_read_fd);
		if (close(pipe_fd[0]) == -1)
			error_exit(NULL, pipe_fd[0], pipe_fd[1], last_read_fd);
		if (close(pipe_fd[1]) == -1)
			error_exit(NULL, 0, pipe_fd[1], last_read_fd);
		if (close(last_read_fd) == -1)
			error_exit(NULL, 0, 0, last_read_fd);
		exec_command(cl_input.argv[cl_input.argc - cl_input.command_num], envp);
	}
}

void	prepare_next_process(int *pipe_fd, int *last_read_fd)
{
	if (*last_read_fd != -1)
		close(*last_read_fd);
	close(pipe_fd[1]);
	*last_read_fd = pipe_fd[0];
	wait(NULL);
}

void	parent_process(int *pipe_fd, t_input_var cl_input, char **envp,
			int last_read_fd)
{
	int	file_fd;

	file_fd = open_file(cl_input, OUT_FILE);
	if (!file_fd)
		error_exit(NULL, 0, pipe_fd[0], 0);
	if (dup2(last_read_fd, STDIN_FILENO) == -1)
		error_exit(NULL, pipe_fd[0], file_fd, 0);
	if (close(pipe_fd[0]) == -1)
		error_exit(NULL, pipe_fd[0], file_fd, 0);
	if (dup2(file_fd, STDOUT_FILENO) == -1)
		error_exit(NULL, 0, file_fd, 0);
	if (close(file_fd) == -1)
		error_exit(NULL, 0, file_fd, 0);
	exec_command(cl_input.argv[cl_input.argc - cl_input.command_num], envp);
}
