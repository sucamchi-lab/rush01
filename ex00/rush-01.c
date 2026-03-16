/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush-01.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lupin <lupin@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 11:56:10 by scamlett          #+#    #+#             */
/*   Updated: 2026/03/15 19:33:42 by lupin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int		check_board(int board[4][4], int *clues);
void	print_board(int board[4][4]);

int	is_value_in_line(int board[4][4], int index, int value, int is_row)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (is_row && board[index][i] == value)
			return (1);
		if (!is_row && board[i][index] == value)
			return (1);
		i++;
	}
	return (0);
}

int	solve_cell(int board[4][4], int *clues, int cell)
{
	int	row;
	int	column;
	int	value;

	if (cell == 4 * 4)
		return (check_board(board, clues));
	row = cell / 4;
	column = cell % 4;
	value = 1;
	while (value <= 4)
	{
		if (!is_value_in_line(board, row, value, 1)
			&& !is_value_in_line(board, column, value, 0))
		{
			board[row][column] = value;
			if (solve_cell(board, clues, cell + 1))
				return (1);
			board[row][column] = 0;
		}
		value++;
	}
	return (0);
}

int	init(int board[4][4], int *clues)
{
	int	cell;

	cell = 0;
	while (cell < 4 * 4)
	{
		board[cell / 4][cell % 4] = 0;
		cell++;
	}
	return (solve_cell(board, clues, 0));
}

int	parse(char *text, int *clues)
{
	int	index;
	int	counter;

	index = 0;
	counter = 0;
	while (counter < 4 * 4)
	{
		if (text[index] < '1' || text[index] > '4')
			return (0);
		clues[counter] = text[index] - '0';
		counter++;
		index++;
		if (counter < 4 * 4)
		{
			if (text[index] != ' ')
				return (0);
			index++;
		}
	}
	return (text[index] == '\0');
}

int	main(int argc, char *argv[])
{
	int	clues[4 * 4];
	int	board[4][4];

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
	if (!init(board, clues))
	{
		write(1, "Error\n", 6);
		return (1);
	}
	print_board(board);
	return (0);
}
