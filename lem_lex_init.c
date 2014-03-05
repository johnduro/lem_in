/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_lex_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/03 18:15:23 by mle-roy           #+#    #+#             */
/*   Updated: 2014/03/05 18:05:00 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lemmin.h"
#include "libft.h"

int					is_valid_char_lem(char c)
{
	if (c >= 33 && c <= 126)
		return (1);
	return (0);
}

t_lx				*init_lex(void)
{
	t_lx	*new;

	if ((new = (t_lx *)malloc(sizeof(*new))) == NULL)
		return (NULL);
	new->start = NULL;
	new->end = NULL;
	new->save = NULL;
	new->save_end = NULL;
	return (new);
}

t_lex				*init_node(char *buf)
{
	t_lex	*new;

	if ((new = (t_lex *)malloc(sizeof(*new))) == NULL)
		return (NULL);
	new->str = ft_strtrim(buf);
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void				add_to_list(t_lx *list, char *buf)
{
	t_lex	*node;

	node = init_node(buf);
	if (node == NULL)
		return ;
	if (list->start == NULL)
	{
		list->start = node;
		list->end = node;
	}
	else
	{
		list->end->next = node;
		node->prev = list->end;
		list->end = node;
	}
}
