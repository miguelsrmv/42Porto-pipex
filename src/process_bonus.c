/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 21:56:10 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/09/05 17:27:40 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	child_process_first(int *pipe_fd, t_input_var cl_input, char **envp)
{
	int		file_fd;

	if (close(pipe_fd[0]) == -1)
		error_exit(NULL, NULL, 0, 0);
	fprintf(stderr, "file: %s\n", cl_input.input_file);
	file_fd = open_file(cl_input.input_file, IN_FILE);
	if (file_fd == -1)
		error_exit(cl_input.argv[1], cl_input.input_file, 0, 0);
	if (dup2(file_fd, STDIN_FILENO) == -1)
		error_exit(cl_input.argv[1], cl_input.input_file, file_fd, 0);
	if (close(file_fd) == -1)
		error_exit(cl_input.argv[1], cl_input.input_file, file_fd, 0);
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		error_exit(cl_input.argv[1], cl_input.input_file, pipe_fd[1], 0);
	unlink_free_infile(cl_input.argv[1], cl_input.input_file);
	if (close(pipe_fd[1]) == -1)
		error_exit(cl_input.argv[1], NULL, pipe_fd[1], pipe_fd[0]);
	execute_command(cl_input.argv[cl_input.argc - cl_input.command_num], envp);
}

void	child_process_main(int *pipe_fd, t_input_var cl_input, char **envp,
			int last_read_fd)
{
	if (last_read_fd == -1)
		child_process_first(pipe_fd, cl_input, envp);
	else
	{
		if (dup2(last_read_fd, STDIN_FILENO) == -1
			|| dup2(pipe_fd[1], STDOUT_FILENO) == -1)
			error_exit(NULL, NULL, pipe_fd[0], pipe_fd[1]);
		if (close(pipe_fd[0]) == -1 || close(pipe_fd[1]) == -1)
			error_exit(NULL, NULL, pipe_fd[1], pipe_fd[0]);
		execute_command(cl_input.argv[cl_input.argc - cl_input.command_num],
			envp);
	}
}

void	prepare_next_process(int *last_read_fd, int *pipe_fd)
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

	close(pipe_fd[1]);
	file_fd = open_file(cl_input.argv[cl_input.argc - 1], OUT_FILE);
	if (dup2(last_read_fd, STDIN_FILENO) == -1)
	{
		perror(NULL);
		close(pipe_fd[0]);
		exit(EXIT_FAILURE);
	}
	close(pipe_fd[0]);
	if (dup2(file_fd, STDOUT_FILENO) == -1)
	{
		perror(NULL);
		close(file_fd);
		exit(EXIT_FAILURE);
	}
	close(file_fd);
	execute_command(cl_input.argv[cl_input.argc - cl_input.command_num], envp);
}
