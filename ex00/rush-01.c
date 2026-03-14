/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush-01.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scamlett <scamlett@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 11:56:10 by scamlett          #+#    #+#             */
/*   Updated: 2026/03/14 18:37:06 by scamlett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int		check_view(int board[4][4], int *clues);
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

int	solve_cell(int board[4][4], int *clues, int position)
{
	int	row;
	int	column;
	int	value;

	if (position == 4 * 4)
		return (check_view(board, clues));
	row = position / 4;
	column = position % 4;
	value = 1;
	while (value <= 4)
	{
		if (!is_value_in_line(board, row, value, 1) && !is_value_in_line(board,
				column, value, 0))
		{
			board[row][column] = value;
			if (solve_cell(board, clues, position + 1))
				return (1);
			board[row][column] = 0;
		}
		value++;
	}
	return (0);
}

int	solve(int board[4][4], int *clues)
{
	int	position;

	position = 0;
	while (position < 4 * 4)
	{
		board[position / 4][position % 4] = 0;
		position++;
	}
	return (solve_cell(board, clues, 0));
}

int	parse(char *text, int *clues)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (text[i])
	{
		if (text[i] >= '1' && text[i] <= '4')
		{
			if (counter >= 4 * 4)
				return (0);
			clues[counter] = text[i] - '0';
			counter++;
		}
		else if (text[i] != ' ')
			return (0);
		i++;
	}
	return (counter == 4 * 4);
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
	if (!solve(board, clues))
	{
		write(1, "Error\n", 6);
		return (1);
	}
	print_board(board);
	return (0);
}
