/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 17:24:16 by mmilliot          #+#    #+#             */
/*   Updated: 2024/11/25 12:13:58 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	s;
	size_t	t;

	s = 0;
	if (*to_find == '\0')
		return ((char *)str);
	if (len == 0)
		return (NULL);
	if (to_find[s] == '\0')
		return ((char *)str);
	while (str[s])
	{
		t = 0;
		while (str[s + t] == to_find[t] && (s + t) < len)
		{
			if (str[s + t] == '\0' && to_find[t] == '\0')
				return ((char *)str + s);
			t++;
		}
		if (to_find[t] == '\0')
			return ((char *)str + s);
		s++;
	}
	return (0);
}
