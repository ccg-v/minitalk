/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 20:36:36 by ccarrace          #+#    #+#             */
/*   Updated: 2023/03/31 23:41:49 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	ft_error_control(pid_t pid)
{
	char	*str;

	str = ft_itoa(pid);
	if (pid == 0)
	{
			ft_putstr_fd(RED"Pid not valid!\n"DEF_COLOR, 1);
			return (-1);
	}
	if (kill(pid, 0) != 0)
	{
		ft_putstr_fd(RED"There is no process running with that pid!\n" \
				DEF_COLOR, 1);
		return (-1);
	}
	while (*str)
	{
		if (!ft_isdigit(*str))
		{	
			ft_putstr_fd(RED"Pid not valid!\n"DEF_COLOR, 1);
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

int	main(int argc, char **argv)
{
	pid_t		pid;
	char		*str;

	if (argc != 3)
		ft_putstr_fd(RED"Wrong number of arguments supplied!\n"DEF_COLOR, 1);
	else
	{
		pid = ft_atoi(argv[1]);
		if (ft_error_control(pid) == -1)
			return (0);
		str = argv[2];
		ft_send_strlen(pid, ft_strlen(str));
		ft_putstr_fd(B_WHITE"-- Sending ", 1);
		ft_putnbr_fd(ft_strlen(str), 1);
		ft_putstr_fd(" characters... --\n"DEF_COLOR, 1);
		while (*str)
			ft_send_signal(pid, *str++);
		ft_send_signal(pid, *str);
	}
	return (0);
}
