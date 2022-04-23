/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmilan <gmilan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 14:36:02 by gmilan            #+#    #+#             */
/*   Updated: 2022/03/15 18:58:12 by gmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

char	**get_paths(char **envp);
void	free_cmd_and_paths(char **s1, char **s2);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
void	ft_perror(char *str);
int		ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);

#endif
