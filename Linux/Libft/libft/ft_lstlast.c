/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 00:21:02 by mmilliot          #+#    #+#             */
/*   Updated: 2024/11/25 12:12:57 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	int	i;

	if (!lst)
		return (0);
	i = ft_lstsize(lst);
	while (i > 1)
	{
		lst = lst->next;
		i--;
	}
	return (lst);
}
