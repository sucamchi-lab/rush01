/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scamlett <scamlett@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 12:14:15 by scamlett          #+#    #+#             */
/*   Updated: 2026/03/14 12:03:08 by scamlett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush-01.h"

int	count_visible(int line[SIZE])
{
	int	i;
	int	max;
	int	visible;

	i = 0;
	visible = 0;
	max = 0;
	while (i < SIZE)
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

static void	fill_line(int board[SIZE][SIZE], int line[SIZE], int i, int mode)
{
	int	j;

	j = 0;
	while (j < SIZE)
	{
		if (mode == 0)
			line[j] = board[j][i];
		else if (mode == 1)
			line[j] = board[SIZE - 1 - j][i];
		else if (mode == 2)
			line[j] = board[i][j];
		else
			line[j] = board[i][SIZE - 1 - j];
		j++;
	}
}

int	check_views(int board[SIZE][SIZE], int *clues)
{
	int	i;
	int	line[SIZE];

	i = 0;
	while (i < SIZE)
	{
		fill_line(board, line, i, 0);
		if (count_visible(line) != clues[i])
			return (0);
		fill_line(board, line, i, 1);
		if (count_visible(line) != clues[SIZE + i])
			return (0);
		fill_line(board, line, i, 2);
		if (count_visible(line) != clues[(SIZE * 2) + i])
			return (0);
		fill_line(board, line, i, 3);
		if (count_visible(line) != clues[(SIZE * 3) + i])
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
