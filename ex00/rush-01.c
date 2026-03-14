/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush-01.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scamlett <scamlett@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 11:56:10 by scamlett          #+#    #+#             */
/*   Updated: 2026/03/14 14:09:33 by scamlett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int		comprobar_vistas(int tablero[4][4], int *pistas);
void	imprimir_tablero(int tablero[4][4]);

int	esta_en_linea(int tablero[4][4], int indice, int valor, int es_fila)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (es_fila && tablero[indice][i] == valor)
			return (1);
		if (!es_fila && tablero[i][indice] == valor)
			return (1);
		i++;
	}
	return (0);
}

int	resolver_celda(int tablero[4][4], int *pistas, int posicion)
{
	int	fila;
	int	columna;
	int	valor;

	if (posicion == 4 * 4)
		return (comprobar_vistas(tablero, pistas));
	fila = posicion / 4;
	columna = posicion % 4;
	valor = 1;
	while (valor <= 4)
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

int	parsear(char *texto, int *pistas)
{
	int	i;
	int	contador;

	i = 0;
	contador = 0;
	while (texto[i])
	{
		if (texto[i] >= '1' && texto[i] <= '4')
		{
			if (contador >= 4 * 4)
				return (0);
			pistas[contador] = texto[i] - '0';
			contador++;
		}
		else if (texto[i] != ' ')
			return (0);
		i++;
	}
	return (contador == 4 * 4);
}

int	resolver(int tablero[4][4], int *pistas)
{
	int	fila;
	int	columna;

	fila = 0;
	while (fila < 4)
	{
		columna = 0;
		while (columna < 4)
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
	int	pistas[4 * 4];
	int	tablero[4][4];

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
