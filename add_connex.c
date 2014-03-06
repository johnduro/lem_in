/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_connex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/05 14:31:42 by mle-roy           #+#    #+#             */
/*   Updated: 2014/03/06 16:15:22 by mle-roy          ###   ########.fr       */
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

char			**get_room_name(char *str)
{
	char	**tab;
	char	*tmp;

	tab = ft_strsplit(str, '-');
	tmp = ft_strtrim(tab[0]);
	free(tab[0]);
	tab[0] = tmp;
	tmp = ft_strtrim(tab[1]);
	free(tab[1]);
	tab[1] = tmp;
	return (tab);
}

void			add_connex(t_env *maze, t_lex *lex)
{
	t_mz	*room;
	char	**tab;

	if (maze->rooms == NULL)
		error_lemmin();
	if ((how_many_dash(lex->str) != 1))
		error_lemmin();
	tab = get_room_name(lex->str);
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
