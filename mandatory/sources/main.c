/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcotonea <mcotonea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:17:55 by mcotonea          #+#    #+#             */
/*   Updated: 2025/03/04 17:09:04 by mcotonea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_list(t_data *data)
{
	t_token *current = data->lst_token;
	
	while (current != NULL)
	{
		printf("%s, %d\n", current->line, current->token);
		current = current->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	(void)argv;
	(void)envp;
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
			write_history("history.txt");
			tokenization(data);
		}
		free(data->prompt);
	}
	print_list(data);
	if (isatty(STDIN_FILENO))
		ft_putstr_fd("exit\n", 2);
	return (rl_clear_history(), free_garbage(data), 0);
}

/* 
int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)envp;
	(void)argv;

	t_data *data = init_all(envp);
	data->prompt = "echo \"Marc insane ton gc\" >> file.txt";
	cut_the_line(data);
	print_list(data);
	free_garbage(data);
} */