#include "ft_ls.h"

static void		get_time(t_meta **data)
{
	struct stat	st;
	t_meta	*d;

	d = *data;
	while (d)
	{
		stat(d->path, &st);
		d->m_time = st.st_mtime;
		d = d->next;
	}
}

t_meta			*dispatch_sort(t_meta **data, int opts)
{
	if (MATCH(opts, LT))
	{
		get_time(data);
		return (time_sort(data));
	}
	return (bubble_sort(data, !MATCH(opts, LR)));
}
