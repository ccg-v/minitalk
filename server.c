/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 22:54:34 by ccarrace          #+#    #+#             */
/*   Updated: 2023/03/16 13:30:54 by ccarrace         ###   ########.fr       */
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

static void	ft_rebuild_char(int signal)
{
	if (signal == SIGUSR2)
		g_data.octet = (g_data.octet | 1 << g_data.current_bit);
	if (g_data.current_bit == 7)
	{
		g_data.buffer[g_data.i] = g_data.octet;
		(g_data.i)++;
		g_data.current_bit = 0;
		if (g_data.octet == '\0')
			ft_print_and_reset();
		g_data.octet = 0;
		return ;
	}
	(g_data.current_bit)++;
}

static void	ft_rebuild_buffer(int signal)
{
	if (g_data.flag == 0)
		ft_rebuild_bufsize(signal);
	else
		ft_rebuild_char(signal);
	return ;
}

int	main(void)
{
	ft_printf("Server's pid is %d\n", getpid());
	signal(SIGUSR1, ft_rebuild_buffer);
	signal(SIGUSR2, ft_rebuild_buffer);
	while (1)
		pause();
}
