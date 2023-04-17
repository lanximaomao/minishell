#include "minishell.h"

t_list	*segment_split_token(char *segment)
{
	t_list *token;
	size_t	i = 0;
	size_t	len = 0;

	while (*segment)
	{
		if (*str != ' ')
		{
			len = 0;
			while (*str != ' ' && *str && ++len)
				str++;
			str_arr[i++] = ft_substr(s - len, 0, len);
		}
		else
			s++;
	}
	token[i] = 0;
	return (token);
}