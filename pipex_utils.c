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

int	ft_check_access(char *str, char *path_envp)
{
	if (path_envp == NULL)
	{
		perror("Command not found");
		exit(EXIT_FAILURE);
	}
	if (access(str, F_OK) != 0)
		return (1);
	if (access(str, F_OK) == 0 && access(str, X_OK) != 0)
	{
		perror("PATH access error");
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
	//una vez arreglado esto debería estar. Ahora mismo está funcional realmente.
	//tiene comportamiento totalmente aleatorio. A veces crea un fichero otras no.
	while (ft_check_access(str, path_envp[n]) != 0)
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
	else
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
