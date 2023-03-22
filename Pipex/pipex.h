/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoro-sa <imoro-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 11:47:19 by imoro-sa          #+#    #+#             */
/*   Updated: 2023/03/22 13:27:34 by imoro-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "Libft/libft.h"

void	ft_pipex(char **argv);
char	**ft_cmd(char **argv);
#endif

/*
perror:
		void perror(const char *s);
	(imprime por pantalla un error de mensaje)
	se puede utilizar cuando se activa errno.
	comprobar en man si errno se activa con la función utilizada.
	se utiliza para escribir un mensaje de error claro.
	fopen retorna NULL en el fd, errno -> "error al abrir el fichero"

strerror:
		char *strerror(int errnum);
	(imprime por pantalla el mensaje de error del int que le pasemos)

access:
		int access(const char *pathname, int mode);
	(comprueba los permisos de un usuario para acceder a un archivo)
	mode comprueba los permisos:
	F_OK = Existence of the file
	R_OK = Read
	W_OK = Write
	X_OK = Execute permissions
	retorna 0 si está todo ok, sino retorna -1 y se activa errno
	-(utilizarlo para acceder a un archivo con las flags para saber si podemos acceder a él, concretamente usarlo para encontrar el PATH)-

dup:
		int dup(int oldfd);
	(duplica un fd)
	crea una copia de un fd en el fd no utilizado con el número más bajo
	retorna el fd si todo está ok, sino retorna -1 y se activa errno
dup2:
		int dup(int oldfd, int newfd);
	(duplica un fd en el fd que queramos)
	retorna el fd si todo está ok, sino retorna -1 y se activa errno

execve:
		int execve(const char *pathname, char *const argv[], char *const envp[]);
	(ejecuta un programa)
	el programa que se ejecuta reemplazará el actual.
	argv debe empezar con el nombre del programa que se va a ejecutar y acabar con NULL.
	no retorna nada si se realiza correctamente. si hay error retorna -1 y se activa errno.

exit:
		void exit(int status);
	(termina el proceso en curso)

fork:
		pid_t fork(void);
	(crea un proceso child)
	si se realiza correctamente retornará el pid del child al parent y retorna 0 en el child
	child process id = 0
	parent process id != 0.
	child process es el primero en ejecutarse.
	-(se puede realizar el proyecto con un fork y dos pipes o tres)-
pipe:
		int pipe(int pipefd[2]);
	(crea un pipe)
	abre los fd 0 y 1 y los duplica en el child process por lo que se deben cerrar después de usarlos.
	no se puede usar el mismo pipe para read and write bilateralmente entre child y parent.
	no retorna nada si se realiza correctamente. si hay error retorna -1 y se activa errno.

unlink:
	(llama a la función unlink para borrar un archivo determinado)
		
wait:
		pid_t wait(int *wstatus);
	(espera a que un proceso cambie de estado)
	se puede utilizar para esperar a que un child process termine de ejecutarse,
	y asi no se ejecute en paralelo o de forma caótica con un parent process.
	wait(NULL) al final del programa espera a que todos los child process se ejecuten.

waitpid:
		pid_t waitpid(pid_t pid, int *wstatus, int options);
	(espera a que un proceso cambie de estado)

ideas:
	Echar un vistazo a algún proyecto si el ft_search_path es demasiado complejo o
empezar el proyecto directamente.

	Antes que nada necesitamos lo primero comprobar los permisos con ACCESS y las flags.
También deberíamos crear el archivo outfile.

	ft_search_path
Tiene que buscar la variable de entorno PATH y sacar con un split todos los directorios.
(Separados por :)
Ver cómo implementar esto.

	Sólo necesitamos de un fork. El otro proceso se puede hacer en el proceso parent.
Utilizar el exit para matar un proceso. El proceso enviado por el pipe de STDIN/STDOUT al fd[] y del fd[] output.

*/
