#include "minishell.h"

void handle_quote()
{

}


t_list *get_linelst(char *line)
{
	t_list *line_lst = NULL;
	t_list *node;
	char *temp_line;
	int i = 0;
	int j = 0;
	int len = 0;
	int count_quote = 0;
	int count_dquote = 0;

	if (line == NULL)
		return ;
	if (ft_strnstr(line, "&&", ft_strlen(line)) || ft_strnstr(line, "||", ft_strlen(line)))
	{
		ft_printf("\033[1;31mError\n\033[0m: %s\n", "&& or || is handled in BONUS PART\n");
		return ;
	}
	while (*line)
	{
		i = 0;
		if (*line != ' ')
		{
			len = 0;
			while (*line != ' ' && *line && ++len)
				line++;
			temp_line[i] = ft_substr(line - len, 0, len);
			if (!temp_line)
			{
				ft_printf("\033[1;31mError\n\033[0m: %s\n", "Malloc failed\n");
				return (NULL);
			}
			i++;
			node = ft_lstnew(temp_line);
			if (!line_lst)
			{
				ft_printf("\033[1;31mError\n\033[0m: %s\n", "Malloc failed\n");
				return (NULL);
			}

				ft_lstadd_back(&line_lst, node);
		} else
			line++;
	}
	line_lst[i] = NULL;
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
	return (line_lst);
}
