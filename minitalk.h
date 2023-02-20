/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 22:27:29 by ccarrace          #+#    #+#             */
/*   Updated: 2023/02/20 22:32:22 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

/* FUNCIONES A SUSTITUIR POR LAS MIAS PROPIAS
 	- PRINTF
	- ATOI
	- CALLOC
	- STRLEN
*/

# include <stdio.h>	// printf()
# include <stdlib.h>	// atoi(), calloc()
# include <signal.h>	// SIGUSR1, SIGUSR2
# include <unistd.h>	// write(), getpid(), pause(), usleep()

typedef struct s_data
{
	char	*message;
	int		octet;
	int		current_bit;
	int		i;
	int		flag;
}			t_data;

t_data		g_data;

#endif
