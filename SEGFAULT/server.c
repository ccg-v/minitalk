/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 22:54:34 by ccarrace          #+#    #+#             */
/*   Updated: 2023/02/08 23:26:59 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static  void    ft_rebuild_strlen(char **message, int *current_bit, int *flag, int signal)
{
	static int	message_len;

	message_len = 0;
	if (*current_bit < 32)
	{
		if (signal == SIGUSR2)
			message_len = (message_len | 1 << *current_bit);
		(*current_bit)++;
	}
	else
	{
		*flag  = 1;
		*message = calloc((message_len + 1), sizeof(char));
		*current_bit = 0;
		message_len = 0;
		return;
	}
}

static void	ft_print_message(char *message, int i)
{
	while (message[i] != 0)
	{
		write(1, &message[i], 1);
		i++;
	}
	write(1, "\n", 1);
	free(message);
}

static void    ft_rebuild_char(char **message, int *octet, int *current_bit, int *flag, int *i, int signal)
{
	if (signal == SIGUSR2)
		*octet = (*octet | 1 << *current_bit);
	if (*current_bit == 7)
 	{
 		*message[*i] = *octet;
		(*i)++;
 		*current_bit = 0;
		if (*octet == 0)
		{
			flag = 0;
            		ft_print_message(*message, *i);
			flag = 0;
			*message = 0;
			*i = 0;
		}
     		*octet = 0;
		return;
 	}
	(*current_bit)++;
}

static void	ft_rebuild_string(int signal)
{
	static int	octet;
	static int	current_bit;
	static int	flag;
	static int	i;
	static char	*message;

	octet = 0;
	current_bit = 0;
	flag = 0;
	i = 0;
	*message = 0;

	if (flag == 0)
		ft_rebuild_strlen(&message, &current_bit, &flag, signal);
	else
		ft_rebuild_char(&message, &octet, &current_bit, &flag, &i, signal);
}

int main(void)
{
	printf("The ID of the parent process (pid) is %d\n", getpid());
	signal(SIGUSR1, ft_rebuild_string);
	signal(SIGUSR2, ft_rebuild_string);
	while (1)
		pause();
}