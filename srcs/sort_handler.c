#include "ft_ls.h"

t_meta		*dispatch_sort(t_meta **data, int opts)
{
	t_meta		*d;
	struct stat	st;

	d = *data;
	if (MATCH(opts, LT))
	{
		while (d)
		{
			stat(d->path, &st);
			d->m_time = st.st_mtime;
			d = d->next;
		}
		return (time_sort(data));
	}
	return (bubble_sort(data, !MATCH(opts, LR)));
}
