/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush-01.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scamlett <scamlett@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 11:56:10 by scamlett          #+#    #+#             */
/*   Updated: 2026/03/14 16:10:04 by scamlett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int		comprobar_vistas(int tablero[4][4], int *pistas);
void	imprimir_tablero(int tablero[4][4]);

int	esta_en_linea(int tablero[4][4], int indice, int valor, int es_fila)
{
	// Comprueba si un valor ya existe en una fila o columna concreta.
	int i; // Variable de recorrido para iterar 4 posiciones.
	i = 0;        // Empezamos la comprobacion desde la primera columna/fila.
	while (i < 4) // Recorremos los 4 elementos de la fila o columna indicada.
	{
		if (es_fila && tablero[indice][i] == valor) 
			// Si buscamos en fila y encontramos el valor...
			return (1);                             
				// ...devolvemos 1 indicando que ya existe en esa fila.
		if (!es_fila && tablero[i][indice] == valor)
			// Si buscamos en columna y encontramos el valor...
			return (1);                             
				// ...devolvemos 1 indicando que ya existe en esa columna.
		i++;                                        
			// Avanzamos a la siguiente posicion de la fila/columna.
	}
	return (0); // No se encontro el valor en la fila/columna: devolvemos 0.
}

int	resolver_celda(int tablero[4][4], int *pistas, int posicion)
{
	// Resuelve el tablero con backtracking probando valores en cada celda.
	int fila;    // Fila actual que corresponde a la posicion lineal.
	int columna; // Columna actual que corresponde a la posicion lineal.
	int valor;   // Valor candidato a probar en la celda (1..4).
	if (posicion == 4 * 4)                         
		// Caso base: ya se rellenaron 16 celdas.
		return (comprobar_vistas(tablero, pistas));
			// Validamos que el tablero cumpla todas las vistas.
	fila = posicion / 4;                           
		// Convertimos posicion lineal a indice de fila.
	columna = posicion % 4;                        
		// Convertimos posicion lineal a indice de columna.
	valor = 1;                                     
		// Empezamos probando desde el valor minimo permitido.
	while (valor <= 4)                             
		// Probamos todos los valores posibles en esta celda.
	{
		if (!esta_en_linea(tablero, fila, valor, 1) && !esta_en_linea(tablero,
				columna, valor, 0))
			// Solo seguimos si no se repite en fila ni columna.
		{
			tablero[fila][columna] = valor;                   
				// Colocamos provisionalmente el valor en la celda actual.
			if (resolver_celda(tablero, pistas, posicion + 1))
				// Intentamos resolver recursivamente la siguiente celda.
				return (1);                                   
					// Si la recursion encuentra solucion, propagamos exito.
			tablero[fila][columna] = 0;                       
				// Backtracking: deshacemos la asignacion si no funciono.
		}
		valor++; // Probamos el siguiente candidato.
	}
	return (0); // Ningun valor valido condujo a solucion desde esta posicion.
}

int	parsear(char *texto, int *pistas)
{
	// Convierte la cadena de entrada en 16 pistas numericas validas.
	int i;       
		// Indice para recorrer caracter a caracter la cadena de entrada.
	int contador; // Cuenta cuantas pistas validas hemos extraido.
	i = 0;           // Empezamos por el primer caracter.
	contador = 0;    // Inicialmente no hay pistas parseadas.
	while (texto[i]) // Recorremos hasta el caracter nulo final.
	{
		if (texto[i] >= '1' && texto[i] <= '4')
			// Si el caracter es un digito de pista permitido...
		{
			if (contador >= 4 * 4)             // ...si ya tenemos 16 pistas,la entrada tiene demasiados numeros.
				return (0);                    // Error por exceso de pistas.
			pistas[contador] = texto[i] - '0';
				// Convertimos de ASCII a entero y guardamos la pista.
			contador++;                       
				// Aumentamos el numero de pistas leidas.
		}
		else if (texto[i] != ' ') // Si no es numero valido, solo aceptamos espacios.
			return (0);          
				// Cualquier otro caracter invalida la entrada.
		i++;                      // Avanzamos al siguiente caracter.
	}
	return (contador == 4 * 4);
		// Solo es valido si se leyeron exactamente 16 pistas.
}

int	resolver(int tablero[4][4], int *pistas)
{
	// Inicializa el tablero a cero y lanza la resolucion recursiva.
	int fila;    // Indice de fila para inicializar el tablero.
	int columna; // Indice de columna para inicializar el tablero.
	fila = 0;        // Empezamos desde la primera fila.
	while (fila < 4) // Recorremos las 4 filas del tablero.
	{
		columna = 0;        // Para cada fila empezamos en la primera columna.
		while (columna < 4) // Recorremos las 4 columnas de la fila actual.
		{
			tablero[fila][columna] = 0;
				// Inicializamos la celda a 0 (sin valor asignado).
			columna++;                  // Avanzamos a la siguiente columna.
		}
		fila++; // Avanzamos a la siguiente fila.
	}
	return (resolver_celda(tablero, pistas, 0));
		// Lanzamos el backtracking desde la posicion 0.
}

int	main(int cantidad_args, char *argumentos[])
{
	// Valida argumentos, parsea pistas, resuelve el puzzle e imprime resultado.
	int pistas[4 * 4]; // Array para almacenar las 16 pistas de entrada.
	int tablero[4][4]; // Matriz 4x4 donde se construira la solucion.
	if (cantidad_args != 2)
		// Debe recibirse exactamente un argumento (la cadena de pistas).
	{
		write(1, "Error\n", 6);
			// Mostramos error por formato de llamada incorrecto.
		return (1);             // Terminamos con codigo de error.
	}
	if (!parsear(argumentos[1], pistas))
		// Intentamos convertir y validar las pistas del argumento.
	{
		write(1, "Error\n", 6);
			// Mostramos error si la entrada contiene formato invalido.
		return (1);             // Terminamos con codigo de error.
	}
	if (!resolver(tablero, pistas))
		// Intentamos resolver el puzzle con backtracking.
	{
		write(1, "Error\n", 6);
			// Mostramos error si no existe una solucion valida.
		return (1);             // Terminamos con codigo de error.
	}
	imprimir_tablero(tablero); // Si todo fue bien, imprimimos el tablero resuelto.
	return (0);                // Terminamos correctamente.
}
