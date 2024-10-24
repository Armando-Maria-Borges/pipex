/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aborges <aborges@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 13:09:10 by aborges           #+#    #+#             */
/*   Updated: 2024/07/16 17:45:23 by aborges          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_file(const char *filename, int flags, mode_t mode)
{
	int	fd;

	fd = open(filename, flags, mode);
	if (fd < 0)
		perror("Erro ao abrir o arquivo");
	return (fd);
}

void	close_files(int file1, int file2, int pipefd[2])
{
	close(file1);
	close(file2);
	close(pipefd[0]);
	close(pipefd[1]);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_message(char *str)
{
	char	*green;
	char	*blue;
	char	*yellow;
	char	*reset;
	char	*red;

	red = "\033[1;31m";
	green = "\033[1;32m";
	blue = "\033[1;34m";
	yellow = "\033[1;33m";
	reset = "\033[0m";
	write(1, yellow, ft_strlen(green));
	write(1, "Forma de execução:  ", 20);
	write(1, reset, ft_strlen(reset));
	write(1, red, ft_strlen(blue));
	write(1, str, ft_strlen(str));
	write(1, reset, ft_strlen(reset));
	write(1, green, ft_strlen(yellow));
	write(1, " <file1> <cmd1> <cmd2> <file2>\n", 31);
	write(1, reset, ft_strlen(reset));
}
