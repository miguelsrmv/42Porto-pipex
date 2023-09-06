/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 23:04:04 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/09/06 09:42:29 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

void	error_exit(char *argv, char *file, int fd1, int fd2)
{
	if (fd1 != -1)
		close(fd1);
	if (fd2 != -1)
		close(fd2);
	if (!ft_strncmp(argv, "/dev/urandom", ft_strlen("/dev/urandom")))
	{
		unlink(file);
		free(file);
	}
	perror(NULL);
	exit(EXIT_FAILURE);
}

void	free_memory_command(char **path, char **split_commands,
			char *command_location, int exit_code)
{
	int	i;

	if (exit_code == COMMAND_NOT_FOUND)
		ft_fprintf(STDERR_FILENO, "Error: command not found.\n");
	if (path)
	{
		i = 0;
		while (path[i])
			free(path[i++]);
		free(path);
	}
	if (split_commands)
	{
		i = 0;
		while (split_commands[i])
			free(split_commands[i++]);
		free(split_commands);
	}
	if (command_location)
		free(command_location);
	exit(exit_code);
}

void	free_memory_buffers(char *buffer, char *path, int fd)
{
	if (buffer)
		free(buffer);
	if (path)
		free(path);
	if (fd != -1)
		close(fd);
	perror(NULL);
	exit(EXIT_FAILURE);
}
