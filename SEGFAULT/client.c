/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 20:36:36 by ccarrace          #+#    #+#             */
/*   Updated: 2023/02/13 20:55:01 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

//int	len;

int	ft_strlen(char *s)
{
	int	len;

	len = 0;
	while (s[len] != '\0')
		len++;
printf("len in CLIENT ft_strlen = %d\n", len);
	return (len);
}

static void	ft_send_strlen(int pid, int len)
{
	int	i;

	i = 0;;
printf("len in CLIENT ft_send_strlen = %d\n", len);
	while (i < 32)
	{
//		if (len & 1)
		if (0 != (len & 1 << i))
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
//		len = len >> 1;
		i++;
		usleep(100);
	}
}

static void	ft_send_signal(int pid, unsigned char octet)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if (0 != (octet & 1 << i))
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		usleep(200);
		i++;;
	}
}

int	main(int argc, char **argv)
{
	int	pid;
	int	len;
	char	*s;
	int	i;
//	t_struct	data;

	if (argc == 3)
	{
		pid = atoi(argv[1]);
		s = argv[2];
		len = ft_strlen(s);
		ft_send_strlen(pid, len);
		i = 0;
		while (s[i] != '\0')
		{
			ft_send_signal(pid, s[i]);
			i++;
		}
/*		while (*s)
		{
			ft_send_signal(pid, *s);
			s++;
		}
*/
		ft_send_signal(pid, '\n');
		ft_send_signal(pid, s[i]);
	}
	else
	{
		printf("No arguments or wrong arguments supplied!\n");
		printf("(Three parameters needed: executable name, ");
		printf("parent process ID (pid) and a string to send)\n");
	}
}
