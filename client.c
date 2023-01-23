/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 20:36:36 by ccarrace          #+#    #+#             */
/*   Updated: 2023/01/23 23:45:35 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

/* Standard functions to be replaced by mine:
 * printf()
 * atoi()
 */

static void	ft_send_signal(int pid, unsigned char octet)
{
	int bit;
	int	mask;

	i = 7;
	mask = 128;
	while (i >= 0)
	{
		if (octet & mask)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		i--;
		mask /= 2; 
	}
	printf("\n");
}

int	main(int argc, char **argv)
{
	char	*s;
	int		pid;

	pid = atoi(argv[1]);
	s = argv[2];
	if (argc == 3)
	{
		while (*s)
		{
			ft_send_signal(pid, *s);
			s++;
		}
	}
	else
		printf("To run function properly, please type './client' followed \
				by the process id and the string to be sent]'");
	return (0);
}
