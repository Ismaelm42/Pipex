/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoro-sa <imoro-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 11:46:55 by imoro-sa          #+#    #+#             */
/*   Updated: 2023/03/22 16:14:40 by imoro-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*

$> < archivo1 comando1 | comando2 > archivo2

$> ./pipex infile "ls -l" "wc -l" outfile
$> ./pipex infile "grep a1" "wc -w" outfile

//void	ft_free(char	**argv)

*/

#include "pipex.h"
#include "Libft/libft.h"

char	**ft_cmd(char **argv)
{
	char	**argv_cmd;

	argv_cmd = ft_split(argv[2], 32);
	//modificado str[n] = 0;
	//str = malloc(sizeof(char **) * (ft_string_counter(s, c) + 2)); (+2 para argv_cmd[2]);
	argv_cmd[0] = ft_strjoin("/bin/", argv_cmd[0]);//modificado (free)
	argv_cmd[2] = ft_strdup(argv[1]);
	argv_cmd[3] = NULL;
	return (argv_cmd);
}

void	pipex(char **argv, char **envp)
{
	char	**argv_cmd;
	char	buffer[100];
	int		pid;
	int		fd[2];

	argv_cmd = ft_cmd(argv);
	if (pipe(fd) == -1)
		perror("Error oppening pipe\n");
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			perror("Error redirecting pipe\n");
		close(fd[1]);
		if (execve(argv_cmd[0], argv_cmd, envp) == -1)
			perror("Error executing command\n");
	}
	else
	{
		wait(NULL);
		close(fd[1]);
		read(fd[0], buffer, 100);
		close(fd[0]);
	}
}

int	main(int argc, char **argv, char **envp)
{
	//pipex(argv, envp);
	int	i = argc;
	i = 1;
	char *str = argv[2];
	str = NULL;
	while (envp[i] != NULL)
	{
		printf("%s\n", envp[i]);
		i++;
	}
	return (0);
}

