/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scamlett <scamlett@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 12:14:15 by scamlett          #+#    #+#             */
/*   Updated: 2026/03/14 18:47:29 by scamlett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#define TOP_TO_BOTTOM 0
#define BOTTOM_TO_TOP 1
#define LEFT_TO_RIGHT 2
#define RIGHT_TO_LEFT 3

int	count_visible_elements(int line[4])
{
	int	i;
	int	max;
	int	visible;

	i = 0;
	visible = 0;
	max = 0;
	while (i < 4)
	{
		if (line[i] > max)
		{
			max = line[i];
			visible++;
		}
		i++;
	}
	return (visible);
}

void	fill_line(int board[4][4], int line[4], int i, int mode)
{
	int	j;

	j = 0;
	while (j < 4)
	{
		if (mode == TOP_TO_BOTTOM)
			line[j] = board[j][i];
		else if (mode == BOTTOM_TO_TOP)
			line[j] = board[4 - 1 - j][i];
		else if (mode == LEFT_TO_RIGHT)
			line[j] = board[i][j];
		else if (mode == RIGHT_TO_LEFT)
			line[j] = board[i][4 - 1 - j];
		j++;
	}
}

int	check_view(int board[4][4], int *clues)
{
	int	i;
	int	line[4];

	i = 0;
	while (i < 4)
	{
		fill_line(board, line, i, TOP_TO_BOTTOM);
		if (count_visible_elements(line) != clues[i])
			return (0);
		fill_line(board, line, i, BOTTOM_TO_TOP);
		if (count_visible_elements(line) != clues[4 + i])
			return (0);
		fill_line(board, line, i, LEFT_TO_RIGHT);
		if (count_visible_elements(line) != clues[(4 * 2) + i])
			return (0);
		fill_line(board, line, i, RIGHT_TO_LEFT);
		if (count_visible_elements(line) != clues[(4 * 3) + i])
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
