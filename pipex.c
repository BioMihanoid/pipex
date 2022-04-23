/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmilan <gmilan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 14:30:21 by gmilan            #+#    #+#             */
/*   Updated: 2022/03/15 18:58:12 by gmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec(char *cmd, char **envp)
{
	char	**cmd_parse;
	char	**paths;
	char	*this_path;
	int		i;

	cmd_parse = ft_split (cmd, ' ');
	paths = get_paths(envp);
	if (paths == NULL)
		ft_perror("Error (no PATH)");
	i = 0;
	while (paths[i])
	{
		this_path = ft_strjoin(paths[i], "/");
		this_path = ft_strjoin(this_path, cmd_parse[0]);
		if (access(this_path, F_OK) == 0)
		{
			if (execve(this_path, cmd_parse, NULL) == -1)
				ft_perror("Error");
		}
		free(this_path);
		i++;
	}
	free_cmd_and_paths(paths, cmd_parse);
	ft_perror("Error");
}

void	child_one_process(int *fd, char **argv, char **envp)
{
	int	fd_in;

	fd_in = open (argv[1], O_RDONLY);
	if (fd_in < 0)
		ft_perror("Error (input file)");
	if (dup2(fd[1], 1) == -1)
		ft_perror("Error");
	close(fd[0]);
	if (dup2(fd_in, 0) == -1)
		ft_perror("Error");
	exec(argv[2], envp);
}

void	child_two_process(int *fd, char **argv, char **envp)
{
	int	fd_out;

	fd_out = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd_out < 0)
		ft_perror("Error (output file)");
	if (dup2(fd[0], 0) == -1)
		ft_perror("Error");
	close(fd[1]);
	if (dup2(fd_out, 1) == -1)
		ft_perror("Error");
	exec(argv[3], envp);
}

void	pipex(char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (pipe(fd) == -1)
		ft_perror("Error");
	pid1 = fork();
	if (pid1 < 0)
		ft_perror("Error");
	if (pid1 == 0)
		child_one_process(fd, argv, envp);
	pid2 = fork();
	if (pid2 < 0)
		ft_perror("Error");
	if (pid2 == 0)
		child_two_process(fd, argv, envp);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

int	main(int argc, char **argv, char **envp)
{
	if (argc != 5)
	{
		write (1, "Usage : ./pipex infile cmd1 cmd2 outfile\n", 41);
		return (0);
	}
	pipex(argv, envp);
	return (0);
}
