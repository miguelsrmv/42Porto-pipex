/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 21:57:39 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/09/05 19:13:07 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	error_exit(char *argv, char *file, int fd1, int fd2)
{
	if (fd1)
		close(fd1);
	if (fd2)
		close(fd2);
	if (!ft_strncmp(argv, "/dev/urandom", ft_strlen("/dev/urandom"))
		|| (!ft_strncmp(argv, "here_doc", ft_strlen("here_doc"))))
	{
		unlink(file);
		free(file);
	}
	perror(NULL);
	exit(EXIT_FAILURE);
}

void	usage_check(int argc, char **argv)
{
	if ((argc < 5 || (argc < 6
				&& !ft_strncmp(argv[1], "here_doc", ft_strlen("here_doc")))))
	{
		ft_printf("%s", ARG_USAGE);
		exit(EXIT_FAILURE);
	}
}

void	simple_error_exit(char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}
