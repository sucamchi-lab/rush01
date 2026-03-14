/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scamlett <scamlett@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 12:14:15 by scamlett          #+#    #+#             */
/*   Updated: 2026/03/14 17:28:26 by scamlett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

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
		if (mode == 0)
			line[j] = board[j][i];
		else if (mode == 1)
			line[j] = board[4 - 1 - j][i];
		else if (mode == 2)
			line[j] = board[i][j];
		else
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
		fill_line(board, line, i, 0);
		if (count_visible_elements(line) != clues[i])
			return (0);
		fill_line(board, line, i, 1);
		if (count_visible_elements(line) != clues[4 + i])
			return (0);
		fill_line(board, line, i, 2);
		if (count_visible_elements(line) != clues[(4 * 2) + i])
			return (0);
		fill_line(board, line, i, 3);
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
