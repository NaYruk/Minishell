/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 19:40:02 by mmilliot          #+#    #+#             */
/*   Updated: 2024/11/25 12:12:23 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include <stdint.h>

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*buff;

	if (count * size / size != count)
		return (NULL);
	buff = (unsigned char *)malloc(count * size);
	if (!buff)
		return (NULL);
	ft_bzero(buff, (count * size));
	return ((void *)buff);
}
