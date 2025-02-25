/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:56:54 by mmilliot          #+#    #+#             */
/*   Updated: 2024/11/25 12:13:13 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*source;
	unsigned char	*destination;

	if (!dest || !src)
		return (NULL);
	source = (unsigned char *)src;
	destination = (unsigned char *)dest;
	if (destination < source)
	{
		while (n > 0)
		{
			*destination++ = *source++;
			n--;
		}
	}
	else if (source < destination)
	{
		while (n > 0)
		{
			destination[n - 1] = source[n - 1];
			n--;
		}
	}
	return (dest);
}
