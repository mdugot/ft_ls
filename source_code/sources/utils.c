/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/21 16:59:08 by mdugot            #+#    #+#             */
/*   Updated: 2016/01/29 18:13:40 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <sys/ioctl.h>

int			size_number(int n)
{
	int r;

	r = 1;
	while (n >= 10)
	{
		r++;
		n /= 10;
	}
	return (r);
}

void		update_format(t_lsfile *origin, t_format *format, t_lsdata *data)
{
	int				n;
	t_lsfile		*file;

	file = find_file(origin, data);
	if (file->error != NULL ||
		(!file->argument && file->name[0] == '.' && !data->options[O_ALL]))
		return ;
	if ((n = ft_strlen(origin->name)) > format->name_width)
		format->name_width = n;
	if ((n = ft_strlen(file->user)) > format->user_width)
		format->user_width = n;
	if ((n = ft_strlen(file->group)) > format->group_width)
		format->group_width = n;
	if ((n = size_number(file->size)) > format->size_width)
		format->size_width = n;
	if ((n = size_number(file->number_links)) > format->links_width)
		format->links_width = n;
}

t_format	calculate_format(t_list *list, t_lsdata *data)
{
	t_lsfile		*file;
	t_format		format;
	struct winsize	win;

	ft_bzero(&format, sizeof(t_format));
	ioctl(0, TIOCGWINSZ, &win);
	format.window_width = win.ws_col;
	while (list != NULL)
	{
		file = (t_lsfile*)list->content;
		update_format(file, &format, data);
		list = list->next;
	}
	format.fpl = format.window_width / (format.name_width + GAP_SIZE);
	return (format);
}
