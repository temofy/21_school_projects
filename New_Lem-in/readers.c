#include "lem-in.h"

int 	reading_rooms(char *str, t_map *map)
{
	char		**room;
	static int	i = 0;
	long		*value;
	int 		rtn;

	rtn = (!str) ? -1 : 1;
	room = ft_strsplit(str, ' ');
	rtn = (rtn == 1 && room && room[0][0] == 'L') ? -1 : 1;
	if (rtn == 1 && map->rooms)
	{
		map->rooms[i].name = ft_strdup(room[0]);
		value = ft_atopi(room[1]); //учесть передачу адреса
		if (value)
			map->rooms[i].x = (int)*value;
		else
			rtn = -1;
		value = ft_atopi(room[2]); // учесть передачу адреса
		if (value)
			map->rooms[i].y = (int)*value;
		else
			rtn = -1;
		i++;
	}
	ft_arrdel(&room);
	return (rtn);
}

int 	reading_se(char *str, t_room **se) // добавить очищение и на L проверку
{
	char		**room;
	long 		*value;
	int 		rtn;

	rtn = (!str || ft_count_words(str) != 3) ? -1 : 1;
	room = (rtn == 1) ? ft_strsplit(str, ' ') : NULL;
	*se = (rtn == 1) ? (t_room *) ft_memalloc(sizeof(t_room)) : NULL;
	rtn = (*se == NULL) ? -1 : 1;
	rtn = (rtn == 1 && room[0][0] == 'L') ? -1 : 1;
	if (rtn == 1)
	{
		(*se)->name = ft_strdup(room[0]);
		value = ft_atopi(room[1]);
		if (value)
			(*se)->x = (int) *value;
		else
			rtn = -1;
		value = ft_atopi(room[2]);
		if (value)
			(*se)->y = (int) *value;
		else
			rtn = -1;
	}
	ft_arrdel(&room);
	return (rtn);
}