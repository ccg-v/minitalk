/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_server.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 21:16:41 by ccarrace          #+#    #+#             */
/*   Updated: 2023/03/16 15:03:55 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_data	g_data;

static void	ft_rebuild_bufsize(int signal)
{
	if (signal == SIGUSR2)
		g_data.buffer_size = (g_data.buffer_size | 1 << g_data.current_bit);
	if (g_data.current_bit == 31)
	{
		g_data.flag = 1;
		g_data.buffer = calloc((g_data.buffer_size + 1), sizeof(char));
		if (g_data.buffer == NULL)
		{
			printf("Memory allocation failed!\n");
			return ;
		}
		g_data.current_bit = 0;
		g_data.buffer_size = 0;
		return ;
	}
	(g_data.current_bit)++;
}

static void	ft_print_and_reset(void)
{
	ft_printf("%s\n", g_data.buffer);
	free(g_data.buffer);
	g_data.buffer = NULL;
	g_data.buffer_size = 0;
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
		g_data.buffer[g_data.i] = g_data.octet;
		(g_data.i)++;
		g_data.current_bit = 0;
		if (g_data.octet == '\0')
		{
			ft_print_and_reset();
			kill(client_pid, SIGUSR2);
		}
		g_data.octet = 0;
		return ;
	}
	(g_data.current_bit)++;
}

static void	ft_rebuild_buffer(int signal, siginfo_t *info, void *prev_context)
{
	pid_t	client_pid;

	(void)prev_context;
	client_pid = 0;
	client_pid = info->si_pid;
	if (g_data.flag == 0)
		ft_rebuild_bufsize(signal);
	else
		ft_rebuild_char(signal, client_pid);
}

int	main(void)
{
	struct sigaction	newact;

	ft_printf("The ID of the parent process (pid) is %d\n", getpid());
	newact.sa_sigaction = ft_rebuild_buffer;
	newact.sa_flags = SA_RESTART;
	sigaction(SIGUSR1, &newact, NULL);
	sigaction(SIGUSR2, &newact, NULL);
	while (1)
		pause();
}
