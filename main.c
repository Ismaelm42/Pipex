/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoro-sa <imoro-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 11:47:02 by imoro-sa          #+#    #+#             */
/*   Updated: 2023/04/13 12:17:54 by imoro-sa         ###   ########.fr       */
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
			perror("error creating pipe");
		pid = fork();
		if (pid == 0)
			child_process(fd, argv, envp);
		else
			parent_process(fd, argv, envp);
	}
	else
	{
		ft_putstr_fd("invalid number of arguments\n", 2);
		exit(EXIT_FAILURE);
	}
	return (0);
}
