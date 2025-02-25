/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 18:11:09 by mmilliot          #+#    #+#             */
/*   Updated: 2024/11/25 12:12:49 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	if (!lst || !(*del))
		return ;
	while (*lst != NULL)
	{
		temp = (*lst)->next;
		del((void *)(*lst)->content);
		free (*lst);
		*lst = temp;
	}
	*lst = NULL;
}
