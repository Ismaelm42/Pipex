/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoro-sa <imoro-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 11:47:02 by imoro-sa          #+#    #+#             */
/*   Updated: 2023/03/22 11:47:03 by imoro-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//  infile "ls -l" "awk '{count++} END {print count}'" outfile
//	/usr/bin/awk ''
//	ls -l

// 

#include "pipex.h"

















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
			perror("Error reading pipe");
			exit(EXIT_FAILURE);
		}
		write(fd_file, buffer, bytes_read);
		free(buffer);
	}
}
