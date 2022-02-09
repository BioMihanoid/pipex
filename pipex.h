#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

char	**get_paths(char **envp);
void	free_cmd_and_paths(char **s1, char **s2);

#endif
