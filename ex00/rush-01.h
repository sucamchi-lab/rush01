/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush-01.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scamlett <scamlett@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 11:50:34 by scamlett          #+#    #+#             */
/*   Updated: 2026/03/14 12:02:22 by scamlett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#define SIZE 4

int		parse(char *str, int *clues);
int		count_visible(int line[SIZE]);
int		check_views(int board[SIZE][SIZE], int *clues);
void	print_board(int board[SIZE][SIZE]);
int		solve(int board[SIZE][SIZE], int *clues);
