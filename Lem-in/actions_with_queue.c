#include "lem_in.h"

void	queue_pop(t_queue **q)
{
	t_queue	*tmp;
	int		i;

	i = 0;
	while ((*q) && (!(*q)->room || !i))
	{
		tmp = *q;
		if ((*q)->next_in_q)
			*q = (*q)->next_in_q;
		else
			*q = NULL;
		free(tmp);
		i++;
	}
}

t_queue	*que_new()
{
	t_queue	*next_in_q;

	next_in_q = (t_queue*)malloc(sizeof(t_queue));
	next_in_q->next_in_q = NULL;
	next_in_q->room = NULL;
	return (next_in_q);
}

t_num_q	*n_que_new()
{
	t_num_q	*next_in_q;

	next_in_q = (t_num_q*)malloc(sizeof(t_num_q));
	next_in_q->next_in_q = NULL;
	next_in_q->nbr = -1;
	return (next_in_q);
}
void	n_queue_pop(t_num_q **q)
{
	t_num_q	*tmp;

	tmp = *q;
	if ((*q)->next_in_q)
		*q = (*q)->next_in_q;
	else
		*q = NULL;
	free(tmp);
}