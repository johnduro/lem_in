/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_maze.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/05 14:22:54 by mle-roy           #+#    #+#             */
/*   Updated: 2014/03/05 18:22:58 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lemmin.h"
#include "libft.h"

#include <stdio.h> //nononononoonno

static int			how_many_word(const char *str)
{
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	while (str[i])
	{
		if (!ft_isspace(str[i]) && (i == 0 || ft_isspace(str[i - 1])))
			ret++;
		i++;
	}
	return (ret);
}

void				add_to_mz(t_env *maze, t_mz *room)
{
	t_mz	*browse;

	if (maze->rooms == NULL)
		maze->rooms = room;
	else
	{
		browse = maze->rooms;
		while (browse->next)
			browse = browse->next;
		browse->next = room;
		room->prev = browse;
	}
}

static t_env		*init_maze(t_lex *first)
{
	t_env	*new;
	int		i;

	i = 0;
	if ((new = (t_env *)malloc(sizeof(*new))) == NULL)
		ft_exit("malloc", 1);
	if (how_many_word(first->str) > 1)
		error_lemmin();
	while ((first->str)[i])
	{
		if (!ft_isdigit((first->str)[i]))
			error_lemmin();
		i++;
	}
	new->fourmiz = ft_atoi(first->str);
	new->start = NULL;
	new->end = NULL;
	new->rooms = NULL;
	new->ants = NULL;
	return (new);
}

t_env				*get_maze(t_lx *lex)
{
	t_env	*maze;
	t_lex	*browse;

	maze = init_maze(lex->start);
	browse = lex->start->next;
	while (browse)
	{
		if ((browse->str)[0] == '#')
		{
			browse = browse->next;
			add_start_end(maze, browse);
		}
		else if ((how_many_word(browse->str)) == 3)
			add_room(maze, browse);
		else if ((how_many_word(browse->str)) == 1)
			add_connex(maze, browse);
		browse = browse->next;
	}
	make_ants(maze);
	return (maze);
}
