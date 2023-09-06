/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_infile_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 12:23:50 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/09/06 16:19:59 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	open_file(t_input_var cl_input, int file_type)
{
	int	file_fd;

	if (file_type == IN_FILE)
		file_fd = open(cl_input.input_file, O_RDONLY, 0777);
	else if (file_type == OUT_FILE)
	{
		if (ft_strncmp(cl_input.argv[1], "here_doc", ft_strlen("here_doc")))
			file_fd = open(cl_input.output_file, O_WRONLY | O_CREAT | O_TRUNC,
					0777);
		else
			file_fd = open(cl_input.output_file, O_WRONLY | O_CREAT | O_APPEND,
					0777);
	}
	if (file_fd == -1)
	{
		close(file_fd);
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
	char	*urand_buffer;
	int		i;
	int		read_return;

	(void)limiter;
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
		free_memory_buffers(urand_buffer, NULL, urand_fd);
	return (urand_buffer);
}

char	*create_heredoc_buffer(char *limiter)
{
	char	*result;
	char	*input;
	char	*temp;
	int		bytes_read;

	input = (char *)malloc(sizeof(char) * 1001);
	result = (char *)ft_calloc(1, sizeof(char));
	if (!input || !result)
		exit(EXIT_FAILURE);
	while (1)
	{
		bytes_read = read(STDIN_FILENO, input, 1000);
		if (bytes_read == -1)
			free_memory_buffers(input, result, 0);
		input[bytes_read] = '\0';
		if (!ft_strncmp(input, limiter, ft_strlen(limiter)))
			break ;
		temp = ft_strjoin(result, input);
		if (!temp)
			free_memory_buffers(input, result, 0);
		free(result);
		result = temp;
	}
	free(input);
	return (result);
}
