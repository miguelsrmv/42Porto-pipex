/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 09:56:28 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/08/23 22:10:56 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv)
{
	if (argc != 5)
		return (ARG_USAGE_ERROR);
	argv++;
	if (parse_pipex_args(argv) != 0)
		return (INVALID_ARGS_ERROR);
	return (0);
}
