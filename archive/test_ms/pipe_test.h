# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>

char    **ft_split(char const *s, char c);
char    *ft_strdup(const char *s1);
char    *ft_strjoin(char const *s1, char const *s2);
