/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush-01.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scamlett <scamlett@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 11:56:10 by scamlett          #+#    #+#             */
/*   Updated: 2026/03/14 13:05:41 by scamlett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush-01.h"

static int	esta_en_linea(int tablero[SIZE][SIZE], int indice, int valor,
		int es_fila)
{
	int	i;

	i = 0;
	while (i < SIZE)
	{
		if (es_fila && tablero[indice][i] == valor)
			return (1);
		if (!es_fila && tablero[i][indice] == valor)
			return (1);
		i++;
	}
	return (0);
}

static int	resolver_celda(int tablero[SIZE][SIZE], int *pistas, int posicion)
{
	int	fila;
	int	columna;
	int	valor;

	if (posicion == SIZE * SIZE)
		return (comprobar_vistas(tablero, pistas));
	fila = posicion / SIZE;
	columna = posicion % SIZE;
	valor = 1;
	while (valor <= SIZE)
	{
		if (!esta_en_linea(tablero, fila, valor, 1) && !esta_en_linea(tablero,
				columna, valor, 0))
		{
			tablero[fila][columna] = valor;
			if (resolver_celda(tablero, pistas, posicion + 1))
				return (1);
			tablero[fila][columna] = 0;
		}
		valor++;
	}
	return (0);
}

static int	parsear(char *texto, int *pistas)
{
	int	i;
	int	contador;

	i = 0;
	contador = 0;
	while (texto[i])
	{
		if (texto[i] >= '1' && texto[i] <= '4')
		{
			if (contador >= SIZE * 4)
				return (0);
			pistas[contador] = texto[i] - '0';
			contador++;
		}
		else if (texto[i] != ' ')
			return (0);
		i++;
	}
	return (contador == SIZE * 4);
}

static int	resolver(int tablero[SIZE][SIZE], int *pistas)
{
	int	fila;
	int	columna;

	fila = 0;
	while (fila < SIZE)
	{
		columna = 0;
		while (columna < SIZE)
		{
			tablero[fila][columna] = 0;
			columna++;
		}
		fila++;
	}
	return (resolver_celda(tablero, pistas, 0));
}

int	main(int cantidad_args, char *argumentos[])
{
	int	pistas[SIZE * 4];
	int	tablero[SIZE][SIZE];

	if (cantidad_args != 2)
	{
		write(1, "Error\n", 6);
		return (1);
	}
	if (!parsear(argumentos[1], pistas))
	{
		write(1, "Error\n", 6);
		return (1);
	}
	if (!resolver(tablero, pistas))
	{
		write(1, "Error\n", 6);
		return (1);
	}
	imprimir_tablero(tablero);
	return (0);
}
