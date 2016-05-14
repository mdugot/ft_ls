/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/19 17:30:35 by mdugot            #+#    #+#             */
/*   Updated: 2016/01/29 17:07:10 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft.h"

# define GAP_SIZE 4
# define OPTIONS "lRartLuUGS"
# define S_LSFILE struct s_lsfile

typedef struct passwd	t_passwd;
typedef struct group	t_group;

typedef enum	e_option
{
	O_LIST = 0, O_REPERTORY = 1, O_ALL = 2, O_REVERSE = 3, O_MODIFIED_TIME = 4,
	O_LINK = 5, O_CREATION_TIME = 6, O_ACCESS_TIME = 7, O_COLOR = 8, O_SIZE = 9,
}				t_option;

typedef struct	s_lsfile
{
	char		argument;
	char		*error;
	char		*name;
	char		*path;
	char		*full_name;
	char		type;
	char		right[9];
	int			number_links;
	char		*user;
	char		*group;
	size_t		size;
	time_t		acces_time;
	time_t		modification_time;
	time_t		status_time;
	S_LSFILE	*symbolic_link;
}				t_lsfile;

typedef struct	s_lsrep
{
	char		*error;
	int			number_blocks;
	t_lsfile	*origin;
	t_list		*files;
}				t_lsrep;

typedef struct	s_format
{
	int			window_width;
	int			name_width;
	int			links_width;
	int			user_width;
	int			group_width;
	int			size_width;
	int			fpl;
}				t_format;

typedef struct	s_lsdata
{
	int			no_first;
	char		c_error;
	int			nfile;
	t_list		*files;
	char		options[10];
}				t_lsdata;

t_format		calculate_format(t_list *list, t_lsdata *data);
t_lsdata		*read_parameter(int argc, char **argv);
void			list_data(t_lsdata *data);
void			free_data(t_lsdata *data);
void			free_lsrep(t_lsrep *rep);
void			free_lsfile(void *file, size_t size);
void			print_repertory(t_lsrep *rep, t_lsdata *data);
void			print_data(t_lsdata *data);
void			print_repertory(t_lsrep *rep, t_lsdata *data);
t_lsrep			*read_directory(t_lsfile *file, t_lsdata *data);
t_lsfile		*read_file(char *path, char *name, char arg, char link);
void			add_list_files(t_list **alist, t_lsfile *file, t_lsdata *data);
int				to_print(t_lsfile *file, t_lsdata *data);
t_lsfile		*find_file(t_lsfile *file, t_lsdata *data);
void			print_time(t_lsfile *file, t_lsdata *data);
time_t			which_time(t_lsfile *file, t_lsdata *data);
void			print_color_file(t_lsdata *data, char type);

#endif
