#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <fcntl.h>

char	**ft_split(char *s, char c);
void	freemalloc(char **strs);
size_t	ft_strlen(const char *str);
char	*ft_strjoin(char *s1, char *s2);

#endif