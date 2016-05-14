/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_directory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/21 12:37:03 by mdugot            #+#    #+#             */
/*   Updated: 2016/01/29 17:23:16 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

int			size_directory(t_lsrep *rep, t_lsdata *data)
{
	size_t		result;
	t_list		*tmp;
	t_lsfile	*file;

	result = 0;
	tmp = rep->files;
	while (tmp != NULL)
	{
		file = (t_lsfile*)tmp->content;
		if (file->type != 'd' && (file->name[0] != '.' || data->options[O_ALL])
			&& file->size > 0)
			result += (((file->size - 1) / 4096) + 1) * 8;
		tmp = tmp->next;
	}
	return (result);
}

t_lsrep		*read_directory(t_lsfile *file, t_lsdata *data)
{
	DIR				*dir;
	struct dirent	*tmp;
	t_lsrep			*rep;
	t_lsfile		*tmp_file;

	dir = opendir(file->full_name);
	rep = ft_memalloc(sizeof(t_lsrep));
	rep->origin = file;
	if (dir == NULL)
	{
		rep->error = ft_strdup(strerror(errno));
		return (rep);
	}
	errno = 0;
	while ((tmp = readdir(dir)) != NULL)
	{
		tmp_file = read_file(file->full_name, tmp->d_name, 0, 0);
		add_list_files(&(rep->files), tmp_file, data);
	}
	if (errno != 0)
		rep->error = ft_strdup(strerror(errno));
	rep->number_blocks = size_directory(rep, data);
	closedir(dir);
	return (rep);
}
