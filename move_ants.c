/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/06 19:36:50 by mle-roy           #+#    #+#             */
/*   Updated: 2014/03/06 19:38:57 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lemmin.h"
#include "libft.h"

static void		make_move(t_ant *ant, t_room *room)
{
	if (ant == NULL || room->start || room == NULL)
		return ;
	if (room->end)
		ant->finish = 1;
	ant->move = 1;
	if (ant->room)
		free(ant->room);
	ant->room = ft_strdup(room->name);
	make_move(ant->next, room->prev);
}

void			move_ants(t_res *res, t_env *maze)
{
	t_ant	*ant;
	t_room	*max_room;

	ant = maze->ants;
	while (ant->finish != 0)
		ant = ant->next;
	max_room = res->path;
	if (ant->room != NULL)
	{
		while ((ft_strcmp(ant->room, max_room->name)))
			max_room = max_room->next;
	}
	make_move(ant, max_room->next);
}
