/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_prueba.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoro-sa <imoro-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 11:47:09 by imoro-sa          #+#    #+#             */
/*   Updated: 2023/03/22 14:08:32 by imoro-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*

$> < archivo1 comando1 | comando2 > archivo2

$> ./pipex infile "ls -l" "wc -l" outfile
$> ./pipex infile "grep a1" "wc -w" outfile

*/

//void	ft_free(char	**argv)

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

void	child_process(int *fd, char **argv, char **envp)
{
	char	**path_envp;
	int		fd_file;

	close(fd[0]);
	//cierre del pipe de lectura que no utilizo;
	path_envp = ft_search_path(argv[2], envp);
	//array para ejecutar execve;
	fd_file = open(argv[1], O_RDONLY, 0666);
	//apertura de archivo en fd;
	if (fd_file == -1)
	{
		perror("File error");
		exit(EXIT_FAILURE);
	}
	if (dup2(fd_file, STDIN_FILENO) == -1)
		perror("Error redirecting pipe in 1");
	//dup fd de lectura redireccionado a stdin_fileno;
	close(fd_file);
	//cierre del fd de lectura;
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		perror("Error redirecting pipe out 1");
	//dup fd de salida redireccionado al pipe fd[1];
	close(fd[1]);
	if (execve(path_envp[0], path_envp, NULL) == -1)
		perror("Error executing command");
	//ejecuta el primer comando
	exit(EXIT_FAILURE);
}

void	parent_process(int *fd, char **argv, char **envp)
{
	int		pid;
	int		fd_2[2];
	int		fd_file;
	int		bytes_read;
	char	*buffer;
	char	**path_envp;

	if (pipe(fd_2) == -1)
		perror("Error openning pipe 2");
	pid = fork();
	if (pid == 0)
	{
		path_envp = ft_search_path(argv[3], envp);
		//child process reenvia la salida por fd[1] y recibimos por fd[0];
		close(fd[1]);
		close(fd_2[0]);
		//cierre de los fd que no utilizo
		if (dup2(fd[0], STDIN_FILENO) == -1)
			perror("Error redirecting pipe in 2");
		//redirección de fd a stdin
		close(fd[0]);
		if (dup2(fd_2[1], STDOUT_FILENO) == -1)
			perror("Error redirecting pipe out 2");
		//redirección de stdout a fd_2;
		close(fd_2[1]);
		if (execve(path_envp[0], path_envp, NULL) == -1)
			perror("Error executing command");
		//si falla debo liberar la memoria de path_envp;
		exit(EXIT_FAILURE);
	}
	else
	{
		close(fd[0]);
		close(fd[1]);
		close(fd_2[1]);
		fd_file = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0666);
		if (fd_file == -1)
		{
			perror("File error 2\n");
			exit(EXIT_FAILURE);
		}
		bytes_read = 1;
		while (bytes_read > 0)
		{
			buffer = malloc (sizeof(char));
			bytes_read = read(fd_2[0], buffer, sizeof(char));
			write(fd_file, buffer, bytes_read);
			free(buffer);
		}
		close(fd_2[0]);
		close (fd_file);
		exit(EXIT_SUCCESS);
	}
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

