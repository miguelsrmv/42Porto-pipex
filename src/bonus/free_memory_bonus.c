/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 23:04:04 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/09/06 02:37:56 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	usage_check(int argc, char **argv)
{
	if ((argc < 5 || (argc < 6
				&& !ft_strncmp(argv[1], "here_doc", ft_strlen("here_doc")))))
	{
		ft_printf("%s", ARG_USAGE);
		exit(EXIT_FAILURE);
	}
}

void	error_exit(t_input_var *cl_input, int fd1, int fd2, int fd3)
{
	if (fd1 != 1)
		close(fd1);
	if (fd2 != -1)
		close(fd2);
	if (fd3 != -1)
		close(fd3);
	if (cl_input != 0)
	{
		if (!ft_strncmp((cl_input->argv[1]), "/dev/urandom",
				ft_strlen("/dev/urandom")) || (!ft_strncmp((cl_input->argv[1]),
					"here_doc", ft_strlen("here_doc"))))
		{
			unlink(cl_input->input_file);
			free(cl_input->input_file);
		}
	}
	perror(NULL);
	exit(EXIT_FAILURE);
}

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
	if (fd != -1)
		close(fd);
	perror(NULL);
	exit(EXIT_FAILURE);
}
