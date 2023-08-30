/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 20:42:38 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/08/29 21:35:25 by mde-sa--         ###   ########.fr       */
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

/// Commands.c
char	**get_path_list(char **envp);
char	*get_command_location(char **path, char *command);
void	free_memory(char **path, char **split_commands, char *command_location);
void	execute_command(char *command, char **envp);

/// Main.c
int		open_file(char *arg, int file_type);
void	child_process(int *pipe_fd, char **argv, char **envp);
void	parent_process(int *pipe_fd, char **argv, char **envp);

/// Ft_command_split
typedef struct split_numbers {
	int		wc;
	int		in_word;
	int		in_quote;
	char	quote_char;
	int		len;
}	t_split_numbers;

static int	is_quote(char c);
static char	*get_word(const char *s, size_t *len);
static int	get_word_count(const char *s);
char		**ft_command_split(const char *s);

#endif