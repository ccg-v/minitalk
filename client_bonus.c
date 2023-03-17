/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_client.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 21:18:06 by ccarrace          #+#    #+#             */
/*   Updated: 2023/03/16 15:03:18 by ccarrace         ###   ########.fr       */
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

static void	ft_ack_receipt(int signal, siginfo_t *info, void *prev_context)
{
	(void)prev_context;
	(void)info;
	if (signal == SIGUSR2)
		ft_printf(GREEN"Ack signal received from server: message displayed!\n");
	exit(0);
}

int	main(int argc, char **argv)
{
	struct sigaction	newact;
	pid_t				pid;
	size_t				len;
	char				*s;

	if (argc == 3)
	{
		newact.sa_sigaction = ft_ack_receipt;
		newact.sa_flags = SA_RESTART;
		pid = ft_atoi(argv[1]);
		s = argv[2];
		len = ft_strlen(s);
		ft_send_strlen(pid, len);
		while (*s)
		{
			ft_send_signal(pid, *s);
			s++;
		}
		sigaction(SIGUSR2, &newact, NULL);
		ft_send_signal(pid, *s);
		pause();
	}
	else
		ft_printf("Please check the supplied parameters!\n");
	return (0);
}

/*
static void	ft_ack_receipt(int signal)
{
	if (signal == SIGUSR2)
		ft_printf(GREEN"Ack signal received from server: message displayed!\n");
	exit(0);
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
		signal(SIGUSR2, ft_ack_receipt);
		ft_send_signal(pid, *s);
		pause();
	}
	else
	{
		ft_printf("No arguments or wrong arguments supplied!\n");
		ft_printf("(Three parameters needed: executable/PID/string)\n");
	}
	return (0);
}
*/
