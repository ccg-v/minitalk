/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 20:36:36 by ccarrace          #+#    #+#             */
/*   Updated: 2023/02/03 23:44:12 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <stdlib.h>
#include <stdio.h>

/* Standard functions to be replaced by mine:
 * printf()
 * atoi()
 */

static void	ft_send_signal(int pid, unsigned char octet)
{
	int i;

	i = 0;
	while (i < 8)
	{
		if (0 != (octet & 1 << i))
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		usleep(200);
		i++;
	}
}


int	main(int argc, char **argv)
{
	char	*s;
	int		pid;
	int		i;

	if (argc == 3)
	{
		pid = atoi(argv[1]);
		s = argv[2];
		i = 0;	
		while (s[i] != '\0')
		{
			ft_send_signal(pid, s[i]);
			i++;
		}
		ft_send_signal(pid, '\n');
		ft_send_signal(pid, s[i]);
	}
	else
		printf("To run function properly, please type './client' followed\
				by the process id and the string to be sent]'");
	return (0);
}
