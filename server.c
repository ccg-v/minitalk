/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 22:54:34 by ccarrace          #+#    #+#             */
/*   Updated: 2023/02/03 23:01:39 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <stdio.h>

/* Standard functions used to be replaced by mine:
 * printf()
 */

static void	ft_rebuild_char(int sig)
{
	t_server	g_server;

	if (g_server.flag != 1)
	{
		g_server.octet = 0;
		g_server.current_bit = 0;
		g_server.flag = 1;
	}
	if (sig == SIGUSR2)
		g_server.octet = g_server.octet | 1 << g_server.current_bit;
	g_server.current_bit++;
	if (g_server.current_bit == 8)
	{	
		write(1, &g_server.octet, 1);
		g_server.octet = 0;
		g_server.current_bit = 0;
	}
}

int	main(void)
{
	printf("Parent process ID [pid] is: %d\n", getpid());
	signal(SIGUSR1, ft_rebuild_char);
	signal(SIGUSR2, ft_rebuild_char);
	while (1)
//		signal(SIGUSR1, ft_rebuild_char);
//		signal(SIGUSR2, ft_rebuild_char);
		sleep(1);
	return (0);
}
