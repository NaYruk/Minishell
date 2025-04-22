/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 20:24:49 by mmilliot          #+#    #+#             */
/*   Updated: 2024/11/25 12:14:00 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*ptr;
	int		count;

	if (!s)
		return (NULL);
	count = 0;
	ptr = (char *)s;
	while (*ptr != '\0')
	{
		ptr++;
		count++;
	}
	if (*ptr == (unsigned char)c)
		return (ptr);
	ptr--;
	while (count > 0 && *ptr != (unsigned char)c)
	{
		ptr--;
		count--;
	}
	if (*ptr == (unsigned char)c)
		return (ptr);
	return (NULL);
}
