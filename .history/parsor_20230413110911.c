#include "minishell.h"

void parser(char *line)
{
	int i = 0;
	int count = 0;
	t_input	line_input;

	if (line == NULL)
		return ;
	if (ft_strnstr(line, "&&", ft_strlen(line)) || ft_strnstr(line, "||", ft_strlen(line)))
	{
		ft_printf("\033[1;31mError\n\033[0m: %s\n", "&& or || is handled in BONUS PART\n");
		return ;
	}
	line_input->temp_cmd = ft_split(line, '|');
	
	// while (line_input->temp_cmd[i++])
	// 	count++;


	free(line_split);


}

// < infile ls -l | wc -l > outfile