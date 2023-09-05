/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_infile_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 12:23:50 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/09/05 19:15:49 by mde-sa--         ###   ########.fr       */
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

char	*check_infile(char *argv1, char *argv2)
{
	if (!ft_strncmp(argv1, "/dev/urandom", ft_strlen("/dev/urandom")))
		return (create_infile(create_urand_buffer, NULL));
	else if (!ft_strncmp(argv1, "here_doc", ft_strlen("here_doc")))
		return (create_infile(create_heredoc_buffer, argv2));
	else
		return (argv1);
}

char	*create_infile(char *(create_buffer)(char *limiter), char	*limiter)
{
	char	*buffer;
	char	*buffer_path;
	int		buffer_fd;

	buffer = create_buffer(limiter);
	buffer_path = ft_strdup("/tmp/pipex_buffer");
	if (!buffer_path)
		free_memory_buffers(buffer, NULL, 0);
	buffer_fd = open(buffer_path, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (buffer_fd == -1)
		free_memory_buffers(buffer, buffer_path, 0);
	if (write(buffer_fd, buffer, ft_strlen(buffer)) == -1)
		free_memory_buffers(buffer, buffer_path, buffer_fd);
	close(buffer_fd);
	free(buffer);
	return (buffer_path);
}

char	*create_urand_buffer(char *limiter)
{
	int		urand_fd;
	int		i;
	char	*urand_buffer;

	(void)limiter;
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

char	*create_heredoc_buffer(char *limiter)
{
	char	*result;
	char	*input;
	char	*temp;
	int		bytes_read;

	input = (char *)malloc(sizeof(char) * 1001);
	result = (char *)malloc(sizeof(char) * 1);
	if (!input || !result)
		exit(EXIT_FAILURE);
	result[0] = '\0';
	while (1)
	{
		bytes_read = read(STDIN_FILENO, input, 1000);
		if (!bytes_read)
			free_memory_buffers(input, result, 0);
		input[bytes_read] = '\0';
		if (!ft_strncmp(input, limiter, ft_strlen(limiter)))
			break ;
		temp = ft_strjoin(result, input);
		free(result);
		result = temp;
	}
	free(input);
	return (result);
}