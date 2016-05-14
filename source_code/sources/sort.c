/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/21 16:24:09 by mdugot            #+#    #+#             */
/*   Updated: 2016/01/29 18:05:39 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

time_t	which_time(t_lsfile *file, t_lsdata *data)
{
	if (data->options[O_ACCESS_TIME])
		return (file->acces_time);
	else if (data->options[O_CREATION_TIME])
		return (file->status_time);
	else
		return (file->modification_time);
}

int		sort_name(void *a1, void *a2, void *option)
{
	t_lsfile	*f1;
	t_lsfile	*f2;
	t_lsdata	*data;

	f1 = (t_lsfile*)a1;
	f2 = (t_lsfile*)a2;
	data = (t_lsdata*)option;
	if (f1->error == NULL && f2->error != NULL)
		return (1);
	else if (f1->error != NULL && f2->error == NULL)
		return (0);
	else if (ft_strcmp(f1->name, f2->name) > 0)
		return (data->options[O_REVERSE] ? 0 : 1);
	return (data->options[O_REVERSE] ? 1 : 0);
}

int		sort_mtime(void *a1, void *a2, void *option)
{
	t_lsfile	*f1;
	t_lsfile	*f2;
	t_lsdata	*data;
	time_t		t1;
	time_t		t2;

	f1 = (t_lsfile*)a1;
	f2 = (t_lsfile*)a2;
	data = (t_lsdata*)option;
	t1 = which_time(f1, data);
	t2 = which_time(f2, data);
	if (f1->error == NULL && f2->error != NULL)
		return (1);
	else if (f1->error != NULL && f2->error == NULL)
		return (0);
	else if (t1 < t2)
		return (data->options[O_REVERSE] ? 0 : 1);
	else if (t1 == t2)
		return (sort_name(a1, a2, option));
	return (data->options[O_REVERSE] ? 1 : 0);
}

int		sort_size(void *a1, void *a2, void *option)
{
	t_lsfile	*f1;
	t_lsfile	*f2;
	t_lsdata	*data;

	f1 = (t_lsfile*)a1;
	f2 = (t_lsfile*)a2;
	data = (t_lsdata*)option;
	if (f1->error == NULL && f2->error != NULL)
		return (1);
	else if (f1->error != NULL && f2->error == NULL)
		return (0);
	else if (f1->size < f2->size)
		return (data->options[O_REVERSE] ? 0 : 1);
	return (data->options[O_REVERSE] ? 1 : 0);
}

void	add_list_files(t_list **a, t_lsfile *f, t_lsdata *data)
{
	if (data->options[O_MODIFIED_TIME])
		ft_lstadd_sorted_o(a,
				ft_lstnew_noalloc(f, sizeof(t_lsfile)), data, sort_mtime);
	else if (data->options[O_SIZE])
		ft_lstadd_sorted_o(a,
				ft_lstnew_noalloc(f, sizeof(t_lsfile)), data, sort_size);
	else
		ft_lstadd_sorted_o(a,
				ft_lstnew_noalloc(f, sizeof(t_lsfile)), data, sort_name);
}
