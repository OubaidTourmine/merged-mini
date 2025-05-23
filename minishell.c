#include "minishell.h"

void	get_input(t_data *data)
{
	char	*line;

	track_ptr(line = readline("minishell: "), data);
	if (!line)
	{	
		free_memory(data);
		clear_history();
		exit(0);
	}
	else if (line[0])
		add_history(line);
	if (tokenize_input(line, data))
		return ;
	// print_tokens(data->tokens);
	if (process_heredocs(data))
	return ;
	report_redirect_errors(data);
	parse_commands(data);
	
}

int	main(int ac, char **av, char **env)
{
	t_data	data;
	(void)ac;
	(void)av;
	setup_signals();
	ft_memset(&data, 0, sizeof(t_data));
	while (1)
	{
		get_input(&data);
		execution_pars(env, &data);
		free_memory(&data);
	}
}
