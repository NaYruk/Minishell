/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 18:08:52 by mmilliot          #+#    #+#             */
/*   Updated: 2025/03/11 00:40:07 by mmilliot         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/minishell.h"

/* 
   This function assigns a type (int) to each token in the list
   Missing infiles, outfiles and differentiating arg from cmd
   all this is managed in cmd_or_arg
*/

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

/* 
	attribute_cmd_or_arg = Function for decide if a node is a CMD or an ARG
	- if a token is not OTHER, he is already define.
	- if the prev is NULL, it is the head of the list so the token is CMD
	- if the prev is everything except |, it is ARG
	- as long as there are no pipes all tokens will be ARG
	- If the previous token is a PIPE, the next token is a CMD
*/

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
	else if (current->prev->token == ARG && current->prev->prev->token == INFILE)
		current->token = CMD;
	else if (current->prev->token == ARG)
		current->token = ARG;
	else if (current->prev->token == PIPE)
		current->token = CMD;
	return ;
}

/* 
	cmd_or_arg = Function for decide if a node is a cmd or an arg :
	- attribute_cmd_or_arg = Function for decide if a node is a cmd or an arg
*/

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

/* 
	main Function for the tokenisation !
	- cut_the_line = Function for Cut the line in token :
		arg, cmd, and, or, pipe, outfile, append, infile, heredoc
	- ft_gettype = Function for attribute the token to each
		node create in the cut_the_line function.
	- cmd_or_arg = Function for decide if a node is a cmd or an arg
	- check_pipes = Verify the position of each | and find any error.
	- check_rafter =  Verify the position of each <,<<,>>,> and find any error.
*/

void	tokenization(t_data *data)
{
	data->exit_status = 0;
	if (cut_the_line(data) == -1)
		return ;
	ft_gettype(data);
	cmd_or_arg(data);
	if (check_pipes(data) == -1)
		return ;
	if (check_rafter(data) == -1)
		return ;
}
