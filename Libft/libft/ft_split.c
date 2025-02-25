/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 18:38:37 by mmilliot          #+#    #+#             */
/*   Updated: 2024/11/25 12:13:27 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	count_word(char const *str, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		while (str[i] == c)
			i++;
		if (str[i] != c && str[i] != '\0')
			count++;
		while (str[i] != c && str[i] != '\0')
			i++;
	}
	return (count);
}

static char	*ft_strndup(const char *src, size_t count)
{
	char	*dest;
	size_t	i;

	i = 0;
	dest = (char *)malloc(sizeof(char) * (count + 1));
	if (!dest)
		return (NULL);
	while (i < count)
	{
		dest[i] = src[i];
		i++;
	}
	dest[count] = '\0';
	return (dest);
}

static char	**free_all(char **str, size_t k)
{
	while (k > 0)
	{
		free(str[k - 1]);
		k--;
	}
	free(str);
	return (NULL);
}

static size_t	get_start(char const *s, size_t *i, char c)
{
	size_t	start;

	start = 0;
	while (s[*i] == c)
		(*i)++;
	start = *i;
	while (s[*i] != c && s[*i] != '\0')
		(*i)++;
	return (start);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	size_t	i;
	size_t	k;
	size_t	start;

	if (!s)
		return (NULL);
	i = 0;
	k = 0;
	str = (char **)malloc(sizeof(char *) * (count_word(s, c) + 1));
	if (!str)
		return (NULL);
	while (s[i] != '\0')
	{
		start = get_start(s, &i, c);
		if (i > start)
		{
			str[k] = ft_strndup(s + start, i - start);
			if (!str[k])
				return (free_all(str, k));
			k++;
		}
	}
	str[k] = NULL;
	return (str);
}
