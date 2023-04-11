/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoro-sa <imoro-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 11:47:02 by imoro-sa          #+#    #+#             */
/*   Updated: 2023/04/11 17:04:21 by imoro-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**ft_path_envp(char **envp)
{
	char	**path_envp;
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
	return (path_envp);
}

void	ft_check_error(char *str, char *path_comd)
{
	if (access(str, F_OK) != 0)
	{
		perror(path_comd);
		exit(EXIT_FAILURE);
	}
	if (access(str, F_OK) == 0 && access(str, X_OK) != 0)
	{
		perror(path_comd);
		exit(EXIT_FAILURE);
	}
}

int	ft_check_access(char *str, char *path_envp, char *path_comd)
{
	if (path_envp == NULL)
	{
		ft_putstr_fd("command not found: ", 2);
		ft_putstr_fd(path_comd, 2);
		ft_putstr_fd("\n", 2);
		exit(EXIT_FAILURE);
	}
	if (access(str, F_OK) != 0)
		return (1);
	if (access(str, F_OK) == 0 && access(str, X_OK) != 0)
	{
		ft_putstr_fd("PATH access error", 2);
		exit(EXIT_FAILURE);
	}
	if (access(str, F_OK | X_OK) == 0)
		return (0);
	return (1);
}

char	**ft_path_comd(char	**path_comd, char **path_envp)
{
	char	*str;
	int		n;

	n = 0;
	str = path_comd[0];
	if (ft_strchr(str, '/') != NULL && ft_strchr(str, ' ') != NULL)
		str = ft_strtrim(str, "'");
	if (ft_strchr(str, '/') != NULL)
		ft_check_error(str, path_comd[0]);
	while (ft_check_access(str, path_envp[n], path_comd[0]) != 0)
	{
		str = ft_strjoin(path_envp[n], "/");
		str = ft_strjoin(str, path_comd[0]);
		n++;
	}
	if (str != path_comd[0])
	{
		free(path_comd[0]);
		path_comd[0] = str;
		return (path_comd);
	}
	return (path_comd);
}

char	**ft_path(char	*comd, char **envp)
{
	char	**path_comd;
	char	**path_envp;

	path_comd = ft_pipex_splitter(comd);
	path_envp = ft_path_envp(envp);
	return (ft_path_comd(path_comd, path_envp));
}
