/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoro-sa <imoro-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 11:47:09 by imoro-sa          #+#    #+#             */
/*   Updated: 2023/04/11 19:10:27 by imoro-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process(int *fd, char **argv, char **envp)
{
	char	**path_envp;
	int		fd_file;

	close(fd[0]);
	path_envp = ft_path(argv[2], envp);
	fd_file = open(argv[1], O_RDONLY, 0666);
	if (fd_file == -1)
	{
		perror(argv[1]);
		exit(EXIT_FAILURE);
	}
	if (dup2(fd_file, STDIN_FILENO) == -1)
		perror("error redirecting pipe");
	close(fd_file);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		perror("error redirecting pipe");
	close(fd[1]);
	if (execve(path_envp[0], path_envp, envp) == -1)
		perror("error executing command");
	exit(EXIT_FAILURE);
}

void	parent_process(int *fd, char **argv, char **envp)
{
	pid_t	pid;
	int		fd_file;
	int		fd_2[2];

	fd_file = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (fd_file == -1)
	{
		perror(argv[4]);
		exit(EXIT_FAILURE);
	}
	if (pipe(fd_2) == -1)
		perror("error openning pipe");
	pid = fork();
	if (pid == 0)
		second_child_process(fd, fd_2, argv, envp);
	else
		second_parent_process(fd, fd_2, fd_file);
}

void	second_child_process(int *fd, int *fd_2, char **argv, char **envp)
{
	char	**path_envp;

	path_envp = ft_path(argv[3], envp);
	close(fd[1]);
	close(fd_2[0]);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		perror("error redirecting pipe");
	close(fd[0]);
	if (dup2(fd_2[1], STDOUT_FILENO) == -1)
		perror("error redirecting pipe");
	close(fd_2[1]);
	if (execve(path_envp[0], path_envp, envp) == -1)
		perror("error executing command");
	exit(EXIT_FAILURE);
}

void	second_parent_process(int *fd, int *fd_2, int fd_file)
{
	close(fd[0]);
	close(fd[1]);
	close(fd_2[1]);
	printing_pipe(fd_file, fd_2);
	close(fd_2[0]);
	close (fd_file);
	exit(EXIT_SUCCESS);
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
			perror("error reading pipe");
			exit(EXIT_FAILURE);
		}
		write(fd_file, buffer, bytes_read);
		free(buffer);
	}
}

// void	ft_leaks(void)
// {
// 	system ("leaks -q pipex");
// }
