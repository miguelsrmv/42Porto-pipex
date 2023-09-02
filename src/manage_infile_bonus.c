/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_infile_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 12:23:50 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/09/02 23:14:39 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
	/*if (!ft_strncmp(argv, "/dev/urandom", ft_strlen("/dev/urandom")))
		return (urandom_infile());*/
	/*if (!ft_strncmp(argv, "here_doc", ft_strlen("here_doc")))
		return (heredoc_infile());
	else*/
	return (argv);
}

char	*urandom_infile(void) // Generalizar??
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
