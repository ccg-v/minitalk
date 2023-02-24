/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 22:27:29 by ccarrace          #+#    #+#             */
/*   Updated: 2023/02/25 00:14:09 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

/* External functions called:
 *  -	From <stdlib.h>:	free()
 *  -	From <unistd.h>:	getpid(), pause(), usleep(), write()
 *  -	From <signal.h>:	SIGUSER1, SIGUSER2
 * 	-	From "libft.h" :	ft_strlen(), ft_calloc(), ft_atoi()
 * 	-	From "printf.h":	ft_printf()
*/
//H
//
# include <stdio.h>	// printf()
# include <stdlib.h>
# include <signal.h>	
# include <unistd.h>
# include "libft/libft.h"

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
