/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 21:18:06 by ccarrace          #+#    #+#             */
/*   Updated: 2023/03/24 20:34:22 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	ft_error_control(char *str, pid_t pid)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
		{
			ft_putstr_fd(RED"[Bonus]: Pid not valid!\n"DEF_COLOR, 1);
			return (-1);
		}
		str++;
	}
	if (kill(pid, 0) != 0)
	{
		ft_putstr_fd(RED"[Bonus]: There is no process running with that pid!\n" \
				DEF_COLOR, 1);
		return (-1);
	}
	return (0);
}

static void	ft_send_strlen(pid_t pid, int len)
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

static void	ft_send_signal(pid_t pid, unsigned char octet)
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

static void	ft_ack_receipt(int signal, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	if (signal == SIGUSR1)
	{
		ft_putstr_fd(GREEN"[Bonus]: Ack signal received from server: ", 1);
		ft_putstr_fd("message displayed!\n" DEF_COLOR, 1);
	}
	exit(0);
}

int	main(int argc, char **argv)
{
	struct sigaction	newact;
	pid_t				pid;
	char				*str;

	if (argc != 3)
		ft_putstr_fd(RED"Wrong number of arguments supplied!\n"DEF_COLOR, 1);
	else
	{
		newact.sa_sigaction = ft_ack_receipt;
		newact.sa_flags = SA_RESTART;
		pid = ft_atoi(argv[1]);
		if (ft_error_control(argv[1], pid) == -1)
			return (0);
		str = argv[2];
		ft_send_strlen(pid, ft_strlen(str));
		ft_putstr_fd(B_WHITE"-- Sending ", 1);
		ft_putnbr_fd(ft_strlen(str), 1);
		ft_putstr_fd(" characters... --\n"DEF_COLOR, 1);
		while (*str)
			ft_send_signal(pid, *str++);
		sigaction(SIGUSR1, &newact, NULL);
		ft_send_signal(pid, *str);
		pause();
	}
	return (0);
}
