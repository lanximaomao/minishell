#include "builtin.h"
#include "executor.h"
#include "minishell.h"

int		g_exitcode = 0;

int	main(int argc, char **argv, char **env)
{
	t_mini	*mini;

	if (argc != 1 || argv[1])
		ft_error("Wrong input!", FUNC, 0);
	mini = malloc(sizeof(t_mini) * 1);
	if (!mini)
		ft_error("malloc fail.\n", 1, 0);
	env_init(mini, env);
	readline_prompt(mini);
	//free_char((char *)mini); // why?
	ft_lstfree(mini->env);
	free(mini);
	return (0);
}

/* why the ECHOCTL is turned off after the while loop? */
int	readline_prompt(t_mini *mini)
{
	char			*line;
	struct termios	t;

	line = NULL;
	//ascii_art_pattern();
	while (1)
	{
		signal(SIGINT, handle_signal);
		signal(SIGQUIT, SIG_IGN);
		tcgetattr(0, &t);
		t.c_lflag &= ~ECHOCTL;
		tcsetattr(0, TCSANOW, &t);
		line = readline("\033[32m\U0001F40C Minishell \033[31m$\033[0;39m ");
		if (!line)
			exit_with_empty_line("exit\n", 0);
		add_history(line);
		minishell(mini, line);
	}
	tcgetattr(0, &t);
	t.c_lflag |= ECHOCTL;
	tcsetattr(0, TCSANOW, &t);
	rl_clear_history();
	return (0);
}

void	minishell(t_mini *mini, char *line)
{
	int		i;
	int		size;
	t_list	*line_lst;

	line_lst = NULL;
	line_lst = get_linelst(line, line_lst, -1);
	free(line);
	line = NULL;
	if (line_lst == NULL)//lin
		return ; //lin
	if (validator(line_lst) == -1)//lin
		return ; //lin
	if (handle_args_expand(line_lst, mini->env) == -1)
		return ;
	mini->cmd_lst = parse_cmds(line_lst, mini->env);
	ft_lstfree(line_lst);
	signal(SIGQUIT, handle_cmd);
	signal(SIGINT, handle_cmd);
	size = ft_lstsize(mini->cmd_lst);
	if (size == 0)
		return ;
	executor(mini, size);
}

void	ascii_art_pattern(void)
{
	printf("\n\n*********************************************************");
	printf("\n*                                                       *");
	printf("\n*               Enter Minishell's Charm!                *");
	printf("\n*                                                       *");
	printf("\n*********************************************************\n\n");
}

void	exit_with_empty_line(char *msg, int exit_code)
{
	ft_putstr_fd(msg, 0);
	g_exitcode = exit_code;
	exit(g_exitcode);
}
