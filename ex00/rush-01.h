/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush-01.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scamlett <scamlett@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 11:50:34 by scamlett          #+#    #+#             */
/*   Updated: 2026/03/14 12:14:30 by scamlett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#define SIZE 4

int		parsear(char *texto, int *pistas);
int		contar_visibles(int linea[SIZE]);
int		comprobar_vistas(int tablero[SIZE][SIZE], int *pistas);
void	imprimir_tablero(int tablero[SIZE][SIZE]);
int		resolver(int tablero[SIZE][SIZE], int *pistas);
