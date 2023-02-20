/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 22:54:34 by ccarrace          #+#    #+#             */
/*   Updated: 2023/02/14 23:09:34 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_putendl_fd(char *s)
{
	int	i;

	i = 0;
	if (s == 0)
		return;
	while (s[i] != '\0')
	{
		write(1, &s[i], 1);
		i++;
	}
	write(1, "\n", 1);
}

static void	ft_rebuild_strlen(char **message, int *current_bit, int *flag, \
		int signal)
{
	static int	message_len;

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
/*
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
*/

static void	ft_restart_variables(int *flag, char **message, int *i)
{
	*flag = 0;
	if (message)
	{
		ft_putendl_fd(*message);
		free(*message);
		*message = 0;
	}
	*i = 0;
}

/*
static void	ft_rebuild_char(char **message, int *octet, int *current_bit, \
		int *flag, int *i, int signal)
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
			*message = 0;
			*i = 0;
		}
     		*octet = 0;
		return;
 	}
	(*current_bit)++;
}
*/
/*
static void ft_rebuild_char(char **message, int *octet, int *current_bit, \
		int *flag, int *i, int signal)
{
	if (signal == SIGUSR2)
		*octet = (*octet | 1 << *current_bit);
	if (*current_bit == 7)
	{
		*message[*i] = *octet;
		(*i)++;
		*current_bit = 0;
		if (*octet == 0)
			return (ft_restart_variables(flag, message, i));
		*octet = 0;
		return;
	}
	(*current_bit)++;
}
*/
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
//		ft_rebuild_char(&message, &octet, &current_bit, &flag, &i, signal);
	{
		if (signal == SIGUSR2)
			octet = (octet | 1 << current_bit);
		if (current_bit == 7)
		{
			message[i] = octet;
			i++;
			current_bit = 0;
			if (octet == 0)
				return (ft_restart_variables(&flag, &message, &i));
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
