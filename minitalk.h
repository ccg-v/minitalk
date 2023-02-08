#ifndef MINITALK_H
# define MINITALK_H

/* FUNCIONES A SUSTITUIR POR LAS MIAS PROPIAS
 	- PRINTF
	- ATOI
*/

# include <stdio.h>	// printf()
# include <stdlib.h>	// atoi()
# include <signal.h>	// SIGUSR1, SIGUSR2
# include <unistd.h>	// write(), getpid(), pause(), usleep()

 typedef struct	s_struct
 {
 	int	flag;
	int	len;
 	char	octet;
 	int	current_bit;
 }		t_struct;

 t_struct	data;
// void	server(void);
#endif
