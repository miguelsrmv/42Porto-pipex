/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_infile_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 12:23:50 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/09/01 23:01:12 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "pipex.h"

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
	close(buffer_fd);
	free(urand_buffer);
	return (buffer_path);
}

char	*create_urand_buffer(void)
{
	int		urand_fd;
	int		i;
	char	*urand_buffer;

	urand_fd = open("/dev/urandom", O_RDONLY);
	if (urand_fd == -1)
	{
		perror(NULL);
		exit(EXIT_FAILURE);
	}
	urand_buffer = (char *)malloc(sizeof(char) * 1002);
	if (!urand_buffer)
	{
		perror(NULL);
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (read(urand_fd, &urand_buffer[i], 1) && urand_buffer[i] && i < 1000)
		i++;
	urand_buffer[i] = '\n';
	urand_buffer[i + 1] = '\0';
	close(urand_fd);
	return (urand_buffer);
}
