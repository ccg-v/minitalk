#include "minitalk.h"

/*
 * Con esta funcion recogemos las senales
 * y las pasamos de binario a demcimal
 * con operadores binarios, una vez tienes 8 bits
 * (o sea, una caracter) lo muestras en pantalla.
 */

static void	desifrado(int sig)
{
	static t_byna	byna;

	byna.character = 0;
	byna.current_bit = 0;
//	if (byna.starter != 1)
//	{
//		byna.starter = 1;
//		byna.character = 0;
//		byna.current_bit = 0;
//	}
	if (sig == SIGUSR2)
		byna.character = byna.character | 1 << byna.current_bit;
	byna.current_bit++;
	if (byna.current_bit == 8)
	{
		write(1, &byna.character, 1);
		byna.character = 0;
		byna.current_bit = 0;
	}
}

int	main(void)
{
	printf("el PID es: %d\n", getpid());
	signal(SIGUSR1, desifrado);
	signal(SIGUSR2, desifrado);
	while (1)
		sleep(1);
	return (0);
}
