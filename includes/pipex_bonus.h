/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 20:42:38 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/09/05 17:28:25 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

// Libraries
# include "../src/libft/libft.h"
# include <fcntl.h>
# include <sys/wait.h>
# include <stdio.h>

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

typedef struct s_input_var {
	int		argc;
	char	**argv;
	char	*input_file;
	char	*output_file;
	int		command_num;
	char	**commands_start;
}	t_input_var;

typedef struct s_split_numbers {
	int		word_count;
	int		in_word;
	int		in_quote;
	char	quote_char;
	size_t	i;
}	t_split_numbers;

/// Commands.c
int		command_calc(int argc, char **argv);
char	**get_path_list(char **envp);
char	*get_command_location(char **path, char *command);
void	execute_command(char *command, char **envp);

/// Process.c
void	child_process_first(int *pipe_fd, t_input_var cl_input, char **envp);
void	child_process_main(int *pipe_fd, t_input_var cl_input, char **envp,
			int last_read_fd);
void	prepare_next_process(int *last_read_fd, int *pipe_fd);		
void	parent_process(int *pipe_fd, t_input_var cl_input, char **envp,
			int last_read_fd);

/// Error_handling_bonus.c
void	error_exit(char *argv, char *file, int fd1, int fd2);
void	usage_check(int argc, char **argv);

/// ft_command_split.c
char	**ft_command_split(const char *s);

/// Manage_infile.c

int		open_file(char *arg, int file_type);
char	*check_infile(char *argv);
char	*urandom_infile(void);
char	*create_urand_buffer(void);

/// Free_memory.c
void	free_memory_command(char **path, char **split_commands,
			char *command_location, int exit_code);
void	free_memory_buffers(char *buffer, char *path, int fd);
void	free_infile(char **argv, char *file, int command_num);
void	unlink_free_infile(char *argv, char *file);

#endif