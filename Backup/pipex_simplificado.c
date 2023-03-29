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
	“<infile ls -l | wc -l >outfile"
$> ./pipex infile "grep a1" "wc -w" outfile
 	“<infile grep a1 | wc -w >outfile”

//void	ft_free(char	**argv)

*/

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
		if (access(str, F_OK) == 0)
			if (access(str, X_OK) == 0)
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

void	child_process(int *fd, char **argv, char **envp)
{
	char	**path_envp;
	int		fd_file;

	close(fd[0]);
	path_envp = ft_search_path(argv[2], envp);
	fd_file = open(argv[1], O_RDONLY, 0666);
	if (fd_file == -1)
	{
		perror("File error");
		exit(EXIT_FAILURE);
	}
	if (dup2(fd_file, STDIN_FILENO) == -1)
		perror("Error redirecting pipe in 1");
	close(fd_file);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		perror("Error redirecting pipe out 1");
	close(fd[1]);
	if (execve(path_envp[0], path_envp, NULL) == -1)
		perror("Error executing command");
	exit(EXIT_FAILURE);
}

void	parent_process(int *fd, char **argv, char **envp)
{
	char	**path_envp;
	int		fd_file;

	close(fd[1]);
	path_envp = ft_search_path(argv[3], envp);
	fd_file = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd_file == -1)
	{
		perror("File error 2\n");
		exit(EXIT_FAILURE);
	}
	if (dup2(fd[0], STDIN_FILENO) == -1)
		perror("Error redirecting pipe in 2");
	close(fd[0]);
	if (dup2(fd_file, STDOUT_FILENO) == -1)
		perror("Error redirecting pipe out 2");
	close(fd_file);
	if (execve(path_envp[0], path_envp, NULL) == -1)
		perror("Error executing command 2");
	exit(EXIT_FAILURE);
}

void	pipex(char **argv, char	**envp)
{
	int		fd[2];
	int		pid;

	if (pipe(fd) == -1)
		perror("Error openning pipe");
	pid = fork();
	if (pid == 0)
		child_process(fd, argv, envp);
	else
		parent_process(fd, argv, envp);
}

int	main(int argc, char **argv, char **envp)
{
	if (argc >= 0)
		pipex(argv, envp);
	if (argv[argc] == NULL)
		return (0);
	return (0);
}

