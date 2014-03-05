/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/03 17:29:18 by mle-roy           #+#    #+#             */
/*   Updated: 2014/03/05 18:17:38 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lemmin.h"
#include "libft.h"

#include <stdio.h> //nononon

int			error_lemmin(void)
{
	write(2, "ERROR\n", 6);
	exit(0);
}

t_res		*init_res(void)
{
	t_res	*new;

	if ((new = (t_res *)malloc(sizeof(*new))) == NULL)
		ft_exit("malloc", 1);
	new->path = NULL;
	new->current = NULL;
	new->next = NULL;
	return (new);
}

t_connex		*copy_connex(t_connex *list)
{
	t_connex	*first;
	t_connex	*ptr;
	t_connex	*browse;

	if (list == NULL)
		return (NULL);
	first = init_connex(list->name);
	browse = list->next;
	ptr = first;
	while (browse)
	{
		ptr->next = init_connex(browse->name);
		ptr = ptr->next;
		browse = browse->next;
	}
	return (first);
}

t_connex		*make_start(t_mz *start)
{
	t_connex	*copy;

	start->flag = 1;
	start->path = 1;
	copy = copy_connex(start->list);
	return (copy);
}

void		cat_connex(t_res *res, t_mz *room)
{
	t_connex	*connex;

	if (res->next == NULL)
		res->next = copy_connex(room->list);
	else
	{
		connex = res->next;
		while (connex->next)
			connex = connex->next;
		connex->next = copy_connex(room->list);
	}
}

void		free_connex_lst(t_connex *list)
{
	t_connex	*browse;
	t_connex	*tmp;

	browse = list;
	while (browse)
	{
		tmp = browse->next;
		free(browse->name);
		free(browse);
		browse = tmp;
	}
}

void		manage_res(t_res *res)
{
	if (res->current)
		free_connex_lst(res->current);
	res->current = res->next;
	res->next = NULL;
}

int			find_solution(t_env *maze, t_res *res)
{
	t_connex		*connex;
	t_mz			*ptr;
	int				ret;
	static int		i = 2;

	ret = 0;
	connex = res->current;
	while (connex)
	{
		ptr = maze->rooms;
		while (ptr)
		{
			if (!ft_strcmp(ptr->name, connex->name) && ptr->flag == 0)
			{
				if (ptr->end == 1)
					ret = 1;
				cat_connex(res, ptr);
				ptr->flag = 1;
				ptr->path = i;
			}
			ptr = ptr->next;
		}
		connex = connex->next;
	}
	manage_res(res);
	i++;
	return (ret);
}

int			is_solution(t_mz *rooms)
{
	t_mz			*tmp;
	static int		last = 0;
	int				i;

	i = 0;
	tmp = rooms;
	while (tmp)
	{
		if (tmp->flag == 0)
			i++;
		tmp = tmp->next;
	}
	if (i == last)
		return (1);
	last = i;
	return (0);
}

t_room		*init_room_path(t_mz *room)
{
	t_room	*new;

	if ((new = (t_room *)malloc(sizeof(*new))) == NULL)
		ft_exit("malloc", 1);
	new->name = ft_strdup(room->name);
	if (room->start == 1)
		new->start = 1;
	else
		new->start = 0;
	if (room->end == 1)
		new->end = 1;
	else
		new->end = 0;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void		add_path(t_res *res, t_mz *room)
{
	t_room	*add;

	if (res->path == NULL)
		res->path = init_room_path(room);
	else
	{
		add = init_room_path(room);
		res->path->prev = add;
		add->next = res->path;
		res->path = add;
	}
}

t_mz		*find_next_room(t_mz *room, t_env *maze)
{
	t_connex	*connex;
	t_mz		*browse;

	connex = room->list;
	while (connex)
	{
		browse = maze->rooms;
		while (browse)
		{
			if (!ft_strcmp(browse->name, connex->name))
			{
				if (browse->path == (room->path - 1))
					return (browse);
			}
			browse = browse->next;
		}
		connex = connex->next;
	}
	return (NULL);
}

void		save_solution(t_res *res, t_env *maze)
{
	t_mz	*room;

	room = maze->end_ptr;
	add_path(res, room);
	while (room->path != 1)
	{
		room = find_next_room(room, maze);
		if (room == NULL)
			error_lemmin();
		add_path(res, room);
	}
}

t_res		*treat_maze(t_env *maze)
{
	t_res	*res;
	int		find;

	int		i = 1; //TEMPTEMPTEMPTEMPTEMP

	find = 0;
	res = init_res();
	res->current = make_start(maze->start_ptr);
	while (!find)
	{
		if (is_solution(maze->rooms))
			error_lemmin();
		find = find_solution(maze, res);
//		debug_treat_maze(maze, i);
		i++; //nonononon
	}
	save_solution(res, maze); // a faire
	return (res);
}

int			main(void)
{
	t_lx	*lex;
	t_env	*maze;
	t_res	*res;

	lex = get_lex();
	if (lex == NULL)
		error_lemmin();
	print_lex(lex); //nononononon
	maze = get_maze(lex);
	print_maze(maze); //nonononono
	res = treat_maze(maze);
	debug_solution(res);
//	print_result(res, maze, lex);
	return (0);
}
