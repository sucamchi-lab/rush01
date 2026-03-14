/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scamlett <scamlett@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 12:14:15 by scamlett          #+#    #+#             */
/*   Updated: 2026/03/14 14:09:48 by scamlett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	contar_visibles(int linea[4])
{
	int	i;
	int	maximo;
	int	visibles;

	i = 0;
	visibles = 0;
	maximo = 0;
	while (i < 4)
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

void	rellenar_linea(int tablero[4][4], int linea[4], int i, int modo)
{
	int	j;

	j = 0;
	while (j < 4)
	{
		if (modo == 0)
			linea[j] = tablero[j][i];
		else if (modo == 1)
			linea[j] = tablero[4 - 1 - j][i];
		else if (modo == 2)
			linea[j] = tablero[i][j];
		else
			linea[j] = tablero[i][4 - 1 - j];
		j++;
	}
}

int	comprobar_vistas(int tablero[4][4], int *pistas)
{
	int	i;
	int	linea[4];

	i = 0;
	while (i < 4)
	{
		rellenar_linea(tablero, linea, i, 0);
		if (contar_visibles(linea) != pistas[i])
			return (0);
		rellenar_linea(tablero, linea, i, 1);
		if (contar_visibles(linea) != pistas[4 + i])
			return (0);
		rellenar_linea(tablero, linea, i, 2);
		if (contar_visibles(linea) != pistas[(4 * 2) + i])
			return (0);
		rellenar_linea(tablero, linea, i, 3);
		if (contar_visibles(linea) != pistas[(4 * 3) + i])
			return (0);
		i++;
	}
	return (1);
}

void	imprimir_tablero(int tablero[4][4])
{
	int		fila;
	int		columna;
	char	c;

	fila = 0;
	while (fila < 4)
	{
		columna = 0;
		while (columna < 4)
		{
			c = tablero[fila][columna] + '0';
			write(1, &c, 1);
			if (columna < 4 - 1)
				write(1, " ", 1);
			columna++;
		}
		write(1, "\n", 1);
		fila++;
	}
}
