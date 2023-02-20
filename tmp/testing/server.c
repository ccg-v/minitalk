/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 22:54:34 by ccarrace          #+#    #+#             */
/*   Updated: 2023/02/20 22:16:33 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	ft_rebuild_strlen(t_data *data,	int signal)
{
	int	message_len;

	message_len = 0;
	if (signal == SIGUSR2)
		message_len = (message_len | 1 << data->current_bit);
	if (data->current_bit == 31)
	{
		data->flag = 1;
		data->message = calloc((message_len + 1), sizeof(char));
		data->current_bit = 0;
		message_len = 0;
		return ;
	}
	(data->current_bit)++;
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

static void	ft_rebuild_char(t_data *data, int signal)
{
	if (signal == SIGUSR2)
		data->octet = (data->octet | 1 << data->current_bit);
	if (data->current_bit == 7)
	{
		data->message[data->i] = data->octet;
		data->i++;
		data->current_bit = 0;
		if (data->octet == '\0')
			ft_print_and_reset(&data->message, data->message, &data->i, \
					&data->flag);
		data->octet = 0;
		return ;
	}
	data->current_bit++;
}

static void	ft_rebuild_string(int signal)
{
	static t_data	data;

	if (data.flag == 0)
		ft_rebuild_strlen(&data, signal);
	else
	{
		ft_rebuild_char(&data, signal);
	}
}

int	main(void)
{
	printf("The ID of the parent process (pid) is %d\n", getpid());
	signal(SIGUSR1, ft_rebuild_string);
	signal(SIGUSR2, ft_rebuild_string);
	while (1)
		pause();
}
