#include "minishell.h"

void parser(char *line)
{
	int i = 0;
	int count = 0;
	char *line_split = NULL;

	if (line == NULL)
		return ;
	while (line[0] == '\0')
		return ;
	line_split = ft_split(line, '|');
	while (line_split[i])
	{
		if (line_split[i] == NULL)
			break;
		count++;
		i++;
	}


	free(line_split);


}

// < infile ls -l | wc -l > outfile
