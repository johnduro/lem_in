/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/03 17:29:18 by mle-roy           #+#    #+#             */
/*   Updated: 2014/03/03 18:17:43 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lemmin.h"
#include "libft.h"
#include "get_next_line.h"

#include <stdio.h> //nononon

void		print_lex(t_lx *lex)
{
	t_lex	*browse;

	browse = lex->start;
	while (browse)
	{
		printf("LEX=%s\n", browse->str);
		browse = browse->next;
	}
}

int			main(void)
{
	t_lx	*lex;
//	t_env	*maze;

	lex = get_lex();
	if (lex == NULL)
	{
		write(2, "ERROR\n", 6);
		return (0);
	}
	print_lex(lex);
//	maze = get_maze(lex);
//	treat_maze(maze);
	return (0);
}
