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
	// printf("envp = %s\n", envp[i]);
	str = ft_substr(envp[i], 5, ft_strlen(envp[i]) - 4);
	// printf("str = %s\n", str);
	path_envp = ft_split(str, ':');
	free(str);
	// printf("path_envp = %s\n\n", path_envp[2]);
	path_cmd = ft_split(cmd, ' ');
	i = 0;
	while (path_envp[i] != NULL)
	{
		str = ft_strjoin(path_envp[i], "/");
		str = ft_strjoin(str, path_cmd[0]);
		if (access(str, F_OK) == 0)
			if (access(str, X_OK) == 0)
				break ;
		//printf("str = %s\n", str);
		i++;
	}
	if (path_envp[i] == NULL)
	{
		perror("Command not found");
		exit(EXIT_FAILURE);
	}
	free(path_cmd[0]);
	path_cmd[0] = str; 
	// // mirar si vale la pena un ft_free para liberar la memoria (pro ahora no está liberada)
	// printf("i = %d\n", i);
	// printf("%s\n%s\n%s\n%s\n", path_cmd[0], path_cmd[1], path_cmd[2], path_cmd[3]);
	// printf("\n\n\n");
	return (path_cmd);
}

void	child_process(int *fd, char **argv, char **envp)
{
	char	**path_envp;
	int		fd_file;
	int		stdin_save;
	int		stdout_save;

	close(fd[0]);
	stdin_save = dup(STDIN_FILENO);
	if (stdin_save == -1)
		perror("Error saving stdin");
	stdout_save = dup(STDOUT_FILENO);
	if (stdout_save == -1)
		perror("Error saving stdout");
	//cierre del pipe de lectura que no utilizo;
	path_envp = ft_search_path(argv[2], envp);
	//array para ejecutar execve;
	fd_file = open(argv[1], O_RDONLY, 0666);
	//apertura de archivo en fd;
	if (fd_file == -1)
	{
		perror("File error\n");
		exit(EXIT_FAILURE);
	}
	if (dup2(fd_file, STDIN_FILENO) == -1)
		perror("Error redirecting pipe in 1\n");
	//dup fd de lectura redireccionado a stdin_fileno;
	close(fd_file);
	//cierre del fd de lectura;
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		perror("Error redirecting pipe out 1\n");
	//dup fd de salida redireccionado al pipe fd[1];
	close(fd[1]);
	if (execve(path_envp[0], path_envp, NULL) == -1)
		perror("Error executing command\n");
	//ejecuta el primer comando
	if (dup2(stdin_save, STDIN_FILENO) == -1)
		perror("Error restoring stdin\n");
	if (dup2(stdout_save, STDOUT_FILENO) == -1)
		perror("Error restoring stdout\n");
	//reestablecer los fd STDOUT_FILENO y STDIN_FILENO
	exit(EXIT_FAILURE);
}

void	parent_process(int *fd, char **argv, char **envp)
{
	char	*buffer;
	int		fd_file;
	int		bytes_read;

	argv = (char **)argv;
	envp = (char **)envp;
	close(fd[1]);
	fd_file = open("outfile", O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (fd_file == -1)
	{
		perror("File error 2\n");
		exit(EXIT_FAILURE);
	}
	bytes_read = 1;
	while (bytes_read > 0)
	{
		buffer = malloc (sizeof(char));
		bytes_read = read(fd[0], buffer, bytes_read);
		write(fd_file, buffer, bytes_read);
		free(buffer);
	}
	close(fd[0]);
	close (fd_file);
	return ;
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
	{
		pipex(argv, envp);
	}


	if (argv[argc] == NULL)
		return (0);
	return (0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////// 	PARENT ANTES DE REALIZAR EL SEGUNDO FORK   //////////////////////////////////////////////////////////////////////////////////////////////////

void	parent_process(int *fd, char **argv, char **envp)
{
	char	**path_envp;
	int		stdin_save;
	int		stdout_save;
	// char	*buffer;
	// int		fd_file;
	// int		bytes_read;

	stdin_save = dup(STDIN_FILENO);
	stdout_save = dup(STDOUT_FILENO);
	close(fd[1]);
	//cierre del fd no utilizado;
	path_envp = ft_search_path(argv[3], envp);
	//array para ejecutar execve;
	if (dup2(fd[0], STDIN_FILENO) == -1)
		perror("Error redirecting pipe");
	//dup de fd a stdin;
	close(fd[0]);
	//cierre del fd;
	if (dup2(STDOUT_FILENO, fd[1]) == -1)
		perror("Error redirecting pipe");
	//dup de stdout a fd;
	close(fd[1]);
	//cierre del fd
	if (execve(path_envp[0], path_envp, NULL) == -1)
		perror("Error executing command 2\n");
	//ejecuta el segundo comando

	// fd_file = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0666);
	// if (fd_file == -1)
	// {
	// 	perror("File error 2\n");
	// 	exit(EXIT_FAILURE);
	// }
	// bytes_read = 1;
	// while (bytes_read > 0)
	// {
	// 	buffer = malloc (sizeof(char));
	// 	bytes_read = read(fd[0], buffer, bytes_read);
	// 	write(fd_file, buffer, bytes_read);
	// 	free(buffer);
	// }
	// close(fd[0]);
	// close (fd_file);
	// return ;
}
