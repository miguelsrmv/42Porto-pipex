/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 12:24:41 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/09/06 16:27:52 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <sys/wait.h>
#include <stdio.h>

void	child_process(int *pipe_fd, char **argv, char **envp)
{
	int		file_fd;
	char	*file;

	if (close(pipe_fd[0]) == -1)
		error_exit(argv[1], NULL, 0, 0);
	file = check_infile(argv[1]);
	file_fd = open_file(file, IN_FILE);
	if (file_fd == -1)
		error_exit(argv[1], file, 0, 0);
	if (dup2(file_fd, STDIN_FILENO) == -1)
		error_exit(argv[1], file, pipe_fd[1], file_fd);
	if (close(file_fd) == -1)
		error_exit(argv[1], file, pipe_fd[1], 0);
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		error_exit(argv[1], file, pipe_fd[1], 0);
	if (close(pipe_fd[1]) == -1)
		error_exit(argv[1], file, 0, 0);
	if (!ft_strncmp(argv[1], "/dev/urandom", ft_strlen("/dev/urandom")))
	{
		unlink(file);
		free(file);
	}
	execute_command(argv[2], envp);
}

void	parent_process(int *pipe_fd, char **argv, char **envp)
{
	int	file_fd;

	if (close(pipe_fd[1]) == -1)
		error_exit(argv[1], NULL, 0, 0);
	file_fd = open_file(argv[4], OUT_FILE);
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
		error_exit(argv[1], NULL, file_fd, pipe_fd[0]);
	if (close(pipe_fd[0]) == -1)
		error_exit(argv[1], NULL, file_fd, 0);
	if (dup2(file_fd, STDOUT_FILENO) == -1)
		error_exit(argv[1], NULL, file_fd, 0);
	if (close(file_fd) == -1)
		error_exit(argv[1], NULL, 0, 0);
	execute_command(argv[3], envp);
}

int	main(int argc, char **argv, char **envp)
{
	int	pipe_fd[2];
	int	pid;

	if (argc != 5)
	{
		ft_fprintf(STDERR_FILENO, "%s", ARG_USAGE);
		return (ERROR);
	}
	if (pipe(pipe_fd) == -1)
		return (ERROR);
	pid = fork();
	if (pid == -1)
		return (ERROR);
	if (pid == 0)
		child_process(pipe_fd, argv, envp);
	wait(NULL);
	parent_process(pipe_fd, argv, envp);
	return (SUCCESS);
}
