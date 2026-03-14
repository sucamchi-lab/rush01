/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush-01.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scamlett <scamlett@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 11:56:10 by scamlett          #+#    #+#             */
/*   Updated: 2026/03/14 12:08:43 by scamlett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush-01.h"

static int	in_line(int board[SIZE][SIZE], int idx, int val, int is_row)
{
	int	i;

	i = 0;
	while (i < SIZE)
	{
		if (is_row && board[idx][i] == val)
			return (1);
		if (!is_row && board[i][idx] == val)
			return (1);
		i++;
	}
	return (0);
}

static int	solve_cell(int board[SIZE][SIZE], int *clues, int pos)
{
	int	row;
	int	col;
	int	val;

	if (pos == SIZE * SIZE)
		return (check_views(board, clues));
	row = pos / SIZE;
	col = pos % SIZE;
	val = 1;
	while (val <= SIZE)
	{
		if (!in_line(board, row, val, 1) && !in_line(board, col, val, 0))
		{
			board[row][col] = val;
			if (solve_cell(board, clues, pos + 1))
				return (1);
			board[row][col] = 0;
		}
		val++;
	}
	return (0);
}

int	parse(char *str, int *clues)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] >= '1' && str[i] <= '4')
		{
			if (count >= SIZE * 4)
				return (0);
			clues[count] = str[i] - '0';
			count++;
		}
		else if (str[i] != ' ')
			return (0);
		i++;
	}
	return (count == SIZE * 4);
}

int	solve(int board[SIZE][SIZE], int *clues)
{
	int	row;
	int	col;

	row = 0;
	while (row < SIZE)
	{
		col = 0;
		while (col < SIZE)
		{
			board[row][col] = 0;
			col++;
		}
		row++;
	}
	return (solve_cell(board, clues, 0));
}

int	main(int argc, char *argv[])
{
	int	clues[SIZE * 4];
	int	board[SIZE][SIZE];

	if (argc != 2)
	{
		write(1, "Error\n", 6);
		return (1);
	}
	if (!parse(argv[1], clues))
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
