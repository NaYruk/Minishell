/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 17:53:27 by mmilliot          #+#    #+#             */
/*   Updated: 2024/11/25 12:14:05 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	verify(const char *set, char c)
{
	int	i;

	i = 0;
	while (set[i] != 0)
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static size_t	ft_size(const char *s1, const char *set)
{
	size_t	start;
	size_t	end;
	size_t	i;

	i = 0;
	while (verify(set, s1[i]) == 1)
		i++;
	start = i;
	while (s1[i] != '\0')
		i++;
	while (verify(set, s1[i - 1]) == 1 && i > start)
		i--;
	end = i;
	return (end - start);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	size;
	size_t	i;
	size_t	j;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	j = 0;
	size = ft_size(s1, set);
	str = (char *)malloc(sizeof(char) * size + 1);
	if (!str)
		return (NULL);
	while (verify(set, s1[i]) == 1)
		i++;
	while (size > 0)
	{
		str[j] = s1[i];
		j++;
		i++;
		size--;
	}
	str[j] = '\0';
	return (str);
}
