/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 20:36:36 by ccarrace          #+#    #+#             */
/*   Updated: 2023/03/17 22:41:15 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	ft_send_strlen(int pid, int len)
{
	int	i;

	i = 0;
	while (i < 32)
	{
		if (len & 1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		len = len >> 1;
		i++;
		usleep(100);
	}
}

static void	ft_send_signal(int pid, unsigned char octet)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if ((octet & 1 << i) == 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(100);
		i++;
	}
}

int	main(int argc, char **argv)
{
	int		pid;
	size_t	len;
	char	*s;

	if (argc == 3)
	{
		pid = ft_atoi(argv[1]);
		s = argv[2];
		len = ft_strlen(s);
		ft_send_strlen(pid, len);
		while (*s)
		{
			ft_send_signal(pid, *s);
			s++;
		}
		ft_send_signal(pid, *s);
	}
	else
	{
		ft_printf("No arguments or wrong arguments supplied!\n");
		ft_printf("(Three parameters needed: executable name, ");
		ft_printf("parent process ID (pid) and a string to send)\n");
	}
	return (0);
}
