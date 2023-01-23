/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 22:54:34 by ccarrace          #+#    #+#             */
/*   Updated: 2023/01/23 23:46:01 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/* Standard functions used to be replaced by mine:
 * printf()
 */

static void	ft_rebuild_char(int bit)
{

}

int	main(void)
{
	printf("Parent process ID [pid] is: %d\n", getpid());
	signal(SIGUSR1, rebuild_char);
	signal(SIGUSR2, rebuild_char);
	while (1)
		sleep(1);
	return (0);
}
