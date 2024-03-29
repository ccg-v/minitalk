/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 21:16:41 by ccarrace          #+#    #+#             */
/*   Updated: 2023/04/02 20:41:38 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_data	g_data;

static void	ft_rebuild_string_len(int signal)
{
	if (signal == SIGUSR2)
		g_data.string_len = (g_data.string_len | 1 << g_data.current_bit);
	if (g_data.current_bit == 31)
	{
		g_data.flag = 1;
		g_data.string = ft_calloc((g_data.string_len + 1), sizeof(char));
		if (g_data.string == NULL)
		{
			ft_putstr_fd(RED"[Bonus]: Memory allocation failed!\n"DEF_COLOR, 1);
			return ;
		}
		g_data.current_bit = 0;
		g_data.string_len = 0;
		return ;
	}
	(g_data.current_bit)++;
}

static void	ft_print_and_reset(void)
{
	int	j;

	j = 0;
	while (g_data.string[j] != '\0')
	{
		write(1, &(g_data.string[j]), 1);
		j++;
	}
	write(1, "\n", 1);
	ft_putstr_fd(B_WHITE"-- ", 1);
	ft_putnbr_fd(j, 1);
	ft_putstr_fd(" bytes displayed --\n"DEF_COLOR, 1);
	free(g_data.string);
	g_data.string = NULL;
	g_data.string_len = 0;
	g_data.octet = 0;
	g_data.current_bit = 0;
	g_data.i = 0;
	g_data.flag = 0;
	return ;
}

static void	ft_rebuild_char(int signal, pid_t client_pid)
{
	if (signal == SIGUSR2)
		g_data.octet = (g_data.octet | 1 << g_data.current_bit);
	if (g_data.current_bit == 7)
	{
		g_data.string[g_data.i] = g_data.octet;
		(g_data.i)++;
		g_data.current_bit = 0;
		if (g_data.octet == '\0')
		{
			ft_print_and_reset();
			kill(client_pid, SIGUSR1);
		}
		g_data.octet = 0;
		return ;
	}
	(g_data.current_bit)++;
}

static void	ft_rebuild_string(int signal, siginfo_t *info, void *context)
{
	pid_t	client_pid;

	(void)context;
	client_pid = 0;
	client_pid = info->si_pid;
	if (g_data.flag == 0)
		ft_rebuild_string_len(signal);
	else
		ft_rebuild_char(signal, client_pid);
}

int	main(void)
{
	struct sigaction	newact;
	int					tmp;

	ft_putstr_fd(GREEN"[Bonus]: Server_bonus pid is ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putstr_fd("\n"DEF_COLOR, 1);
	newact.sa_sigaction = ft_rebuild_string;
	newact.sa_flags = SA_RESTART;
	sigaction(SIGUSR1, &newact, NULL);
	sigaction(SIGUSR2, &newact, NULL);
	while (1)
	{
		tmp = g_data.current_bit;
		sleep(1);
		if (g_data.current_bit == tmp)
		{
			free(g_data.string);
			g_data.string = NULL;
			g_data.string_len = 0;
			g_data.octet = 0;
			g_data.current_bit = 0;
			g_data.i = 0;
			g_data.flag = 0;
		}
	}
}
