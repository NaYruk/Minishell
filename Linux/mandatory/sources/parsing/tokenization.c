/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 18:08:52 by mmilliot          #+#    #+#             */
/*   Updated: 2025/04/19 00:22:54 by mmilliot         ###   ########.fr       */
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
		if (current->quote_char == '\0')
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
			else
				current->token = OTHER;
		}
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
	if (*one_cmd_in_pipe == false
		&& (current->prev->token < 1 || current->prev->token > 4))
	{
		current->token = CMD;
		*one_cmd_in_pipe = true;
		return ;
	}
	if ((current->prev->token >= 1 && current->prev->token <= 4)
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

int	check_pipes_and_rafter(t_data *data)
{
	t_token	*current;

	current = data->lst_token;
	while (current != NULL)
	{
		if (check_pipes(data, current) == -1)
			return (-1);
		if (check_rafter(data, current) == -1)
			return (-1);
		current = current->next;
	}
	return (0);
}

/*
** tokenization:
** - This is the main function for tokenizing
**		the input prompt into meaningful components.
** - It first validates the quotes in the input to ensure proper syntax.
** - Replaces environment variables and special characters like `$` and `~`.
** - Splits the input into tokens such as commands, arguments, pipes,
**		and redirections.
** - Assigns a type to each token (e.g., CMD, ARG, PIPE, INFILE, OUTFILE).
** - Checks for syntax errors related to pipes (`|`)
**		and redirections (`<`, `>`, etc.).
** - Returns 0 on success or -1 if any error is encountered during tokenization
*/

int	tokenization(t_data *data)
{
	if (check_quotes(data, data->prompt) == -1)
		return (-1);
	replace_dollars(data, &data->prompt);
	if (check_quotes(data, data->prompt) == -1)
		return (-1);
	if (cut_the_line(data) == -1 || data->lst_token == NULL)
		return (-1);
	ft_gettype(data);
	cmd_or_arg(data);
	if (check_pipes_and_rafter(data) == -1)
		return (-1);
	return (0);
}
