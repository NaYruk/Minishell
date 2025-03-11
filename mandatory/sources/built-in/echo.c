/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 14:23:30 by mcotonea          #+#    #+#             */
/*   Updated: 2025/03/10 15:06:30 by mmilliot         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/minishell.h"

static int	check_option(char *str)
{
	int	i;
	
	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
	
}

char	*extract_value(t_data *data, char *name)
{
	char	*value;
	int		i;
	int		len;
	
	i = 0;
	len = ft_strlen(name);
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], name, len) == 0)
		{
			value = ft_strdup(data->env[i] + len + 1);
			add_g_c_node(data, &data->g_c, (void **)value, false);
			return (value);
		}
		i++;
	}
	return (NULL);
}

int	check_dollar(char *str)
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

int	ft_echo(t_data *data)
{
	t_token *tmp;

	tmp = data->lst_token;
	if (!tmp->next)
		return (printf("\n"), EXIT_SUCCESS);
	if (tmp->next->token == ARG && check_option(tmp->next->line) == 1)
	{
		tmp = tmp->next;
		while (tmp->next && tmp->next->token == ARG)
		{
			printf("%s", tmp->next->line);
			tmp = tmp->next;
			if (tmp->next && tmp->next->token == ARG)
				printf(" ");
		}
		return (EXIT_SUCCESS);
	}
	else if (tmp->next->token == ARG)
	{
		while (tmp->next && tmp->next->token == ARG)
		{
			printf("%s", tmp->next->line);
			tmp = tmp->next;
			if (tmp->next && tmp->next->token == ARG)
				printf(" ");
		}
		printf("\n");
		return (EXIT_SUCCESS);
	}
	else
		return (EXIT_FAILURE);
}

