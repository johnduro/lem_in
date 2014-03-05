/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_room.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/05 14:28:19 by mle-roy           #+#    #+#             */
/*   Updated: 2014/03/05 17:43:54 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "lemmin.h"

t_mz			*init_room(char *str)
{
	t_mz	*new;

	if (str[0] == 'L' || str[0] == '#')
		error_lemmin();
	if ((new = (t_mz *)malloc(sizeof(*new))) == NULL)
		ft_exit("malloc", 1);
	new->name = ft_strdup(str);
	new->flag = 0;
	new->start = 0;
	new->end = 0;
	new->path = 0;
	new->list = NULL;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void			add_room(t_env *maze, t_lex *lex)
{
	char	**tab;
	t_mz	*room;

	tab = ft_strsplitspace(lex->str);
	if (ft_strchr(tab[0], '-') != NULL)
		error_lemmin();
	room = init_room(tab[0]);
	add_to_mz(maze, room);
	ft_tabfree(&tab);
}
