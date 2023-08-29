/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 20:42:38 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/08/29 13:08:38 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

// Libraries
# include "../src/libft/libft.h"
# include <fcntl.h>

// Error Codes
# define SUCCESS 0
# define ERROR 1
# define IN_FILE 0
# define OUT_FILE 1
# define UNABLE_TO_MALLOC "Error: Couldn't allocate memory.\n"
# define ARG_USAGE "Error: Invalid usage.\n"

// Function declarations
/// Main.c
int		open_file(char *arg, int file_type);
void	child_process(int *pipe_fd, char **argv, char **envp);
void	parent_process(int *pipe_fd, char **argv, char **envp);


#endif