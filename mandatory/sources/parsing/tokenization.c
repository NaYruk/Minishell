/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melvin <melvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 18:08:52 by mmilliot          #+#    #+#             */
/*   Updated: 2025/03/03 15:34:31 by melvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


/* This function assigns a type (int) to each token in the list
   Missing infiles, outfiles and differentiating arg from cmd */

static void	ft_gettype(t_data *data)
{
	t_token *current;

	current = data->lst_token;
	while (current)
	{
		if (ft_strcmp(current->line, "|") == 0)
			current->token = PIPE;
		else if ((ft_strcmp(current->line, "<") == 0) ||
			(ft_strcmp(current->line, ">") == 0))
			current->token = REDIR;
		else if (ft_strcmp(current->line, "<<") == 0)
			current->token = HEREDOC;
		else if (ft_strcmp(current->line, ">>") == 0)
			current->token = APPEND;
		else if (ft_strcmp(current->line, "&&") == 0)
			current->token = AND;
		else if (ft_strcmp(current->line, "||") == 0)
			current->token = OR;
		else
			current->token = CMD;
		current = current->next;
	}
	return ;
}

/* It is the main Function for the tokenisation !*/

void	tokenization(t_data *data)
{
	cut_the_line(data);
	ft_gettype(data);
	return ;
}
