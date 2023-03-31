/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 22:27:29 by ccarrace          #+#    #+#             */
/*   Updated: 2023/03/30 22:22:22 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

/* 		
  		External functions called:
		-	From <stdlib.h>		:	free()
  		-	From <unistd.h>		:	getpid(), pause(), usleep(), write()
  		-	From <signal.h>		:	SIGUSR1, SIGUSR2
 		-	From "libft.h" 		:	ft_strlen(), ft_calloc(), ft_atoi(),
									ft_isdigit(), ft_putstr_fd(), ft_putnbr_fd()
*/

# include <stdlib.h>
# include <signal.h>	
# include <unistd.h>
# include "libft.h"

# define RED		"\033[0;31m"
# define GREEN 		"\033[0;32m"
# define B_WHITE	"\033[1;37m"
# define DEF_COLOR	"\033[0m"

typedef struct s_data
{
	char	*string;
	int		string_len;
	int		octet;
	int		current_bit;
	int		i;
	int		flag;
}			t_data;

t_data		g_data;

#endif
