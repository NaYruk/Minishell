/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_dollars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melvin <melvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:56:58 by mmilliot          #+#    #+#             */
/*   Updated: 2025/03/24 00:23:28 by melvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	dollar_presence(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

char	*get_expand_name(char *line, int *i)
{
	int		count;
	char	*name;

	name = NULL;
	count = *i;
	while (line[count] && (line[count] == '_' || ft_isalnum(line[count])))
		count++;
	name = ft_strndup(&(line[*i]), count - *i);
	*i = count;
	return (name);
}

char	*get_name(char *line, int *i)
{
	int		count;
	char	*name;
	
	count = *i;
	name = NULL;
	while (line[count] && (line[count] != '$'))
		count++;
	name = ft_strndup(&(line[*i]), count - *i);
	*i = count;
	return (name);
}

char	*parse_line(t_data *data, char *line)
{
	int		i;
	int		dollar_count;
	char	*name;
	char	*final_line;
	char	*value;
	char	*exit_status;
	
	i = 0;
	final_line = ft_strdup("");
	add_g_c_node(data, &data->g_c, (void **)final_line, false);
	value = NULL;
	exit_status = NULL;
	while(line[i] != '\0')
	{
		if (line[i] == '$')
		{
			dollar_count = 0;
			while (line[i] == '$')
			{
				dollar_count++;
				i++;
			}
			if (line[i] == '?' && dollar_count == 1)
			{
				exit_status = ft_itoa(data->exit_status);
				final_line = ft_strjoin(final_line, exit_status);
				free (exit_status);
				i++;
			}
			else
			{
				name = get_expand_name(line, &i);
				if (dollar_count % 2 == 1)
				{
					value = ft_getenv(data, name);
					if (value)
						final_line = ft_strjoin(final_line, value);
				}
				else
					final_line = ft_strjoin(final_line, name);
				free (name);
			}
		}
		else
		{
			name = get_name(line, &i);
			final_line = ft_strjoin(final_line, name);
			free(name);
		}

	}
	return (final_line);
}

void	check_dollars(t_data *data)
{
	t_token	*current;
	char	*new_token;
	
	new_token = NULL;
	current = data->lst_token;
	while (current != NULL)
	{
		if (dollar_presence(current->line))
		{
			new_token = parse_line(data, current->line);
			free(current->line);
			current->line = new_token;
		}
		current = current->next;
	}
}
