/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipex_args.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 22:06:37 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/08/23 22:17:07 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	parse_pipex_args(char **args)
{
	if (open(*args, O_RDONLY) == -1)
		return (FILE_NOT_FOUND_ERROR);
	return (1);
}
