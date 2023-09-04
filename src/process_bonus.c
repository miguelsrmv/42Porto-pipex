/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 21:56:10 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/09/02 23:35:39 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	child_process_first(int *pipe_fd, char *argv, char **envp)
{
	int		file_fd;
	char	*file;

	if (close(pipe_fd[0]) == -1)
		error_exit(NULL, NULL, 0, 0);
	file = check_infile(argv);
	fprintf(stderr, "file: %s\n", file);
	file_fd = open_file(file, IN_FILE);
	if (file_fd == -1)
		error_exit(argv, file, 0, 0);
	if (dup2(file_fd, STDIN_FILENO) == -1)
		error_exit(argv, file, file_fd, 0);
	if (close(file_fd) == -1)
		error_exit(argv, file, file_fd, 0);
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		error_exit(argv, file, pipe_fd[1], 0);
	unlink_free_infile(argv, file);
	if (close(pipe_fd[1]) == -1)
		error_exit(argv, NULL, pipe_fd[1], pipe_fd[0]);
	fprintf(stderr, "First command: %s", check_infile(argv));
	execute_command(check_infile(argv), envp);
}

void	child_process_main(int *pipe_fd, int last_read_fd,
				char *argv, char **envp)
{
	if (last_read_fd == -1)
		child_process_first(pipe_fd, argv, envp);
	else
	{
		if (dup2(last_read_fd, STDIN_FILENO) == -1
			|| dup2(pipe_fd[1], STDOUT_FILENO) == -1)
			error_exit(NULL, NULL, pipe_fd[0], pipe_fd[1]);
		if (close(pipe_fd[0]) == -1 || close(pipe_fd[1]) == -1)
			error_exit(NULL, NULL, pipe_fd[1], pipe_fd[0]);
		execute_command(argv, envp);
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

void	parent_process(int *pipe_fd, int last_read_fd,
			char *argv, char **envp)
{
	int	file_fd;

	close(pipe_fd[1]);
	file_fd = open_file(argv, OUT_FILE);
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
	execute_command(argv, envp);
}
