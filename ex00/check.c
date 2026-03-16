/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lupin <lupin@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 12:14:15 by scamlett          #+#    #+#             */
/*   Updated: 2026/03/15 19:32:39 by lupin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#define TOP_TO_BOTTOM 0
#define BOTTOM_TO_TOP 1
#define LEFT_TO_RIGHT 2
#define RIGHT_TO_LEFT 3

int	count_visible_line(int board[4][4], int index, int mode)
{
	int	j;
	int	value;
	int	max;
	int	visible;

	j = -1;
	visible = 0;
	max = 0;
	while (++j < 4)
	{
		if (mode == TOP_TO_BOTTOM)
			value = board[j][index];
		else if (mode == BOTTOM_TO_TOP)
			value = board[4 - 1 - j][index];
		else if (mode == LEFT_TO_RIGHT)
			value = board[index][j];
		else
			value = board[index][4 - 1 - j];
		if (value > max)
		{
			max = value;
			visible++;
		}
	}
	return (visible);
}

int	check_board(int board[4][4], int *clues)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (count_visible_line(board, i, TOP_TO_BOTTOM) != clues[i])
			return (0);
		if (count_visible_line(board, i, BOTTOM_TO_TOP) != clues[4 + i])
			return (0);
		if (count_visible_line(board, i, LEFT_TO_RIGHT) != clues[(4 * 2) + i])
			return (0);
		if (count_visible_line(board, i, RIGHT_TO_LEFT) != clues[(4 * 3) + i])
			return (0);
		i++;
	}
	return (1);
}

void	print_board(int board[4][4])
{
	int		row;
	int		column;
	char	c;

	row = 0;
	while (row < 4)
	{
		column = 0;
		while (column < 4)
		{
			c = board[row][column] + '0';
			write(1, &c, 1);
			if (column < 3)
				write(1, " ", 1);
			column++;
		}
		write(1, "\n", 1);
		row++;
	}
}
