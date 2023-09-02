/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 23:04:04 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/09/02 23:07:43 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	free_memory_command(char **path, char **split_commands,
			char *command_location, int exit_code)
{
	int	i;

	if (exit_code == COMMAND_NOT_FOUND)
		ft_printf_fd(STDERR_FILENO, "Error: command not found.\n");
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
	if (fd)
		close(fd);
	perror(NULL);
	exit(EXIT_FAILURE);
}

void	unlink_free_infile(char *argv, char *file)
{

	if ((!ft_strncmp(argv, "/dev/urandom", ft_strlen("/dev/urandom"))
			|| !ft_strncmp(argv, "here_doc", ft_strlen("here_doc"))))
	{
		unlink(file);
		free(file);
	}
}
	