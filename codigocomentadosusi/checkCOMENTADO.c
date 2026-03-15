/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkCOMENTADO.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scamlett <scamlett@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 12:14:15 by scamlett          #+#    #+#             */
/*   Updated: 2026/03/14 16:29:09 by scamlett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	contar_visibles(int linea[4])
{
	// Cuenta cuantos edificios son visibles recorriendo una linea en orden.
	int	i; // Indice para recorrer la linea de izquierda a derecha.
	int	maximo; // Altura maxima encontrada hasta el momento.
	int	visibles; // Numero de edificios visibles acumulados.

	i = 0; // Empezamos en el primer elemento de la linea.
	visibles = 0; // Al inicio no se ha contado ningun edificio visible.
	maximo = 0; // Al inicio no existe altura maxima observada.
	while (i < 4) // Recorremos los 4 edificios de la linea.
	{
		if (linea[i] > maximo) // Si la altura actual supera la maxima previa...
		{
			maximo = linea[i]; // Actualizamos la nueva altura maxima visible.
			visibles++; // Incrementamos el contador de edificios visibles.
		}
		i++; // Avanzamos al siguiente edificio de la linea.
	}
	return (visibles); // Devolvemos el total de edificios visibles en esta linea.
}

void	rellenar_linea(int tablero[4][4], int linea[4], int i, int modo)
{
	// Copia una fila o columna del tablero en el orden indicado por modo.
	int	j; // Indice para rellenar los 4 elementos del array linea.

	j = 0; // Empezamos escribiendo en la primera posicion de linea.
	while (j < 4) // Copiamos exactamente 4 valores segun el modo de lectura.
	{
		if (modo == 0) // Modo 0: columna i de arriba hacia abajo.
			linea[j] = tablero[j][i]; // Copiamos tablero[fila=j][columna=i].
		else if (modo == 1) // Modo 1: columna i de abajo hacia arriba.
			linea[j] = tablero[4 - 1 - j][i]; // Invertimos el indice de fila para leer al reves.
		else if (modo == 2) // Modo 2: fila i de izquierda a derecha.
			linea[j] = tablero[i][j]; // Copiamos tablero[fila=i][columna=j].
		else
			linea[j] = tablero[i][4 - 1 - j]; // Modo 3: fila i de derecha a izquierda.
		j++; 
	}
}

int	comprobar_vistas(int tablero[4][4], int *pistas)
{
	// Verifica que todas las vistas del tablero coincidan con las pistas.
	int	i; // Indice de la fila/columna que estamos comprobando.
	int	linea[4]; // Buffer temporal para evaluar visibilidad en una direccion.

	i = 0; // Empezamos comprobando la primera columna/fila.
	while (i < 4) // Repetimos las 4 comprobaciones para cada indice i.
	{
		rellenar_linea(tablero, linea, i, 0); // Construimos la columna i vista desde arriba.
		if (contar_visibles(linea) != pistas[i]) // Comparamos con la pista superior correspondiente.
			return (0); // Si falla una sola pista, el tablero no es valido.
		rellenar_linea(tablero, linea, i, 1); // Construimos la columna i vista desde abajo.
		if (contar_visibles(linea) != pistas[4 + i]) // Comparamos con la pista inferior correspondiente.
			return (0); // Cualquier discrepancia invalida el tablero.
		rellenar_linea(tablero, linea, i, 2); // Construimos la fila i vista desde la izquierda.
		if (contar_visibles(linea) != pistas[(4 * 2) + i]) // Comparamos con la pista izquierda correspondiente.
			return (0); // Si no coincide, no cumple las restricciones.
		rellenar_linea(tablero, linea, i, 3); // Construimos la fila i vista desde la derecha.
		if (contar_visibles(linea) != pistas[(4 * 3) + i]) // Comparamos con la pista derecha correspondiente.
			return (0); // Si no coincide, no hay solucion valida con este tablero.
		i++; 
	}
	return (1); // Todas las vistas coinciden con las 16 pistas.
}

void	imprimir_tablero(int tablero[4][4])
{
	// Imprime el tablero 4x4 en salida estandar con espacios entre columnas.
	int		fila; // Indice para recorrer filas del tablero.
	int		columna; // Indice para recorrer columnas del tablero.
	char	c; // Caracter temporal para imprimir cada numero como ASCII.

	fila = 0; // Empezamos en la primera fila.
	while (fila < 4) // Recorremos las 4 filas.
	{
		columna = 0; // Reiniciamos a la primera columna de la fila actual.
		while (columna < 4) // Recorremos las 4 columnas de esta fila.
		{
			c = tablero[fila][columna] + '0'; // Convertimos el entero (1..4) al caracter correspondiente.
			write(1, &c, 1); // Escribimos el numero en salida estandar.
			if (columna < 3) // Si no es la ultima columna...
				write(1, " ", 1); // ...imprimimos un espacio separador.
			columna++; // Avanzamos a la siguiente columna.
		}
		write(1, "\n", 1); // Al terminar la fila, imprimimos salto de linea.
		fila++; // Avanzamos a la siguiente fila.
	}
}
