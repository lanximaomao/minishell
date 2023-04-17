#include "minishell.h"

t_list *get_linelst(char *line)
{
	t_list *line_lst = NULL;
	t_list *node;
	int i;
	int len;
	t_input *input;

	if (line == NULL)
		return NULL;
	if (ft_strnstr(line, "&&", ft_strlen(line)) || ft_strnstr(line, "||", ft_strlen(line)))
	{
		ft_printf("\033[1;31mError\n\033[0m: %s\n", "&& or || is handled in BONUS PART\n");
		return NULL;
	}
	while (*line)
	{
		if (!(*line == ' ' || (*line > 8 && *line < 14)))
		{
			len = 0;
			if (*line == '\'' && (input->quote_type = 1))
			{
				while (*line != '\'' && *line && ++len)
					line++;
			} else if (*line == '\"' && (input->quote_type = 2))
			{
				while (*line != '\"' && *line && ++len)
					line++;
			} else {
				while (*line != ' ' && *line && ++len)
					line++;
			}
			if (!(input = (t_input *)malloc(sizeof(t_input))))
			{
				ft_printf("\033[1;31mError\n\033[0m: %s\n", "Malloc failed\n");
				return (NULL);
			}
			input->temp_line = ft_substr(line - len, 0, len);
			if (!input->temp_line)
			{
				ft_printf("\033[1;31mError\n\033[0m: %s\n", "Malloc failed\n");
				return (NULL);
			}
			node = ft_lstnew(input);
			if (!line_lst)
			{
				ft_printf("\033[1;31mError\n\033[0m: %s\n", "Malloc failed\n");
				return (NULL);
			}
			ft_lstadd_back(&line_lst, node);
			free_input(input);
			input = NULL;
		} else
			line++;
	}
	return (line_lst);
}

int main(int argc, char **argv)
{
	t_list *line_lst = NULL;

	line_lst = get_linelst(argv[1]);
	while (line_lst)
	{
		ft_printf("%s\n", line_lst->content->temp_line);
		ft_printf("%s\n", line_lst->content->quote_type);
		line_lst = line_lst->next;
	}

}
