/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_connex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/05 14:31:42 by mle-roy           #+#    #+#             */
/*   Updated: 2014/03/05 14:52:26 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "lemmin.h"

static int		how_many_dash(const char *str)
{
	int		ret;

	ret = 0;
	while (*str)
	{
		if (*str == '-')
			ret++;
		str++;
	}
	return (ret);
}

t_connex		*init_connex(char *str)
{
	t_connex	*new;

	if ((new = (t_connex *)malloc(sizeof(*new))) == NULL)
		ft_exit("malloc", 1);
	new->name = ft_strdup(str);
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

static void		add_back_connex(char *name, char *str, t_env *maze)
{
	t_mz	*room;

	room = maze->rooms;
	while (room)
	{
		if (!ft_strcmp(str, room->name))
		{
			add_connex_to_room(room, name, maze, 0);
			return ;
		}
		room = room->next;
	}
	error_lemmin();
}

void		add_connex_to_room(t_mz *room, char *str, t_env *maze, int flag)
{
	t_connex	*connex;
	t_connex	*tmp;

	connex = init_connex(str);
	if (room->list == NULL)
		room->list = connex;
	else
	{
		tmp = room->list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = connex;
		connex->prev = tmp;
	}
	if (flag == 1)
		add_back_connex(room->name, str, maze);
}

void			add_connex(t_env *maze, t_lex *lex)
{
	t_mz	*room;
	char	**tab;

	if (maze->rooms == NULL)
		error_lemmin();
	if ((how_many_dash(lex->str) != 1))
		error_lemmin();
	tab = ft_strsplit(lex->str, '-');
	room = maze->rooms;
	while (room)
	{
		if (!ft_strcmp(room->name, tab[0]))
		{
			add_connex_to_room(room, tab[1], maze, 1);
			ft_tabfree(&tab);
			return ;
		}
		room = room->next;
	}
	error_lemmin();
}
