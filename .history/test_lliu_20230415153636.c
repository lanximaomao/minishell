#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (*needle && !len)
		return (NULL);
	if (*needle == 0)
		return ((char *)haystack);
	while (haystack[i] && i < len)
	{
		j = 0;
		while (haystack[i + j] == needle[j] && (i + j) < len)
		{
			if (needle[j + 1] == '\0')
				return ((char *)haystack + i);
			j++;
		}
		i++;
	}
	return (0);
}

int main(int argc, char **argv) {
	int i = 0;
	char *line = readline("minishell$ ");
	add_history(line);
	printf("You entered: %s\n", line);

	return 0;
}

#include <unistd.h>
#include <stdio.h>
#include <errno.h>

int main() {
    if(chdir("/home/user/Documents") == -1) {
        perror("chdir");
        return errno;
    }
    printf("Current working directory is: %s\n", getcwd(NULL, 0));
    return 0;
}
