/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42malaga.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 12:14:15 by scamlett          #+#    #+#             */
/*   Updated: 2026/03/14 15:12:44 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush-01.h"

static int	contar_visibles(int linea[SIZE])
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
			linea[j] = tablero[j][i]; // rellena de arriba a abajo
		else if (modo == 1)
			linea[j] = tablero[SIZE - 1 - j][i]; //rellena de abajo a arriba
		else if (modo == 2)
			linea[j] = tablero[i][j]; //rellena de izquierda a derecha
		else
			linea[j] = tablero[i][SIZE - 1 - j]; //rellena de derecha a izquierda
		j++;
	}
}

int	comprobar_vistas(int tablero[SIZE][SIZE], int *pistas)
{
	int	i;
	int	linea[SIZE]; //linea auxiliar que guarda los valores del tablero

	i = 0;
	while (i < SIZE)
	{
		rellenar_linea(tablero, linea, i, 0); //rellena columnas de arriba a abajo
		if (contar_visibles(linea) != pistas[i]) //comprueba que el numero de pista sea = al visible en la linea auxiliar
			return (0);
		rellenar_linea(tablero, linea, i, 1); //rellena columnas de abajo a arriba
		if (contar_visibles(linea) != pistas[SIZE + i])
			return (0);
		rellenar_linea(tablero, linea, i, 2); //rellena filas de izquierda a derecha
		if (contar_visibles(linea) != pistas[(SIZE * 2) + i])
			return (0);
		rellenar_linea(tablero, linea, i, 3); //rellena la linea de derecha a izquierda
		if (contar_visibles(linea) != pistas[(SIZE * 3) + i])
			return (0);
		i++;
	}
	return (1);
}

void	imprimir_tablero(int tablero[SIZE][SIZE])
{
	int		fila;
	int		columna;
	char	c;

	fila = 0;
	while (fila < SIZE)
	{
		columna = 0;
		while (columna < SIZE)
		{
			c = tablero[fila][columna] + '0';
			write(1, &c, 1);
			if (columna < SIZE - 1)
				write(1, " ", 1);
			columna++;
		}
		write(1, "\n", 1);
		fila++;
	}
}
