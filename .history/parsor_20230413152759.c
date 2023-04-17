#include "minishell.h"



char **get_tokens(char *line)
{
	int i = 0;
	int j = 0;
	int len = 0;
	int count_quote = 0;
	int count_dquote = 0;
	t_input	*line_input;
	t_list node;

	if (line == NULL)
		return ;
	if (ft_strnstr(line, "&&", ft_strlen(line)) || ft_strnstr(line, "||", ft_strlen(line)))
	{
		ft_printf("\033[1;31mError\n\033[0m: %s\n", "&& or || is handled in BONUS PART\n");
		return ;
	}
	count_quote = count_char(line, '\'');
	count_dquote = count_char(line, '\"');
	line_input->cmd_segment = ft_split(line, '|');
	// for count the num_cmd
	// while (line_input->cmd_segment[i++])
	// 	count++;
	while (line_input->cmd_segment[i])
	{
		line_input->*cmd_tokens = ft_split_lexer(line_input->cmd_segment[i]);
		if (node )
		line_inputcmd_tokens++;
		i++;
		// for count the num_cmd
		// while (line_input->cmd_tokens[i++])
		// 	count++;
	}


	free_p2p(line_input->cmd_segment);
	return (line_input->cmd_tokens);
}

t_token *parse_tokens(char **line_input->cmd_tokens)
{
	int i = 0;
	int fd = 0;
	t_token *token;

	while (line_input->cmd_tokens[i])
	{
		if (line_input->cmd_tokens[i] == "<")
		{
			token->*infile++ = line_input->cmd_tokens[i + 1];
			// if ((fd = open(line_input->cmd_tokens[i + 1], O_RDONLY)) == -1)
			// 	error("Open the input file of redirection failed!\n", 1);
			// dup2(fd, STDIN_FILENO);
			i++;
		} else if (line_input->cmd_tokens[i] == ">")
		{
			token->*outfile++ = line_input->cmd_tokens[i + 1];
			i++;
		} else if (line_input->cmd_tokens[i] == "<<")
		{

		} else if (line_input->cmd_tokens[i] == ">>")
		{
			sign_out = 1;

		}
		i++;
	}
	return (token);
}
// < infile 'ls' "-l" | wc -l > outfile
