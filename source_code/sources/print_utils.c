/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/28 16:31:41 by mdugot            #+#    #+#             */
/*   Updated: 2016/01/29 17:53:51 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <time.h>

int		to_print(t_lsfile *file, t_lsdata *data)
{
	t_lsfile	*link;

	link = file->symbolic_link;
	if (!file->argument && file->name[0] == '.' && !data->options[O_ALL])
		return (0);
	if (file->argument && file->type == 'd')
		return (0);
	if (file->argument && !data->options[O_LIST] && link && link->type == 'd')
		return (0);
	data->no_first = 1;
	return (1);
}

void	print_time(t_lsfile *file, t_lsdata *data)
{
	char		*tmp;
	time_t		now;
	time_t		file_time;

	now = time(NULL);
	file_time = which_time(file, data);
	tmp = ctime(&file_time);
	if (now < file_time || ABS(now - file_time) > 15768000)
	{
		tmp += 4;
		ft_printf("%.6s  ", tmp);
		tmp += 16;
		ft_printf("%.4s ", tmp);
	}
	else
	{
		tmp += 4;
		ft_printf("%.12s ", tmp);
	}
}

void	print_color_file(t_lsdata *data, char type)
{
	if (!data->options[O_COLOR])
		return ;
	if (type == 'd')
		ft_printf("#B");
	else if (type == 'l')
		ft_printf("#M");
	else if (type == 'b')
		ft_printf("#R");
	else if (type == 'c')
		ft_printf("#G");
	else if (type == 'p')
		ft_printf("#Y");
	else if (type == 's')
		ft_printf("#C");
	else
		ft_printf("#N");
}
