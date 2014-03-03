/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_lex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/03 18:12:03 by mle-roy           #+#    #+#             */
/*   Updated: 2014/03/03 18:15:54 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"
#include "lemmin.h"

static int			is_start_end(char *str)
{
	char	*buf;

	buf = ft_strtrim(str);
	if (!ft_strcmp(buf, "##start"))
	{
		free(buf);
		return (1);
	}
	else if (!ft_strcmp(buf, "##end"))
	{
		free(buf);
		return (1);
	}
	free(buf);
	return (0);
}

static int			is_valid_lem(char *buf)
{
	int		flag;
	int		i;

	i = 0;
	flag = 0;
	while (buf[i])
	{
		if (i == 0 || (ft_isalnum(buf[i]) && ft_isspace(buf[i - 1])))
			flag++;
		i++;
	}
	if (flag > 3)
		return (0);
	else
		return (1);
}

static int			check_buf(char *buf)
{
	int		i;

	i = 0;
	while (ft_isspace(buf[i]))
		i++;
	if (buf[i] == '\0')
		return (-1);
	if (buf[0] == '#')
	{
		if (is_start_end(buf))
			return (1);
		return (0);
	}
	if (!is_valid_lem(buf))
		return (-1);
	return (1);
}

t_lx				*get_lex(void)
{
	char	*buf;
	t_lx	*list;
	int		ret;

	ret = 0;
	if ((list = init_lex()) == NULL)
		return (NULL);
	while ((ret = get_next_line(0, &buf)))
	{
		if (ret == -1)
			return (NULL);
		if ((ret = check_buf(buf)))
		{
			if (ret == -1)
				return (list);
			add_to_list(list, buf);
		}
		free(buf);
	}
	return (list);
}
