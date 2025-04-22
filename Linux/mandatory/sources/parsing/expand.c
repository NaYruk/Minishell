/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 19:34:23 by mmilliot          #+#    #+#             */
/*   Updated: 2025/04/19 00:36:05 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** get_expand_line:
** - This function extracts the name of a variable
**		to be expanded from the input line.
** - It starts at the current index and continues until
**		a non-alphanumeric or non-underscore character is found.
** - Returns the extracted variable name as a newly allocated string.
** - Updates the index to point to the character after the variable name.
*/

char	*get_expand_line(t_data *data, char *line, int *i)
{
	int		count;
	char	*line_expand;

	line_expand = NULL;
	count = *i;
	while (line[count] && (line[count] == '_' || ft_isalnum(line[count])))
		count++;
	line_expand = ft_strndup(&(line[*i]), count - *i);
	if (!line_expand)
		malloc_error(data);
	*i = count;
	return (line_expand);
}

/*
** check_dollar_interrogation:
** - This function handles the special case of the
**		`$?` variable in the input prompt.
** - Expands `$?` to the exit status of the last executed command.
** - Appends the expanded value to the new_line buffer.
** - Returns 1 if `$?` is successfully processed, otherwise returns 0.
*/

int	check_dollar_interrogation(t_data *data, char **new_line, int *i)
{
	char	*after_expand;
	char	*old_line;

	after_expand = NULL;
	if (data->prompt[*i] == '?')
	{
		after_expand = ft_itoa(data->exit_status);
		old_line = *new_line;
		*new_line = ft_strjoin(old_line, after_expand);
		if (!(*new_line))
			malloc_error(data);
		free(old_line);
		free(after_expand);
		return (1);
	}
	return (0);
}

void	save_after_expand(t_data *data, char **new_line,
			char **after_expand, char **tmp)
{
	if (*after_expand)
	{
		*tmp = ft_strjoin(*new_line, *after_expand);
		if (!(*tmp))
			malloc_error(data);
		free (*new_line);
		*new_line = *tmp;
	}
}

/*
** expand_dollar:
** - This function handles the expansion of variables
**		prefixed by a dollar sign (`$`) in the input prompt.
** - It checks for special cases like `$?` to expand
**		the exit status of the last command.
** - Retrieves the value of environment variables
**		and appends it to the new_line buffer.
** - If the variable is not found, it appends nothing or the literal
**		`$` if no valid variable name follows.
** - SAVE_AFTER_EXPAND is the function for save in new_line the
** 		expand line.
*/

void	expand_dollar(t_data *data, char **new_line, char *prompt, int *i)
{
	char	*var_name;
	char	*after_expand;
	char	*tmp;

	var_name = NULL;
	after_expand = NULL;
	tmp = NULL;
	(*i)++;
	if (check_dollar_interrogation(data, new_line, i) == 1)
		return ;
	else if ((ft_isalnum(prompt[*i]) || prompt[*i] == '_'))
	{
		var_name = get_expand_line(data, prompt, i);
		after_expand = ft_getenv(data, var_name, NULL);
		save_after_expand(data, new_line, &after_expand, &tmp);
		free(var_name);
	}
	else if (prompt[*i] != DOUBLE_QUOTES)
		stock_char(data, new_line, '$');
	(*i)--;
}

/*
** expand_till:
** - This function handles the expansion of the tilde
**		(`~`) character in the input line.
** - If the tilde is at the start or preceded by a
**		space and followed by a space or `/`,
**   it expands to the value of the `HOME` environment variable.
** - If no valid `HOME` variable is found,
**		it sets the exit status to 0 and does nothing.
** - Otherwise, it appends the tilde or the expanded
**		value to the new_line buffer.
*/

int	expand_till(t_data *data, char **new_line, char *line, int *i)
{
	char	*home;
	char	*old_line;

	home = NULL;
	old_line = NULL;
	if ((line[*i + 1] == '\0' || (line[*i + 1] && (line[*i + 1] == ' '
					|| line[*i + 1] == '/')))
		&& ((*i > 0 && line[*i - 1] == ' ') || (*i == 0)))
	{
		home = ft_getenv(data, "HOME", false);
		if (!home)
		{
			data->exit_status = 0;
			return (0);
		}
		old_line = *new_line;
		*new_line = ft_strjoin(old_line, home);
		if (!(*new_line))
			malloc_error(data);
		free(old_line);
	}
	else
		stock_char(data, new_line, line[*i]);
	return (0);
}
