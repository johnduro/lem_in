/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_start_end_ant.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/05 14:42:21 by mle-roy           #+#    #+#             */
/*   Updated: 2014/03/05 14:42:25 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lemmin.h"
#include "libft.h"

static void			add_ant(t_env *maze, int ant)
{
	t_ant	*new;
	t_ant	*tmp;

	if ((new = (t_ant *)malloc(sizeof(*new))) == NULL)
		ft_exit("malloc", 1);
	new->nb = ant;
	new->room = NULL;
	new->next = NULL;
	new->prev = NULL;
	if (maze->ants == NULL)
		maze->ants = new;
	else
	{
		tmp = maze->ants;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
}

void				make_ants(t_env *maze)
{
	int		i;

	i = 1;
	while (i <= maze->fourmiz)
	{
		add_ant(maze, i);
		i++;
	}
}

void				add_start_end(t_env *maze, t_lex *node)
{
	char	**tab;
	t_mz	*room;

	if (node == NULL || node->str == NULL || (node->str)[0] == '\0')
		error_lemmin();
	tab = ft_strsplitspace(node->str);
	room = init_room(tab[0]);
	if (node->prev && !ft_strcmp(node->prev->str, "##start"))
	{
		room->start = 1;
		maze->start_ptr = room;
		maze->start = ft_strdup(tab[0]);
	}
	else if (node->prev && !ft_strcmp(node->prev->str, "##end"))
	{
		room->end = 1;
		maze->end_ptr = room;
		maze->end = ft_strdup(tab[0]);
	}
	add_to_mz(maze, room);
	ft_tabfree(&tab);
}
