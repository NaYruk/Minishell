/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcotonea <mcotonea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 18:08:52 by mmilliot          #+#    #+#             */
/*   Updated: 2025/03/04 17:03:17 by mcotonea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* This function assigns a type (int) to each token in the list
   Missing infiles, outfiles and differentiating arg from cmd */

static void	ft_gettype(t_data *data)
{
	t_token	*current;

	current = data->lst_token;
	while (current)
	{
		if (ft_strcmp(current->line, "|") == 0)
			current->token = PIPE;
		else if (ft_strcmp(current->line, "<") == 0)
			current->token = INFILE;
		else if (ft_strcmp(current->line, ">") == 0)
			current->token = OUTFILE;
		else if (ft_strcmp(current->line, "<<") == 0)
			current->token = HEREDOC;
		else if (ft_strcmp(current->line, ">>") == 0)
			current->token = APPEND;
		else if (ft_strcmp(current->line, "&&") == 0)
			current->token = AND;
		else if (ft_strcmp(current->line, "||") == 0)
			current->token = OR;
		else
			current->token = OTHER;
		current = current->next;
	}
	return ;
}

static void	attribute_cmd_or_arg(t_token *current)
{
	if (current->token != OTHER)
		return ;
	if (current->token == OTHER && current->prev == NULL)
		current->token = CMD;
	else if (current->prev->token == INFILE || current->prev->token == OUTFILE
		|| current->prev->token == HEREDOC || current->prev->token == APPEND
		|| current->prev->token == CMD)
		current->token = ARG;
	else if (current->prev->token == ARG)
		current->token = ARG;
	else if (current->prev->token == PIPE)
		current->token = CMD;
	return ;
}

static void	cmd_or_arg(t_data *data)
{
	t_token	*current;

	current = data->lst_token;
	while (current != NULL)
	{
		attribute_cmd_or_arg(current);
		current = current->next;
	}
	return ;
}

/* It is the main Function for the tokenisation !*/

void	tokenization(t_data *data)
{
	cut_the_line(data);
	ft_gettype(data);
	cmd_or_arg(data);
	return ;
}
