#include "minishell.h"



t_list **get_linelst(char *line)
{
	t_list **line_lst;
	t_list *node;
	char *temp_line;
	int i = 0;
	int j = 0;
	int len = 0;
	int count_quote = 0;
	int count_dquote = 0;
	t_input	*line_input;

	if (line == NULL)
		return ;
	if (ft_strnstr(line, "&&", ft_strlen(line)) || ft_strnstr(line, "||", ft_strlen(line)))
	{
		ft_printf("\033[1;31mError\n\033[0m: %s\n", "&& or || is handled in BONUS PART\n");
		return ;
	}
	if (!(line_lst = (t_list **)malloc(sizeof(t_list *))))
	{
		ft_printf("\033[1;31mError\n\033[0m: %s\n", "Malloc failed\n");
		return (NULL);
	}
	line_input = (t_input *)malloc(sizeof(t_input));
	if (!line_input)
	{
		ft_printf("\033[1;31mError\n\033[0m: %s\n", "Malloc failed\n");
		return (NULL);
	}
	line_input->cmd_segments = NULL;
	line_input->cmd_tokens = NULL;
	i = 0;





	line_input->cmd_segments = ft_split(line, '|');
	// for count the num_cmd
	// while (line_input->cmd_segment[i++])
	// 	count++;
	while (line_input->cmd_segments[i])
	{
		line_input->*cmd_tokens = segment_split_token(line_input->cmd_segments[i], count_quote, count_dquote);
		if (!line_input->*cmd_tokens)
			return (NULL);
		line_input->cmd_tokens++;
		i++;
		// for count the num_cmd
		// while (line_input->cmd_tokens[i++])
		// 	count++;
	}


	free_p2p(line_input->cmd_segments);
	return (line);
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