/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/22 15:08:33 by mdugot            #+#    #+#             */
/*   Updated: 2016/01/29 16:58:39 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		add_option(t_lsdata *data, char c)
{
	if (c == 'l')
		data->options[O_LIST] = 1;
	else if (c == 'R')
		data->options[O_REPERTORY] = 1;
	else if (c == 'a')
		data->options[O_ALL] = 1;
	else if (c == 'r')
		data->options[O_REVERSE] = 1;
	else if (c == 't')
		data->options[O_MODIFIED_TIME] = 1;
	else if (c == 'L')
		data->options[O_LINK] = 1;
	else if (c == 'u')
		data->options[O_ACCESS_TIME] = 1;
	else if (c == 'U')
		data->options[O_CREATION_TIME] = 1;
	else if (c == 'G')
		data->options[O_COLOR] = 1;
	else if (c == 'S')
		data->options[O_SIZE] = 1;
}

char		update_options(t_lsdata *data, char *c)
{
	while (*c)
	{
		if (ft_strchr(OPTIONS, *c))
			add_option(data, *c);
		else
			return (*c);
		c++;
	}
	return (0);
}

void		read_arguments_files(t_lsdata *data, int i, int argc, char **argv)
{
	t_lsfile	*tmp;

	if (i >= argc)
	{
		tmp = read_file("", ".", 1, 0);
		add_list_files(&(data->files), tmp, data);
		return ;
	}
	while (i < argc)
	{
		tmp = read_file("", argv[i], 1, 0);
		add_list_files(&(data->files), tmp, data);
		i++;
		data->nfile += 1;
	}
}

t_lsdata	*read_parameter(int argc, char **argv)
{
	int			i;
	char		e;
	t_lsdata	*data;

	data = ft_memalloc(sizeof(t_lsdata));
	i = 0;
	while (++i < argc && ft_strlen(argv[i]) >= 2 && argv[i][0] == '-')
	{
		e = update_options(data, &(argv[i][1]));
		if (e != 0)
		{
			data->c_error = e;
			return (data);
		}
	}
	read_arguments_files(data, i, argc, argv);
	return (data);
}
