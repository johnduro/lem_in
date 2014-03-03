/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemmin.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/03 17:18:46 by mle-roy           #+#    #+#             */
/*   Updated: 2014/03/03 18:17:21 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMMIN_H
# define LEMMIN_H

typedef struct		s_lex
{
	char				*str;
	struct s_lex		*next;
	struct s_lex		*prev;
}					t_lex;

typedef struct		s_lx
{
	t_lex				*start;
	t_lex				*end;
}					t_lx;

typedef struct		s_connex
{
	char				*name;
	struct s_connex		*next;
	struct s_connex		*prev;
}					t_connex;

typedef struct		s_mz
{
	char				*name;
	char				flag;
	int					path;
	t_connex			*list;
	struct s_mz			*next;
	struct s_mz			*prev;
}					t_mz;

typedef struct		s_env
{
	int					fourmiz;
	char				*start;
	char				*end;
	t_mz				*maze;
}					t_env;

t_lx		*get_lex(void);
void		add_to_list(t_lx *list, char *buf);
t_lx		*init_lex(void);

#endif /* !LEMMIN_H */
