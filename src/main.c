/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 12:24:41 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/08/30 11:10:06 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <sys/wait.h>
#include <stdio.h>

int	open_file(char *arg, int file_type)
{
	int	file_fd;

	if (file_type == IN_FILE)
		file_fd = open(arg, O_RDONLY, 0777);
	if (file_type == OUT_FILE)
		file_fd = open(arg, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (file_fd == -1)
	{
		perror(NULL);
		exit(EXIT_FAILURE);
	}
	return (file_fd);
}

void	child_process(int *pipe_fd, char **argv, char **envp)
{
	int	file_fd;

	close(pipe_fd[0]);
	file_fd = open_file(argv[1], IN_FILE);
	if (dup2(file_fd, STDIN_FILENO) == -1)
	{
		perror(NULL);
		close(file_fd);
		exit(EXIT_FAILURE);
	}
	close(file_fd);
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
	{
		perror(NULL);
		close(pipe_fd[1]);
		exit(EXIT_FAILURE);
	}
	close(pipe_fd[1]);
	execute_command(argv[2], envp);
}

void	parent_process(int *pipe_fd, char **argv, char **envp)
{
	int	file_fd;

	close(pipe_fd[1]);
	file_fd = open_file(argv[4], OUT_FILE);
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
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
	execute_command(argv[3], envp);
}

int	main(int argc, char **argv, char **envp)
{
	int	pipe_fd[2];
	int	pid;

	if (argc != 5)
	{
		ft_printf("%s", ARG_USAGE);
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
