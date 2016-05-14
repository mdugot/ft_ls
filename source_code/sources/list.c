/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/22 15:03:52 by mdugot            #+#    #+#             */
/*   Updated: 2016/01/29 17:21:26 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_lsfile	*find_file(t_lsfile *file, t_lsdata *data)
{
	if (file->argument && !data->options[O_LIST] && file->symbolic_link)
		return (file->symbolic_link);
	if (data->options[O_LINK] && file->symbolic_link)
		return (file->symbolic_link);
	else
		return (file);
}

void		list_directory(t_lsfile *origin, t_lsdata *data)
{
	t_list		*tmp;
	t_lsrep		*rep;
	t_lsfile	*file;

	rep = read_directory(origin, data);
	print_repertory(rep, data);
	if (data->options[O_REPERTORY] == 0)
		return ;
	tmp = rep->files;
	while (tmp != NULL)
	{
		file = find_file(tmp->content, data);
		if (file->type == 'd' && ft_strcmp(file->name, ".")
			&& ft_strcmp(file->name, "..")
			&& (file->name[0] != '.' || data->options[O_ALL] || file->argument))
			list_directory(file, data);
		tmp = tmp->next;
	}
	free_lsrep(rep);
}

void		list_data(t_lsdata *data)
{
	t_list		*tmp;
	t_lsfile	*file;

	print_data(data);
	if (data->c_error)
		return ;
	tmp = data->files;
	while (tmp != NULL)
	{
		file = find_file(tmp->content, data);
		if (file->type == 'd')
			list_directory(file, data);
		tmp = tmp->next;
	}
}
