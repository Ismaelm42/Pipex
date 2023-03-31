/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoro-sa <imoro-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 11:47:02 by imoro-sa          #+#    #+#             */
/*   Updated: 2023/03/31 17:22:47 by imoro-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//  infile "ls -l" "awk '{count++} END {print count}'" outfile
//	/usr/bin/awk ''
//	/bin/ls -l

#include "pipex.h"

char	**ft_search_path(char	*cmd, char **envp)
{
	char	**path_envp;
	char	**path_cmd;
	char	*str;
	int		i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strnstr(envp[i], "PATH=", 5) != NULL)
			break ;
		i++;
	}
	str = ft_substr(envp[i], 5, ft_strlen(envp[i]) - 4);
	path_envp = ft_split(str, ':');
	free(str);
	path_cmd = ft_split(cmd, ' ');
	i = 0;
	while (path_envp[i] != NULL)
	{
		str = ft_strjoin(path_envp[i], "/");
		str = ft_strjoin(str, path_cmd[0]);
		if (access(str, F_OK | X_OK) == 0)
			break ;
		i++;
	}
	if (path_envp[i] == NULL)
	{
		perror("Command not found");
		exit(EXIT_FAILURE);
	}
	free(path_cmd[0]);
	path_cmd[0] = str; 
	return (path_cmd);
}

void	printing_pipe(int fd_file, int *fd_2)
{
	char	*buffer;
	int		bytes_read;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		buffer = malloc (sizeof(char));
		bytes_read = read(fd_2[0], buffer, sizeof(char));
		if (bytes_read == -1)
		{
			perror("Error reading pipe");
			exit(EXIT_FAILURE);
		}
		write(fd_file, buffer, bytes_read);
		free(buffer);
	}
}
