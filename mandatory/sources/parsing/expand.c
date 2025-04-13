/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcotonea <mcotonea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 19:34:23 by mmilliot          #+#    #+#             */
/*   Updated: 2025/04/13 16:28:11 by mcotonea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_expand_line(char *line, int *i)
{
	int		count;
	char	*line_expand;

	line_expand = NULL;
	count = *i;
	while (line[count] && (line[count] == '_' || ft_isalnum(line[count])))
		count++;
	line_expand = ft_strndup(&(line[*i]), count - *i);
	*i = count;
	return (line_expand);
}

int	check_dollar_interrogation(t_data *data, char **new_line, int *i)
{
	char	*after_expand;

	after_expand = NULL;
	if (data->prompt[*i] == '?')
	{
		after_expand = ft_itoa(data->exit_status);
		*new_line = ft_strjoin(*new_line, after_expand);
		free(after_expand);
		return (1);
	}
	return (0);
}

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
		var_name = get_expand_line(prompt, i);
		after_expand = ft_getenv(data, var_name, NULL);
		if (after_expand)
		{
			tmp = ft_strjoin(*new_line, after_expand);
			free (*new_line);
			*new_line = tmp;
		}
		free(var_name);
	}
	else if (prompt[*i] != DOUBLE_QUOTES)
		stock_char(new_line, '$');
	(*i)--;
}

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
		free(old_line);
	}
	else
		stock_char(new_line, line[*i]);
	return (0);
}
