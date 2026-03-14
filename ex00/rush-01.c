/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush-01.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scamlett <scamlett@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 10:29:26 by scamlett          #+#    #+#             */
/*   Updated: 2026/03/14 11:12:31 by scamlett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#define SIZE 4

int	main(int argc, char *argv[])
{
	int	clues[SIZE * 4];
	int	board[SIZE][SIZE];

	if (argc != 2)
	{
		write(1, "Error\n", 6);
		return (1);
	}
	if (!parse_input(argv[1], clues))
	{
		write(1, "Error\n", 6);
		return (1);
	}
	if (!solve(board, clues))
	{
		write(1, "Error\n", 6);
		return (1);
	}
	print_board(board);
	return (0);
}

int	parse_input(char *str, int *clues)
{
	int	i;

	i = 0;
	while (i < SIZE * 4)
	{
		if (str[i * 2] < '1' || str[i * 2] > '4')
			return (0);
		clues[i] = str[i * 2] - '0';
		if (i * 2 + 1 < SIZE * 8 - 1 && str[i * 2 + 1] != ' ')
			return (0);
		i++;
	}
	return (1);
}

void	print_board(int board[SIZE][SIZE])
{
	int		i;
	int		j;
	char	c;

	i = 0;
	while (i < SIZE)
	{
		j = 0;
		while (j < SIZE)
		{
			c = board[i][j] + '0';
			write(1, &c, 1);
			if (j < SIZE - 1)
				write(1, " ", 1);
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
}
