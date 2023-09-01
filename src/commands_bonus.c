/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 13:14:10 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/09/01 23:05:31 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_path_list(char **envp)
{
	char	*envp_copy;
	char	**dirs;
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	if (envp[i] == NULL)
		return (NULL);
	envp_copy = ft_strdup(envp[i] + 5);
	if (envp_copy == NULL)
		return (NULL);
	dirs = ft_split(envp_copy, ':');
	free(envp_copy);
	if (dirs == NULL)
		return (NULL);
	return (dirs);
}

char	*get_command_location(char **path, char *command)
{
	char	*tmp;
	char	*test_location;
	int		i;

	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		if (tmp == NULL)
			return (NULL);
		test_location = ft_strjoin(tmp, command);
		free (tmp);
		if (test_location == NULL)
			return (NULL);
		if (access(test_location, F_OK | X_OK) == 0)
			return (test_location);
		free(test_location);
		i++;
	}
	return (NULL);
}

void	execute_command(char *command, char **envp)
{
	char	**path;
	char	**split_commands;
	char	*command_location;

	path = get_path_list(envp);
	if (path == NULL)
		free_memory_command(NULL, NULL, NULL, EXIT_FAILURE);
	split_commands = ft_command_split(command);
	if (split_commands == NULL)
		free_memory_command(path, NULL, NULL, EXIT_FAILURE);
	command_location = get_command_location(path, split_commands[0]);
	if (command_location == NULL)
		free_memory_command(path, split_commands, NULL, COMMAND_NOT_FOUND);
	free(path);
	if (execve(command_location, split_commands, envp) == -1)
		free_memory_command(path, split_commands,
			command_location, EXIT_FAILURE);
}
