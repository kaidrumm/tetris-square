/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdrumm <kdrumm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/12 15:49:18 by dbotova           #+#    #+#             */
/*   Updated: 2016/10/27 20:16:21 by kdrumm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
** If the piece does not fit, delete it from the board
*/

void	clear_letter(char c)
{
	int		i;
	int		j;

	j = 0;
	while (j < g_size)
	{
		i = 0;
		while (i < g_size)
		{
			if (g_board[j][i] == c)
				g_board[j][i] = '.';
			i++;
		}
		j++;
	}
}

/*
** Put the tetra's letters on the board, but if it's not an empty spot,
** abort, clear the letter from the board and return 0.
*/

int		place_piece(t_tetra *t, int i, int j)
{
	int		k;

	k = 0;
	while (k < 4)
	{
		if (t->p[k].x + i < g_size && t->p[k].y + j < g_size &&
			g_board[t->p[k].x + i][t->p[k].y + j] == '.')
			g_board[t->p[k].x + i][t->p[k].y + j] = t->c;
		else
		{
			clear_letter(t->c);
			k = 9;
		}
		k++;
	}
	if (k == 4)
		return (1);
	return (0);
}

/*
** Recursive function which tests all possible placements for the tetras
** in the order that they were given, searching from left to right and top
** to bottom.
*/

int		spiral(t_tetra **ary, int n)
{
	int		x;
	int		y;

	if (n == 0)
		return (1);
	if (!ary[0])
		return (0);
	y = 0;
	while (y < g_size)
	{
		x = 0;
		while (x < g_size)
		{
			if (place_piece(*ary, x, y))
			{
				if (spiral(&ary[1], n - 1))
					return (1);
				else
					clear_letter((*ary)->c);
			}
			x++;
		}
		y++;
	}
	return (0);
}

int		solve_puzzle(t_tetra **ptr, int n)
{
	int		solved;

	solved = 0;
	get_smallest_square(n * 4);
	while (!solved)
	{
		if (!start_board())
			error("error\n");
		solved = spiral(ptr, n);
		g_size++;
	}
	g_size--;
	print_board();
	return (1);
}
