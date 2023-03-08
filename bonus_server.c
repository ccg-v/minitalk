/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_server.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 21:16:41 by ccarrace          #+#    #+#             */
/*   Updated: 2023/03/08 22:55:57 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	ft_rebuild_strlen(t_data *g_data,	int signal)
{
	int	message_len;

	message_len = 0;
	if (signal == SIGUSR2)
		message_len = (message_len | 1 << g_data->current_bit);
	if (g_data->current_bit == 31)
	{
		g_data->flag = 1;
		g_data->message = ft_calloc((message_len + 1), sizeof(char));
		g_data->current_bit = 0;
		message_len = 0;
		return ;
	}
	(g_data->current_bit)++;
}

static void	ft_print_and_reset(char **pointer, char *message, int *i, \
		int *flag)
{
	int	j;

	j = 0;
	while (message[j] != '\0')
	{
		write(1, &message[j], 1);
		j++;
	}
	write(1, "\n", 1);
	free(*pointer);
	*pointer = 0;
	*i = 0;
	*flag = 0;
}

static void	ft_rebuild_char(t_data *g_data, int signal, pid_t client_pid)
{
	if (signal == SIGUSR2)
		g_data->octet = (g_data->octet | 1 << g_data->current_bit);
	if (g_data->current_bit == 7)
	{
		g_data->message[g_data->i] = g_data->octet;
		g_data->i++;
		g_data->current_bit = 0;
		if (g_data->octet == '\0')
		{
			ft_print_and_reset(&g_data->message, g_data->message, &g_data->i, \
					&g_data->flag);
			kill(client_pid, SIGUSR2);
		}
		g_data->octet = 0;
		return ;
	}
	g_data->current_bit++;
}

static void	ft_rebuild_string(int signal, siginfo_t *info, void *prev_context)
{
	static t_data	g_data;
	pid_t			client_pid;

	(void)prev_context;
	client_pid = 0;
	client_pid = info->si_pid;
	if (g_data.flag == 0)
		ft_rebuild_strlen(&g_data, signal);
	else
	{
		ft_rebuild_char(&g_data, signal, client_pid);
	}
}

int	main(void)
{
	struct sigaction	newact;

	ft_printf("The ID of the parent process (pid) is %d\n", getpid());
	newact.sa_sigaction = ft_rebuild_string;
	newact.sa_flags = SA_RESTART;
	sigaction(SIGUSR1, &newact, NULL);
	sigaction(SIGUSR2, &newact, NULL);
	while (1)
		pause();
}
