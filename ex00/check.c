/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scamlett <scamlett@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 12:14:15 by scamlett          #+#    #+#             */
/*   Updated: 2026/03/14 12:13:15 by scamlett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush-01.h"

int	contar_visibles(int linea[SIZE])
{
	int	i;
	int	maximo;
	int	visibles;

	i = 0;
	visibles = 0;
	maximo = 0;
	while (i < SIZE)
	{
		if (linea[i] > maximo)
		{
			maximo = linea[i];
			visibles++;
		}
		i++;
	}
	return (visibles);
}

static void	rellenar_linea(int tablero[SIZE][SIZE], int linea[SIZE], int i,
		int modo)
{
	int	j;

	j = 0;
	while (j < SIZE)
	{
		if (modo == 0)
			linea[j] = tablero[j][i];
		else if (modo == 1)
			linea[j] = tablero[SIZE - 1 - j][i];
		else if (modo == 2)
			linea[j] = tablero[i][j];
		else
			linea[j] = tablero[i][SIZE - 1 - j];
		j++;
	}
}

int	comprobar_vistas(int tablero[SIZE][SIZE], int *pistas)
{
	int	i;
	int	linea[SIZE];

	i = 0;
	while (i < SIZE)
	{
		rellenar_linea(tablero, linea, i, 0);
		if (contar_visibles(linea) != pistas[i])
			return (0);
		rellenar_linea(tablero, linea, i, 1);
		if (contar_visibles(linea) != pistas[SIZE + i])
			return (0);
		rellenar_linea(tablero, linea, i, 2);
		if (contar_visibles(linea) != pistas[(SIZE * 2) + i])
			return (0);
		rellenar_linea(tablero, linea, i, 3);
		if (contar_visibles(linea) != pistas[(SIZE * 3) + i])
			return (0);
		i++;
	}
	return (1);
}

void	imprimir_tablero(int tablero[SIZE][SIZE])
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
			c = tablero[i][j] + '0';
			write(1, &c, 1);
			if (j < SIZE - 1)
				write(1, " ", 1);
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
}
