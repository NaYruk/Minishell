/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parsing_error.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:19:27 by mmilliot          #+#    #+#             */
/*   Updated: 2025/03/05 19:43:21 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	token_error(t_data *data, char *line)
{
	free_token(data);
	free_garbage(data);
	ft_putstr_fd(line, 2);
	exit(2);
}

static int	pipes_nbr(char *line, int nbr)
{
	int	i;
	
	nbr = 0;
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '|')
			nbr++;
		i++;
	}
	return (nbr);
}

static void check_first_and_last_node(t_token *token, t_data *data)
{
	int		nbr;
	
	nbr = 0;
	if (token->token == PIPE)
		token_error(data, "syntax error near unexpected token `|'\n");
	nbr = pipes_nbr(token->line, nbr);
	if (nbr >= 2 && token->status == 0)
		token_error(data, "syntax error near unexpected token `||'\n");
}

static void	check_pipes(t_data *data)
{
	t_token *current;
	int		nbr;
	
	nbr = 0;
	current = data->lst_token;
	check_first_and_last_node(current, data);
	while (current->next != NULL)
	{
		nbr = pipes_nbr(current->line, nbr);
		if (nbr > 1 && current->status == 0)
		{
			if (nbr == 2)
				token_error(data, "2 Pipes, we don't do bonus !\n");
			if (nbr == 3)
				token_error(data, "syntax error near unexpected token `|'\n");
			if (nbr >= 4)
				token_error(data, "syntax error near unexpected token `||'\n");
		}
		if (current->next->token == PIPE && current->token == PIPE)
			token_error(data, "syntax error near unexpected token `|'\n");
		current = current->next;
	}
	check_first_and_last_node(current, data);
	return ;
}

static int	rafter_nbr(char *line, int nbr)
{
	int	i;
	
	nbr = 0;
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '<' || line[i] == '>')
			nbr++;
		i++;
	}
	return (nbr);
}

static void	special_error(t_data *data, char *line, char *subline)
{
	ft_putstr_fd(line, 2);
	ft_putstr_fd("`", 2);
	ft_putstr_fd(subline, 2);
	ft_putstr_fd("'", 2);
	ft_putstr_fd("\n", 2);
	free_token(data);
	free_garbage(data);
	exit(2);
}

static void	check_rafter(t_data *data)
{
	t_token	*current;
	int		nbr;

	nbr = 0;
	current = data->lst_token;
	while (current != NULL)
	{
		if (current->status == 0 && current->token > OUTFILE)
		{
			nbr = rafter_nbr(current->line, nbr);
			if (nbr < 3 && nbr >= 1)
				token_error(data, "syntax error near unexpected token `newline'\n");
			if (current->line[0] == '<')
			{
				if (nbr == 3)
					token_error(data, "syntax error near unexpected token `newline'\n");
				else if (nbr == 4)
					token_error(data, "syntax error near unexpected token `<'\n");
				else if (nbr == 5)
					token_error(data, "syntax error near unexpected token `<<'\n");
				else if (nbr >= 6)
					token_error(data, "syntax error near unexpected token `<<<'\n");
			}
			else
			{
				if (nbr == 3)
					token_error(data, "syntax error near unexpected token `>'\n");
				else if (nbr >= 4)
					token_error(data, "syntax error near unexpected token `>>'\n");
			}
		}
		if (current->token >= HEREDOC && current->token <= OUTFILE)
		{
			if (current->next != NULL)
			{
					if (current->next->token != ARG)
						special_error(data, "syntax error near unexpected token ", current->next->line);
			}
			else
				token_error(data, "syntax error near unexpected token `newline'\n");
		}
		current = current->next;
	}
}

void	check_parsing_error(t_data *data)
{
	check_pipes(data);
	check_rafter(data);
}