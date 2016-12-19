/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdrumm <kdrumm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/15 13:54:23 by kdrumm            #+#    #+#             */
/*   Updated: 2016/10/27 20:28:58 by kdrumm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	valid_tetra(t_tetra *t, int z)
{
	int		k;
	int		ok;
	int		n;
	int		x;

	k = 0;
	ok = 0;
	while (k < 4)
	{
		n = 0;
		while (n < 3)
		{
			x = ((n + k + 1) % 4);
			if (((ABS(t->p[x].x - t->p[k].x)) == 1) &&
				(t->p[x].y - t->p[k].y == 0))
				ok++;
			if (((ABS(t->p[x].y - t->p[k].y)) == 1) &&
				(t->p[x].x - t->p[k].x == 0))
				ok++;
			n++;
		}
		k++;
	}
	if (ok < 5 || z != 4)
		error("error\n");
}

/*
** Find the smallest square board which
** has enough space for all the tetriminos to fit on it.
*/

void	get_smallest_square(int n)
{
	int		i;

	i = 2;
	while (i * i < n)
		i++;
	g_size = i;
}

/*
** Initialize the board and set it to all dots
*/

int		start_board(void)
{
	int		i;

	if (g_board)
		free_board();
	g_board = (char **)malloc(sizeof(char *) * (g_size + 1));
	MALLOC_GUARD(g_board);
	i = 0;
	while (i < g_size)
	{
		g_board[i] = (char *)malloc(sizeof(char) * (g_size + 1));
		MALLOC_GUARD(g_board[i]);
		g_board[i] = ft_memset(g_board[i], '.', g_size + 1);
		i++;
	}
	g_board[g_size] = 0;
	return (1);
}
