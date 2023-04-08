/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 18:01:31 by ccarrace          #+#    #+#             */
/*   Updated: 2022/06/26 21:48:49 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* LIBRARY <string.h>
 *
 * DESCRIPTION
 * Writes 'len' bytes of value 'c' (converted to an UNSIGNED CHAR) to string 'b'
 *
 * RETURN VALUES
 * Returns its first argument
 *
 * COMMENTS
 * Writes 'c' value 'len' times at the beginning of string 'b'. Returns the 
 * string 'b' with changes made.
 */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		((unsigned char *)b)[i] = c;
		i++;
	}
	return (b);
}
