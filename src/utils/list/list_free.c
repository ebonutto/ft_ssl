#include "lib/list.h"

#include <stdlib.h> // free()


void list_free(t_list **list)
{
	t_list *tmp;

	if (!list)
		return ;

	while (*list) {
		tmp = *list;
		*list = (*list)->next;
		free(tmp);
	}
}
