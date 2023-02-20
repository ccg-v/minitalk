/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 22:54:34 by ccarrace          #+#    #+#             */
/*   Updated: 2023/02/15 21:25:42 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	ft_rebuild_strlen(char **message, int *current_bit, int *flag, \
		int signal)
{
	int	message_len;

	message_len = 0;
	if (signal == SIGUSR2)
		message_len = (message_len | 1 << *current_bit);
	if (*current_bit == 31)
	{
		*flag = 1;
		*message = calloc((message_len + 1), sizeof(char));
		*current_bit = 0;
		message_len = 0;
		return ;
	}
	(*current_bit)++;
}

static void	ft_print_and_reset(char **pointer, char *message, int *i, int *flag)
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

static void	ft_rebuild_string(int signal)
{
	static int	octet;
	static int	current_bit;
	static int	flag;
	static int	i;
	static char	*message;

	if (flag == 0)
		ft_rebuild_strlen(&message, &current_bit, &flag, signal);
	else
	{
		if (signal == SIGUSR2)
			octet = (octet | 1 << current_bit);
		if (current_bit == 7)
		{
			message[i] = octet;
			i++;
			current_bit = 0;
			if (octet == 0)
				ft_print_and_reset(&message, message, &i, &flag);
			octet = 0;
			return;
		}
		current_bit++;
	}
}

int main(void)
{
	printf("The ID of the parent process (pid) is %d\n", getpid());
	signal(SIGUSR1, ft_rebuild_string);
	signal(SIGUSR2, ft_rebuild_string);
	while (1)
		pause();
}
