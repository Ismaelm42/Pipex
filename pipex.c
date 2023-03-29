/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoro-sa <imoro-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 11:47:09 by imoro-sa          #+#    #+#             */
/*   Updated: 2023/03/22 14:08:32 by imoro-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
		perror("Error redirecting pipe");
	close(fd_file);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		perror("Error redirecting pipe");
	close(fd[1]);
	if (execve(path_envp[0], path_envp, envp) == -1)
		perror("Error executing command");
	exit(EXIT_FAILURE);
}

void	parent_process(int *fd, char **argv, char **envp)
{
	int		pid;
	int		fd_2[2];

	if (pipe(fd_2) == -1)
		perror("Error openning pipe");
	pid = fork();
	if (pid == 0)
		second_child_process(fd, fd_2, argv, envp);
	else
		second_parent_process(fd, fd_2, argv);
}

void	second_child_process(int *fd, int *fd_2, char **argv, char **envp)
{
	char	**path_envp;

	path_envp = ft_search_path(argv[3], envp);
	close(fd[1]);
	close(fd_2[0]);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		perror("Error redirecting pipe");
	close(fd[0]);
	if (dup2(fd_2[1], STDOUT_FILENO) == -1)
		perror("Error redirecting pipe");
	close(fd_2[1]);
	if (execve(path_envp[0], path_envp, envp) == -1)
		perror("Error executing command");
	exit(EXIT_FAILURE);
}

void	second_parent_process(int *fd, int *fd_2, char **argv)
{
	int		fd_file;

	close(fd[0]);
	close(fd[1]);
	close(fd_2[1]);
	fd_file = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (fd_file == -1)
	{
		perror("File error");
		exit(EXIT_FAILURE);
	}
	printing_pipe(fd_file, fd_2);
	close(fd_2[0]);
	close (fd_file);
	exit(EXIT_SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	int	fd[2];
	int	pid;

	if (argc == 5)
	{
		if (pipe(fd) == -1)
			perror("Error openning pipe");
		pid = fork();
		if (pid == 0)
			child_process(fd, argv, envp);
		else
			parent_process(fd, argv, envp);
	}
	else
	{
		ft_putendl_fd("Error: too much or too few arguments", 1);
		exit(127);
	}
	return (0);
}
