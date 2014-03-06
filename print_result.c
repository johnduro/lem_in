/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_result.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/06 19:31:06 by mle-roy           #+#    #+#             */
/*   Updated: 2014/03/06 19:39:49 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "lemmin.h"
#include "libft.h"

static void		print_moves(t_env *maze)
{
	t_ant	*ant;
	char	flag;

	flag = 0;
	ant = maze->ants;
	while (ant)
	{
		if (ant->move)
		{
			if (flag)
				write(1, " ", 1);
			else
				flag = 1;
			write(1, "L", 1);
			ft_putnbr(ant->nb);
			write(1, "-", 1);
			ft_putstr(ant->room);
		}
		ant = ant->next;
	}
}

static void		reset_move(t_env *maze)
{
	t_ant	*ant;

	ant = maze->ants;
	while (ant)
	{
		if (ant->move == 1)
			ant->move = 0;
		ant = ant->next;
	}
}

static int		lem_is_finish(t_env *maze)
{
	int		flag;
	t_ant	*ant;

	ant = maze->ants;
	flag = 0;
	while (ant)
	{
		if (ant->finish == 0)
			flag++;
		ant = ant->next;
	}
	return (flag);
}

static void		print_map_lem(t_lx *lex)
{
	t_lex	*map;

	map = lex->save;
	while (map)
	{
		ft_putendl(map->str);
		map = map->next;
	}
}

void			print_result(t_res *res, t_env *maze, t_lx *lex)
{
	int		finish;

	finish = -1;
	print_map_lem(lex);
	write(1, "\n", 1);
	while (finish)
	{
		move_ants(res, maze);
		print_moves(maze);
		write(1, "\n", 1);
		reset_move(maze);
		finish = lem_is_finish(maze);
	}
}
