/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_infile.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 12:23:50 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/09/06 16:29:10 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "pipex.h"

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

char	*check_infile(char *argv)
{
	if (!ft_strncmp(argv, "/dev/urandom", ft_strlen("/dev/urandom")))
		return (urandom_infile());
	else
		return (argv);
}

char	*urandom_infile(void)
{
	char	*urand_buffer;
	char	*buffer_path;
	int		buffer_fd;

	urand_buffer = create_urand_buffer();
	buffer_path = ft_strdup("/tmp/pipex_buffer");
	if (!buffer_path)
		free_memory_buffers(urand_buffer, NULL, 0);
	buffer_fd = open(buffer_path, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (buffer_fd == -1)
		free_memory_buffers(urand_buffer, buffer_path, 0);
	if (write(buffer_fd, urand_buffer, ft_strlen(urand_buffer)) == -1)
		free_memory_buffers(urand_buffer, buffer_path, buffer_fd);
	if (close(buffer_fd) == -1)
		free_memory_buffers(urand_buffer, buffer_path, 0);
	free(urand_buffer);
	return (buffer_path);
}

char	*create_urand_buffer(void)
{
	int		urand_fd;
	char	*urand_buffer;
	int		i;
	int		read_return;

	urand_fd = open("/dev/urandom", O_RDONLY);
	if (urand_fd == -1)
		free_memory_buffers(NULL, NULL, 0);
	urand_buffer = (char *)malloc(sizeof(char) * 1002);
	if (!urand_buffer)
		free_memory_buffers(NULL, NULL, urand_fd);
	i = -1;
	read_return = 1;
	while (++i < 1000 && read_return != -1)
	{
		read_return = read(urand_fd, &urand_buffer[i], 1);
		if (read_return == -1)
			free_memory_buffers(urand_buffer, NULL, urand_fd);
	}
	urand_buffer[i] = '\n';
	urand_buffer[i + 1] = '\0';
	if (close(urand_fd) == -1)
		free_memory_buffers(urand_buffer, NULL, 0);
	return (urand_buffer);
}
