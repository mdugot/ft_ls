/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/21 16:56:40 by mdugot            #+#    #+#             */
/*   Updated: 2016/01/29 16:59:24 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <time.h>

void	print_detail(t_lsfile *origin, t_lsdata *data, t_format format)
{
	t_lsfile	*link;
	t_lsfile	*file;

	if (origin->error != NULL)
	{
		ft_printf_fd(2, "ft_ls: %s: %s\n", origin->name, origin->error);
		return ;
	}
	file = find_file(origin, data);
	print_color_file(data, origin->type);
	ft_printf("%c%s  ", file->type, file->right);
	ft_printf("%*d ", format.links_width, file->number_links);
	ft_printf("%*s  ", format.user_width, file->user);
	ft_printf("%*s  ", format.group_width, file->group);
	ft_printf("%*zu ", format.size_width, file->size);
	print_time(file, data);
	ft_printf("%s", origin->name);
	if (file->type == 'l' && file->symbolic_link != NULL)
	{
		link = file->symbolic_link;
		ft_printf(" -> %s", link->name);
	}
	ft_printf("#N\n");
}

void	print_files(t_list *files, t_lsdata *data)
{
	t_format	format;
	int			i;
	t_lsfile	*tmp;

	format = calculate_format(files, data);
	i = 0;
	while (files)
	{
		tmp = (t_lsfile*)files->content;
		if (tmp->error != NULL)
			ft_printf_fd(2, "ft_ls: %s: %s\n", tmp->name, tmp->error);
		else if (to_print(tmp, data))
		{
			print_color_file(data, tmp->type);
			ft_printf("%-*s#N", (format.name_width + GAP_SIZE), tmp->name);
			i++;
			if (i >= format.fpl)
				i = ft_printf("\n") - 1;
		}
		files = files->next;
	}
	if (i != 0)
		ft_printf("\n");
}

void	print_files_l(t_list *files, t_lsdata *data)
{
	t_format	format;
	t_lsfile	*tmp;

	format = calculate_format(files, data);
	while (files)
	{
		tmp = (t_lsfile*)files->content;
		if (to_print(tmp, data))
			print_detail(tmp, data, format);
		files = files->next;
	}
}

void	print_repertory(t_lsrep *rep, t_lsdata *data)
{
	if (data->no_first)
		ft_printf("\n");
	if (data->no_first || data->nfile > 1)
		ft_printf("%s:\n", rep->origin->full_name);
	if (data->no_first == 0)
		data->no_first = 1;
	if (data->options[O_LIST])
	{
		if (rep->error == NULL)
			ft_printf("total %d\n", rep->number_blocks);
		print_files_l(rep->files, data);
	}
	else
		print_files(rep->files, data);
	if (rep->error != NULL)
		ft_printf_fd(2, "ft_ls: %s: %s\n", rep->origin->name, rep->error);
}

void	print_data(t_lsdata *data)
{
	if (data->c_error)
	{
		ft_printf_fd(2, "ft_ls: illegal option -- %c\n", data->c_error);
		ft_printf_fd(2, "usage: ls [-%s] [file ...]\n", OPTIONS);
		return ;
	}
	if (data->options[O_LIST])
		print_files_l(data->files, data);
	else
		print_files(data->files, data);
}
