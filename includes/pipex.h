/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 20:42:38 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/09/05 23:58:21 by mde-sa--         ###   ########.fr       */
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
# define FILE_NOT_FOUND 0
# define COMMAND_NOT_FOUND 127
# define UNABLE_TO_MALLOC "Error: Couldn't allocate memory.\n"
# define ARG_USAGE "Error: Invalid usage.\n"

// Function declarations

/// Commands.c
char	**get_path_list(char **envp);
char	*get_command_location(char **path, char *command);
void	execute_command(char *command, char **envp);

/// Main.c
void	child_process(int *pipe_fd, char **argv, char **envp);
void	parent_process(int *pipe_fd, char **argv, char **envp);

/// ft_command_split.c
typedef struct s_split_numbers {
	int		word_count;
	int		in_word;
	int		in_quote;
	char	quote_char;
	size_t	i;
}	t_split_numbers;

char	**ft_command_split(const char *s);

/// Infile_manage.c
int		open_file(char *arg, int file_type);
char	*check_infile(char *argv);
char	*urandom_infile(void);
char	*create_urand_buffer(void);

/// free_memory.c
void	error_exit(char *argv, char *file, int fd1, int fd2);
void	free_memory_command(char **path, char **split_commands,
			char *command_location, int exit_code);
void	free_memory_buffers(char *buffer, char *path, int fd);

#endif