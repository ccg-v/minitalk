#include "minitalk.h"

/*
 * Funcion que en caso de error nos indica como
 * usar de manera correcta el cliente.
 */

void	mal_uso(void)
{
	printf("el uso correcto es: ./client [PID del server] [mensaje]\n");
	exit(0);
}

/*
 * Esta funcion manda el char pasado a binario al servidor
 * mediante senales.
 *
 * SIGURS2 = 1
 * SIGURS1 = 0
 * con su PID especifico.
 */

void	send_char(int pid, unsigned char caracter)
{
	int	current_bit;

	current_bit = 0;
	while (current_bit < 8)
	{
		if (0 != (caracter & 1 << current_bit))
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		usleep(200);
		current_bit++;
	}
}

/*
 * Funcion a la que le pasamos como argv[1] el PID (en numero)
 * y en el argv[2] el mensaje (en string).
 *
 * Este mensaje lo recorremos para enviar a convertir
 * caracter a caracter en binario.
 */

void	mensaje_a_enviar(int pid, char *mensaje)
{
	while (*mensaje)
	{
		send_char(pid, *mensaje);
		mensaje++;
	}
	send_char(pid, '\n');
	send_char(pid, *mensaje);
}

/*
 * Parte principal, donde le pasamos como paramentro
 * el PID (numero de identificacion de otro proceso)
 * y el mensaje a enviar al servidor.
 */

int	main(int argc, char **argv)
{
	if (argc != 3)
		mal_uso();
	mensaje_a_enviar(atoi(argv[1]), argv[2]);
	return (0);
}
