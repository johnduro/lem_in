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

#endif /* !LEMMIN_H */
