/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_print_lem.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/05 14:39:05 by mle-roy           #+#    #+#             */
/*   Updated: 2014/03/05 16:58:19 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemmin.h"
#include "libft.h"
#include <stdio.h> //nononononon

void		debug_treat_maze(t_env *maze, int i)
{
	printf("\n****************\n\nTOUR[%d]\n", i);
	print_maze(maze);
}

void		debug_solution(t_res *res)
{
	t_room	*soluce;
	int		i = 1;

	soluce = res->path;
	printf("\n*******\nSOLUTION\n********\n");
	while (soluce)
	{
		if (soluce->start == 1)
			printf("START->>");
		if (soluce->end == 1)
			printf("END->>");
		printf("ROOM[%d]: %s\n", i, soluce->name);
		i++;
		soluce = soluce->next;
	}
}

void		print_lex(t_lx *lex)
{
	t_lex	*browse;

	browse = lex->start;
	while (browse)
	{
		printf("LEX=%s\n", browse->str);
		browse = browse->next;
	}
}

void		print_room(t_mz *room)
{
	t_connex	*tmp;

	printf("name=%s\n", room->name);
	printf("flag=%d\n", room->flag);
	printf("start=%d\n", room->start);
	printf("end=%d\n", room->end);
	printf("path=%d\n", room->path);
	tmp = room->list;
	printf("CONNEX:\n");
	while (tmp)
	{
		printf("connex to %s\n", tmp->name);
		tmp = tmp->next;
	}
}

void		print_maze(t_env *maze)
{
	t_mz	*rooms;
	t_ant	*ants;

	printf("******\nfourmiz=%d\n", maze->fourmiz);
	printf("***\nstart=%s\n", maze->start);
	if (maze->start_ptr)
	{
		printf("\nSTART-ROOM\n");
		print_room(maze->start_ptr);
	}
	printf("***\nend=%s\n", maze->end);
	if (maze->end_ptr)
	{
		printf("\nEND-ROOM\n");
		print_room(maze->end_ptr);
	}
	rooms = maze->rooms;
	printf("***\nROOMS=\n");
	while (rooms)
	{
		printf("\n");
		print_room(rooms);
		rooms = rooms->next;
	}
	ants = maze->ants;
	printf("***\nANTS=\n");
	while (ants)
	{
		printf("NB=%d\nROOM=%s\n", ants->nb, ants->room);
		ants = ants->next;
	}
}
