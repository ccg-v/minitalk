/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 23:00:43 by ccarrace          #+#    #+#             */
/*   Updated: 2023/02/03 20:18:08 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>	// SIGUSR1, SIGUSR2
# include <unistd.h>	// getpid(), pause(), usleep()
# include <stdio.h>		// printf()
# include <unistd.h>	// write(()

	typedef	struct	s_server
	{
		int		flag;
		char	octet;
		int		current_bit;
	}				t_server;

	t_server	g_server;

#endif

