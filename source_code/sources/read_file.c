/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/20 16:58:01 by mdugot            #+#    #+#             */
/*   Updated: 2016/01/29 17:07:09 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <uuid/uuid.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

char		read_type(struct stat *buf)
{
	if (S_ISREG(buf->st_mode))
		return ('-');
	if (S_ISDIR(buf->st_mode))
		return ('d');
	if (S_ISLNK(buf->st_mode))
		return ('l');
	if (S_ISBLK(buf->st_mode))
		return ('b');
	if (S_ISCHR(buf->st_mode))
		return ('c');
	if (S_ISFIFO(buf->st_mode))
		return ('p');
	if (S_ISSOCK(buf->st_mode))
		return ('s');
	return ('-');
}

void		read_rights(t_lsfile *file, struct stat *buf)
{
	ft_memset(file->right, '-', 9);
	if (buf->st_mode & S_IRUSR)
		file->right[0] = 'r';
	if (buf->st_mode & S_IWUSR)
		file->right[1] = 'w';
	if (buf->st_mode & S_IXUSR)
		file->right[2] = 'x';
	if (buf->st_mode & S_IRGRP)
		file->right[3] = 'r';
	if (buf->st_mode & S_IWGRP)
		file->right[4] = 'w';
	if (buf->st_mode & S_IXGRP)
		file->right[5] = 'x';
	if (buf->st_mode & S_IROTH)
		file->right[6] = 'r';
	if (buf->st_mode & S_IWOTH)
		file->right[7] = 'w';
	if (buf->st_mode & S_IXOTH)
		file->right[8] = 'x';
}

void		read_file_info(t_lsfile *file, struct stat *buf)
{
	t_passwd	*user;
	t_group		*group;

	file->type = read_type(buf);
	read_rights(file, buf);
	file->number_links = buf->st_nlink;
	file->size = buf->st_size;
	user = getpwuid(buf->st_uid);
	group = getgrgid(buf->st_gid);
	if (user == NULL)
		file->user = ft_itoa(buf->st_uid);
	else
		file->user = ft_strdup(user->pw_name);
	if (group == NULL)
		file->group = ft_itoa(buf->st_gid);
	else
		file->group = ft_strdup(group->gr_name);
	file->acces_time = buf->st_atime;
	file->modification_time = buf->st_mtime;
	file->status_time = buf->st_ctime;
}

t_lsfile	*read_link(char *origin, char arg)
{
	char		name[1024];
	int			len;
	t_lsfile	*result;
	char		*tmp;
	char		*c;

	ft_bzero(name, 1024);
	len = readlink(origin, name, 1023);
	tmp = ft_strdup(origin);
	c = ft_strrchr(tmp, '/');
	if (c == NULL)
		*tmp = '\0';
	else
		c[1] = '\0';
	if (name[0] != '/')
		result = read_file(tmp, name, arg, 1);
	else
		result = read_file("", name, arg, 1);
	ft_strdel(&tmp);
	return (result);
}

t_lsfile	*read_file(char *path, char *name, char arg, char link)
{
	struct stat	buf;
	t_lsfile	*result;

	result = ft_memalloc(sizeof(t_lsfile));
	ft_bzero(result, sizeof(t_lsfile));
	result->argument = arg;
	result->name = ft_strdup(name);
	result->path = ft_strdup(path);
	result->full_name = ft_strnew(ft_strlen(path) + ft_strlen(name) + 2);
	ft_strcpy(result->full_name, path);
	if (*path != '\0' && path[ft_strlen(path)] != '/')
		ft_strcat(result->full_name, "/");
	ft_strcat(result->full_name, name);
	if (lstat(result->full_name, &buf) == -1)
	{
		result->error = ft_strdup(strerror(errno));
		return (result);
	}
	read_file_info(result, &buf);
	if (result->type == 'l' && link == 0)
		result->symbolic_link = read_link(result->full_name, arg);
	return (result);
}
