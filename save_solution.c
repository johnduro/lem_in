/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_solution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/06 15:52:37 by mle-roy           #+#    #+#             */
/*   Updated: 2014/03/06 15:56:16 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lemmin.h"
#include "libft.h"

static t_room		*init_room_path(t_mz *room)
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

static void			add_path(t_res *res, t_mz *room)
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

static t_mz			*find_next_room(t_mz *room, t_env *maze)
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

void				save_solution(t_res *res, t_env *maze)
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
