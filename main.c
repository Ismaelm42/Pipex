/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoro-sa <imoro-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 11:47:02 by imoro-sa          #+#    #+#             */
/*   Updated: 2023/03/31 17:22:47 by imoro-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid;

	if (argc == 5)
	{
		if (pipe(fd) == -1)
			perror("Error creating pipe");
		pid = fork();
		if (pid == 0)
			child_process(fd, argv, envp);
		else
			parent_process(fd, argv, envp);
	}
	else
	{
		ft_putendl_fd("Invalid number of arguments", 2);
		exit(EXIT_FAILURE);
	}
	return (0);
}
