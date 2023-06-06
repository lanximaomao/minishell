#include "builtin.h"
#include "executor.h"
#include "minishell.h"

int		g_exitcode = 0;

int	main(int argc, char **argv, char **env)
{
	t_mini	*mini;

	if (argc != 1 || argv[1])
		ft_error(" minishell: wrong input!", FUNC, 0);
	mini = malloc(sizeof(t_mini) * 1);
	if (!mini)
		ft_error(" minishell: malloc fail.\n", 1, 0);
	env_init(mini, env);
	readline_prompt(mini);
	free_lst_content(mini->env, 2);
	free(mini);
	mini = NULL;
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
		if (ft_strncmp(line, "", 1))
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
	int		size;
	t_list	*line_lst;
	t_list	*tmp;

	line_lst = NULL;
	line_lst = lexer_get_linelst(line, line_lst, -1);
	free_str(line);
	if (line_lst == NULL)
		return ;
	tmp = line_lst;
	if (validator(&tmp) == -1)
	{
		free_lst_content(tmp, 0);
		return ;
	}
	expander_args(line_lst, mini->env);
	mini->cmd_lst = parser_cmds(line_lst, mini->env);
	free_lst_content(line_lst, 0);
	signal(SIGQUIT, handle_cmd);
	signal(SIGINT, handle_cmd);
	size = ft_lstsize(mini->cmd_lst);
	if (size == 0)
		return ;
	executor(mini, size);
	free_lst_content(mini->cmd_lst, 1);
	remove_tmp_file(size);
}
