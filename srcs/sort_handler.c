#include "ft_ls.h"

t_meta		*dispatch_sort(t_meta **data, int opts)
{
	if (MATCH(opts, LT))
		return (time_sort(data));
	return (bubble_sort(data, !MATCH(opts, LR)));
}
