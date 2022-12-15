#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"
#include "libft.h"
#include "structs.h"

t_coordinates *make_new(char x, char y)
{
	t_coordinates *new;

	new = malloc(sizeof(t_coordinates));
	new->x = x;
	new->y = y;
	new->next = NULL;
	return (new);
}

void	add_front_coordinate(t_coordinates **head, t_coordinates *new)
{
	new->next = *head;
	*head = new;
}

void	check_if_in_list_and_add(t_coordinates **head, int x, int y)
{
	t_coordinates	*new;
	t_coordinates	*temp;

	temp = *head;
	while (temp != NULL)
	{
		if (x == temp->x)
			return ;
		temp = temp->next;
	}
	new = make_new(x, y);
	add_front_coordinate(head, new);
}

t_sensor	get_distance_and_position(char *str)
{
	t_sensor	sensor;
	sscanf(str, "%*s %*s x=%d, y=%d: %*s %*s %*s %*s x=%d, y=%d",\
	&sensor.sensorx, &sensor.sensory, &sensor.beaconx, &sensor.beacony);
	sensor.distance = abs(sensor.sensorx - sensor.beaconx) + abs(sensor.sensory - sensor.beacony);
	// printf("\nsensor:\n%d, %d\n%d %d\n%d\n", sensor.sensorx, sensor.sensory, sensor.beaconx, sensor.beacony, sensor.distance);
	return (sensor);
}

void	check_positions_and_add_to_list(t_coordinates **head, t_sensor sensor)
{
	int				row_to_check = 10;
	t_coordinates	*new;
	int				distance_sensor_row = abs(sensor.sensory - row_to_check);

	while (distance_sensor_row >= sensor.distance)
	{
		if (distance_sensor_row - sensor.distance == 0)
		{
			check_if_in_list_and_add(head, sensor.sensorx, row_to_check);
			// new = make_new(sensor.sensorx, row_to_check);
			// add_front_coordinate(head, new);
		}
		else
		{
			check_if_in_list_and_add(head, sensor.sensorx - distance_sensor_row, row_to_check);
			// new = make_new(sensor.sensorx - distance_sensor_row, row_to_check);
			// add_front_coordinate(head, new);
			check_if_in_list_and_add(head, sensor.sensory + distance_sensor_row, row_to_check);
			// new = make_new(sensor.sensory + distance_sensor_row, row_to_check);
			// add_front_coordinate(head, new);
		}
		distance_sensor_row--;
	}
}

void	printlist(t_coordinates *head)
{
	int	i;

	while (head != (NULL))
	{
		printf("%d, %d\n", head->x, head->y);
		head = head->next;
		i++;
	}
	printf("%d\n", i);
}

int	main()
{
	int				fd = open("test", O_RDONLY);
	char			*str;
	t_sensor		sensor;
	t_coordinates	*head = NULL;

	while (1)
	{
		str = get_next_line(fd);
		if (str == NULL)
			break ;
		sensor = get_distance_and_position(str);
		check_positions_and_add_to_list(&head, sensor);
		printlist(head);
	}
}