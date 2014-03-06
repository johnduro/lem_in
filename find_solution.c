/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_solution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/06 15:46:54 by mle-roy           #+#    #+#             */
/*   Updated: 2014/03/06 15:52:25 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemmin.h"
#include "libft.h"

static void		free_connex_lst(t_connex *list)
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

static void		manage_res(t_res *res)
{
	if (res->current)
		free_connex_lst(res->current);
	res->current = res->next;
	res->next = NULL;
}

static void		cat_connex(t_res *res, t_mz *room)
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

int				find_solution(t_env *maze, t_res *res, int i)
{
	t_connex		*connex;
	t_mz			*ptr;
	int				ret;

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
	return (ret);
}
