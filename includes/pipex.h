/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 20:42:38 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/08/23 22:13:14 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

// Libraries
# include "../src/libft/libft.h"
# include <fcntl.h>

// Error Codes
# define ARG_USAGE_ERROR 1
# define INVALID_ARGS_ERROR 2
# define FILE_NOT_FOUND_ERROR 3
# define INVALID_CMD 4

// Function declarations
int	parse_pipex_args(char **args);

#endif