#include "lib/list.h"

#include <stdlib.h> // free()


void list_clear(t_list **list, void (*del)(void *))
{
	t_list *tmp;

	if (!list || !del)
		return ;
	while (*list) {
		tmp = *list;
		*list = (*list)->next;
		del(tmp->content);
		free(tmp);
	}
}
