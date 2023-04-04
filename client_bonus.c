/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 21:18:06 by ccarrace          #+#    #+#             */
/*   Updated: 2023/04/03 20:29:36 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	ft_error_control(pid_t pid)
{
	char	*str;

	str = ft_itoa(pid);
	if (pid == 0)
	{
		ft_putstr_fd(RED"[Bonus]: Pid not valid!\n"DEF_COLOR, 1);
		return (-1);
	}
	if (kill(pid, 0) != 0)
	{
		ft_putstr_fd(RED"[Bonus]: There is no process running with that pid!\n" \
				DEF_COLOR, 1);
		return (-1);
	}
	while (*str)
	{
		if (!ft_isdigit(*str))
		{
			ft_putstr_fd(RED"[Bonus]: Pid not valid!\n"DEF_COLOR, 1);
			return (-1);
		}
		str++;
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

static int	ft_send_signal(pid_t pid, unsigned char octet)
{
	int	i;

	i = 0;
	if (kill(pid, 0) != 0)
	{
		ft_putstr_fd(RED"[Bonus]: Server closed by user. ", 1);
		ft_putstr_fd("Transmission interrupted\n"DEF_COLOR, 1);
		return (-1);
	}
	while (i < 8)
	{
		if ((octet & 1 << i) == 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(100);
		i++;
	}
	return (0);
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

/*
		Since norminette's doesn't allow more than 25 lines per function, 
		I can't assign the value of each argument to a variable with a
		more understandable names. So remember:
		argv[1] = pid;	(server's pid)
		argv[2] = str; 	(string to send, allocate and display)
*/

int	main(int argc, char **argv)
{
	struct sigaction	newact;

	if (argc != 3)
		ft_putstr_fd(RED"Wrong number of arguments supplied!\n"DEF_COLOR, 1);
	else
	{
		newact.sa_sigaction = ft_ack_receipt;
		newact.sa_flags = SA_RESTART;
		if (ft_error_control(ft_atoi(argv[1])) == -1)
			return (0);
		ft_send_strlen(ft_atoi(argv[1]), ft_strlen(argv[2]));
		ft_putstr_fd(B_WHITE"-- Sending ", 1);
		ft_putnbr_fd(ft_strlen(argv[2]), 1);
		ft_putstr_fd(" bytes... --\n"DEF_COLOR, 1);
		while (*argv[2])
		{
			if (ft_send_signal(ft_atoi(argv[1]), *argv[2]) == -1)
				return (0);
			argv[2]++;
		}
		sigaction(SIGUSR1, &newact, NULL);
		ft_send_signal(ft_atoi(argv[1]), *argv[2]);
		pause();
	}
	return (0);
}
