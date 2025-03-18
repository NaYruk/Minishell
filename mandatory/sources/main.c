/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:17:55 by mcotonea          #+#    #+#             */
/*   Updated: 2025/03/18 15:18:07 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_list(t_data *data)
{
	t_token *current = data->lst_token;
	
	while (current != NULL)
	{
		printf("%s, %d, %d\n", current->line, current->token, current->status);
		current = current->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	(void)argv;
	if (argc != 1)
	{
		ft_putstr_fd("Error ! nbr of arguments != 1\n", 2);
		exit(EXIT_FAILURE);
	}
	data = init_all(envp);
	while (1)
	{
		sig_handler();
		data->prompt = readline("SegfaultBros> ");
		if (!data->prompt)
			break ;
		if (data->prompt[0] != '\0')
		{
			add_history(data->prompt);
			tokenization(data);
			execution(data);
		}
		//print_list(data);
		free(data->prompt);
		free_token(data);
	}
	if (isatty(STDIN_FILENO))
		ft_putstr_fd("exit\n", 2);
	return (free_garbage(data), 0);
}
