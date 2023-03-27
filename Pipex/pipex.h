
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoro-sa <imoro-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 11:47:19 by imoro-sa          #+#    #+#             */
/*   Updated: 2023/03/22 16:11:00 by imoro-sa         ###   ########.fr       */
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

void	pipex(char **argv, char	**envp);
char	**ft_search_path(char *cmd, char **envp);
void	child_process(int *fd, char **argv, char **envp);
void	parent_process(int *fd, char **argv, char **envp);
// void	*free_malloc();




// char	**ft_cmd(char **argv);
// void	pipex(char **argv, char **envp);






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
Abrir el archivo con Open y cambiar el fd de lectura del pipe para que coja directamente del infile.
También deberíamos crear el archivo outfile.
	Crear una función para encontrar la variable de entorno $PATH = ft_search_path
Se puede hacer esto con un while.
Tiene que buscar la variable de entorno PATH y sacar con un split todos los directorios.
(Separados por :) Ver cómo implementar esto. Una vez hecho esto, habrá que ver si access reconoce el directorio.
Si lo encuentra, reconoce, entonces adelante -> execve. Si no lo encuentra, entonces habrá que seguir buscando o retornar un error.
Verificar: Entiendo que para encontrar el PATH de un ejecutable tendrá que probar a ver si encuentra el comando en cada una de las carpetas y cuando acceda entonces ejecturar execve().
	Sólo necesitamos de un fork. El otro proceso se puede hacer en el proceso parent.
Utilizar el exit para matar un proceso es una opción.
	El proceso debe ser enviado por el pipe de STDIN/STDOUT al fd[] y del fd[] al outfile. (No utilizar buffer).
La estructura de funciones sería:
int		main(int argc, char **argv, char **envp);
void	*ft_search_parth();
void	*pipex();
void	*free_malloc();
void	*child_process();
void	*parent_process();
MAOCS PATH
SSH_AUTH_SOCK=/private/tmp/com.apple.launchd.KBOVQb87NU/Listeners
LC_TERMINAL_VERSION=3.4.15
COLORFGBG=7;0
ITERM_PROFILE=Default
XPC_FLAGS=0x0
LANG=en_US.UTF-8
PWD=/Users/imoro-sa/Documents/Pipex
SHELL=/bin/zsh
SECURITYSESSIONID=186a7
TERM_PROGRAM_VERSION=3.4.15
TERM_PROGRAM=iTerm.app
PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/share/dotnet:/usr/local/munki:~/.dotnet/tools:/Library/Frameworks/Mono.framework/Versions/Current/Commands
LC_TERMINAL=iTerm2
COLORTERM=truecolor
COMMAND_MODE=unix2003
TERM=xterm-256color
HOME=/Users/imoro-sa
TMPDIR=/var/folders/zz/zyxvpxvq6csfxvn_n000cg1h0033rc/T/
USER=imoro-sa
XPC_SERVICE_NAME=0
LOGNAME=imoro-sa
LaunchInstanceID=1498C25F-6B16-4627-9667-129400DF45BF
__CF_USER_TEXT_ENCODING=0x0:0:0
ITERM_SESSION_ID=w0t0p0:C9D9C034-4236-4BCD-AE38-D8B22388DFB7
SHLVL=1
OLDPWD=/Users/imoro-sa/Documents
_=/Users/imoro-sa/Documents/Pipex/./a.out
*/
