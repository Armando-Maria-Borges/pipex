/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aborges <aborges@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 08:39:25 by aborges           #+#    #+#             */
/*   Updated: 2024/07/17 11:29:30 by aborges          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_cmd(char *cmd)
{
	char	*args[4];

	args[0] = "/bin/sh";
	args[1] = "-c";
	args[2] = cmd;
	args[3] = NULL;
	execve("/bin/sh", args, NULL);
	perror("Falha ao executar o comando");
	exit(1);
}

void	new_process1(int file1, int pipefd[2], char *cmd1)
{
	pid_t	pid1;

	pid1 = fork();
	if (pid1 == -1)
	{
		perror("Erro ao criar o processo");
		close_files(file1, -1, pipefd);
		exit(1);
	}
	if (pid1 == 0)
	{
		dup2(file1, STDIN_FILENO);
		close(file1);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		execute_cmd(cmd1);
	}
}

void	new_process2(int file2, int pipefd[2], char *cmd2)
{
	pid_t	pid2;

	pid2 = fork();
	if (pid2 == -1)
	{
		perror("Erro ao criar o processo");
		close_files(-1, file2, pipefd);
		exit(1);
	}
	if (pid2 == 0)
	{
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		dup2(file2, STDOUT_FILENO);
		close(file2);
		execute_cmd(cmd2);
	}
}

int	main(int argc, char *argv[])
{
	int	file1;
	int	file2;
	int	pipefd[2];

	if (argc != 5 || (!argv[1][0] || !argv[2][0] || !argv[3][0] || !argv[4][0]))
	{
		ft_message(argv[0]);
		return (1);
	}
	file1 = open_file(argv[1], O_RDONLY, 0);
	if (file1)
		file2 = open_file(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file2 < 0)
		close(file1);
	if (pipe(pipefd) == -1)
	{
		perror("Erro na criar o pipe");
		close_files(file1, file2, pipefd);
		return (1);
	}
	new_process1(file1, pipefd, argv[2]);
	new_process2(file2, pipefd, argv[3]);
	close_files(file1, file2, pipefd);
	return (0);
}
