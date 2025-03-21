/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcotonea <mcotonea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 18:08:52 by mmilliot          #+#    #+#             */
/*   Updated: 2025/03/21 14:39:54 by mcotonea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static void	attribute_cmd_or_arg(t_token *current, bool *one_cmd_in_pipe)
{
	if (current->token == PIPE)
		*one_cmd_in_pipe = false;
	if (current->token != OTHER)
		return ;
	if (current->prev == NULL)
	{
		current->token = CMD;
		*one_cmd_in_pipe = true;
		return ;
	}
	if (*one_cmd_in_pipe == false && (current->prev->token < 1 || current->prev->token > 4))
	{
		current->token = CMD;
		*one_cmd_in_pipe = true;
		return ;
	}
	if ((current->prev->token >=1 && current->prev->token <= 4)
		|| current->prev->token == CMD || current->prev->token == ARG)
	{
		current->token = ARG;
		return ;
	}
	return ;
}

/* 
	cmd_or_arg = Function for decide if a node is a cmd or an arg :
	- attribute_cmd_or_arg = Function for decide if a node is a cmd or an arg
*/

static void	cmd_or_arg(t_data *data)
{
	t_token	*current;
	bool	one_cmd_in_pipe;
	
	one_cmd_in_pipe = false;
	current = data->lst_token;
	while (current != NULL)
	{
		attribute_cmd_or_arg(current, &one_cmd_in_pipe);
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

int	tokenization(t_data *data)
{
	if (cut_the_line(data) == -1)
		return (-1);
	ft_gettype(data);
	cmd_or_arg(data);
	check_dollars(data);
	if (check_pipes(data) == -1)
		return (-1);
	if (check_rafter(data) == -1)
		return (-1);
	return (0);
}
