/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:17:55 by mcotonea          #+#    #+#             */
/*   Updated: 2025/04/10 17:02:43 by mcotonea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_signal = 0;

void	print_list(t_data *data)
{
	t_token *current = data->lst_token;
	
	while (current != NULL)
	{
		printf("%s, %d, %c\n", current->line, current->token, current->quote_char);
		current = current->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data = NULL;

	(void)argv;
	if (argc != 1)
	{
		ft_putstr_fd("Error ! nbr of arguments != 1\n", 2);
		exit(EXIT_FAILURE);
	}
	data = init_all(envp);
	while (1)
	{
		setup_signals_interactive();
		data->prompt = readline("SegfaultBros> ");
		if (!data->prompt)
			break ;
		if (g_signal == SIGINT)
			update_exit_status(data);
		if (data->prompt[0] != '\0')
		{
			add_history(data->prompt);
			if (tokenization(data) == 0)
				execution(data);
		}
		//print_list(data);
		free(data->prompt);
		free_token(data);
	}
	if (isatty(STDIN_FILENO))
		ft_putstr_fd("exit\n", 2);
	return (free_garbage(data), data->exit_status);
}

/* int main(void)
{
	long long a = ft_atoll("-9223372036854775808");
	printf("%lld\n", a);
} */