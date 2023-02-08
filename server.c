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

//extern int    len;

static  void    ft_rebuild_strlen(int sig, char **str, int *len)
{

	if (sig == SIGUSR2)
         *len = (*len | 1 << data.current_bit);
    data.current_bit++;
printf("len from ft_rebuild_STRLEN = %d\n", *len);
    if (data.current_bit == 32)
    {
		*str = malloc((*len + 1) * sizeof(char));
		data.current_bit = 0;
		*len = 0;
 		}
	}

void    ft_rebuild_char(int sig)
{
	t_struct    data;
	char        *str;
	int     i;

	i = 0;
	str = NULL;
//  if (data.flag != 1)
//  {
//      data.flag = 1;
//      data.octet = 0;
//      data.current_bit = 0;
//  }
//  if (!data.len || data.len == 0)
//      ft_rebuild_strlen(sig, &str);
	if (data.flag != 1)
	{
		ft_rebuild_strlen(sig, &str, &data.len);
		data.flag = 1;
 		data.len = 0;
 		data.octet = 0;
		data.current_bit = 0;
 	}
	else
 	{
printf("data.flag = %d\n", data.flag);
printf("data.len from ft_rebuild_CHAR = %d\n", data.len);
 		if (sig == SIGUSR2)
 			data.octet = (data.octet | 1 << data.current_bit);
 		data.current_bit++;
 		if (data.current_bit == 8)
 		{
 			str[i++] = data.octet;
 			data.current_bit = 0;
			if (data.octet == 0)
			{
 				while (*str != '\0')
				{
					write(1, &*str, 1);
					str++;
				}
				write(1, "\n", 1);
				free(str);
				*str = 0;
//              return (ft_display_string(&data.len, &str, &i));
			}			
     		data.octet = 0;
 		}
 	}
}

int main(void)
{
printf("The ID of the parent process (pid) is %d\n", getpid());
	signal(SIGUSR1, ft_rebuild_char);
	signal(SIGUSR2, ft_rebuild_char);
	while (1)
		pause();
 	return (0);
 }
