#include "lib/list.h"

#include <stdlib.h> // NULL, malloc()


t_list *list_new(void *content)
{
	t_list *list;

	list = malloc(sizeof(t_list));
	if (!list)
		return (NULL);
	list->content = content;
	list->next = NULL;
	return (list);
}
