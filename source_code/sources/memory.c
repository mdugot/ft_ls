/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/25 15:08:35 by mdugot            #+#    #+#             */
/*   Updated: 2016/01/29 15:54:33 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	free_lsfile(void *ad, size_t size)
{
	t_lsfile *file;

	file = (t_lsfile*)ad;
	(void)size;
	if (file->error != NULL)
		ft_strdel(&(file->error));
	if (file->name != NULL)
		ft_strdel(&(file->name));
	if (file->path != NULL)
		ft_strdel(&(file->path));
	if (file->full_name != NULL)
		ft_strdel(&(file->full_name));
	if (file->user != NULL)
		ft_strdel(&(file->user));
	if (file->group != NULL)
		ft_strdel(&(file->group));
	if (file->symbolic_link != NULL)
		free_lsfile(file->symbolic_link, sizeof(*(file->symbolic_link)));
	ft_memdel((void**)&ad);
}

void	free_lsrep(t_lsrep *rep)
{
	if (rep->error != NULL)
		ft_strdel(&(rep->error));
	if (rep->files != NULL)
		ft_lstdel(&(rep->files), free_lsfile);
	ft_memdel((void**)&rep);
}

void	free_data(t_lsdata *data)
{
	if (data->files != NULL)
		ft_lstdel(&(data->files), free_lsfile);
	ft_memdel((void**)&data);
}
