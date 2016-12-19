/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdrumm <kdrumm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/11 18:51:22 by dbotova           #+#    #+#             */
/*   Updated: 2016/10/27 20:31:55 by kdrumm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		g_size;
char	**g_board;

/*
** Allocates space and sets null points as (-1, -1).
*/

t_tetra	*init_tetra(void)
{
	t_tetra	*new;
	int		k;

	k = 0;
	new = (t_tetra *)malloc(sizeof(t_tetra));
	if (!new)
		error("error\n");
	while (k < 4)
	{
		new->p[k].x = -1;
		new->p[k].y = -1;
		k++;
	}
	return (new);
}

/*
** Sets the next empty (init as -1, -1) point in the tetra.
*/

t_tetra	*set_point(t_tetra *t, int x, int y)
{
	int		k;
	int		ok;

	k = 0;
	ok = 0;
	while (k < 4)
	{
		if (t->p[k].x < 0)
		{
			t->p[k].x = x;
			t->p[k].y = y;
			return (t);
		}
		k++;
	}
	error("error\n");
	return (t);
}

/*
** Shifts the tetra coordinates up & to the left.
*/

t_tetra	*adjust_coordinates(t_tetra *t)
{
	int		k;
	int		min_x;
	int		min_y;

	k = 0;
	min_x = 3;
	min_y = 3;
	while (k < 4)
	{
		if (t->p[k].x < min_x)
			min_x = t->p[k].x;
		if (t->p[k].y < min_y)
			min_y = t->p[k].y;
		k++;
	}
	while (k--)
	{
		t->p[k].x = t->p[k].x - min_x;
		t->p[k].y = t->p[k].y - min_y;
	}
	return (t);
}

/*
** This function reads hashes into the tetra struct
*/

t_tetra	*read_tet(char *buf, int ltr)
{
	t_tetra	*t;
	int		i;
	int		j;
	int		n;

	j = -1;
	n = 0;
	t = init_tetra();
	while (++j < 4)
	{
		i = -1;
		while (++i < 4)
		{
			if (buf[5 * j + i] != '.' && buf[5 * j + i] != '#')
				error("error\n");
			else if (buf[5 * j + i] == '#' && ++n)
				t = set_point(t, i, j);
		}
		if (buf[5 * j + i] != '\n')
			error("error\n");
	}
	t->c = 'A' + ltr;
	t = adjust_coordinates(t);
	valid_tetra(t, n);
	return (t);
}

/*
** Read the input 21 bytes at a time, which is the size of each tetra.
*/

int		main(int argc, char **argv)
{
	int		n;
	int		id;
	char	buf[21];
	int		bytes;
	t_tetra	*ptr[26];

	if (argc != 2)
		error("usage: ./fillit [input_file]\n");
	id = open(argv[1], O_RDONLY);
	n = 0;
	bytes = 21;
	while (bytes == 21)
	{
		bytes = read(id, &buf, 21);
		buf[20] = '\0';
		if (bytes < 20 || n >= 26)
			error("error\n");
		ptr[n] = read_tet(&buf[0], n);
		n++;
	}
	close(id);
	solve_puzzle(ptr, n);
	free_board();
	free_tetras(ptr, n);
	return (1);
}
