/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoro-sa <imoro-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 11:47:19 by imoro-sa          #+#    #+#             */
/*   Updated: 2023/04/03 12:45:32 by imoro-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <stdio.h>
# include <fcntl.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "libft/libft.h"

int		main(int argc, char **argv, char **envp);
void	child_process(int *fd, char **argv, char **envp);
void	parent_process(int *fd, char **argv, char **envp);
void	second_child_process(int *fd, int *fd_2, char **argv, char **envp);
void	second_parent_process(int *fd, int *fd_2, int fd_file);
void	printing_pipe(int fd_file, int *fd_2);
char	**ft_path_envp(char **envp);
void	ft_check_error(char *str, char *path_comd);
int		ft_check_access(char *str, char *path_envp, char *path_comd);
char	**ft_path_comd(char	**path_comd, char **path_envp);
char	**ft_path(char	*comd, char **envp);
char	**ft_pipex_splitter(char *str);

#endif
