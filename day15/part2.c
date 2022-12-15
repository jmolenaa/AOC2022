#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"
#include "libft.h"
#include "structs.h"

t_sensor	*make_new_sensor(char *str)
{
	t_sensor	*sensor = (t_sensor *)malloc(sizeof(t_sensor));
	sscanf(str, "%*s %*s x=%d, y=%d: %*s %*s %*s %*s x=%d, y=%d",\
	&sensor->sensorx, &sensor->sensory, &sensor->beaconx, &sensor->beacony);
	sensor->distance = abs(sensor->sensorx - sensor->beaconx) + abs(sensor->sensory - sensor->beacony);
	sensor->next = NULL;
	return (sensor);
}

void	add_sensor_front(t_sensor **head, t_sensor *new)
{
	new->next = *head;
	*head = new;
}

void	printsensors(t_sensor *head)
{
	t_sensor *temp;
	while (head != NULL)
	{
		printf("\nsensor\n%d %d\n%d %d\n%d\n", head->sensorx, head->sensory, head->beaconx, head->beacony, head->distance);
		head = head->next;
	}
}

t_sensor	*get_sensor_list(void)
{
	int				fd = open("input", O_RDONLY);
	char			*str;
	t_sensor		*sensor;
	t_sensor		*head;

	head = NULL;
	while (1)
	{
		str = get_next_line(fd);
		if (str == NULL)
			break ;
		sensor = make_new_sensor(str);
		add_sensor_front(&head, sensor);
	}
	return (head);
}

t_ranges	*make_range_for_sensor(t_sensor *head, int y)
{
	int	distance_from_sensor_to_y = abs(head->sensory - y);
	t_ranges *new = NULL;
	if (distance_from_sensor_to_y <= head->distance)
	{
		new = (t_ranges *)malloc(sizeof(t_ranges));
		new->xmin = head->sensorx - (head->distance - distance_from_sensor_to_y);
		if (new->xmin < 0)
			new->xmin = 0;
		new->xmax = head->sensorx + (head->distance - distance_from_sensor_to_y);
		if (new->xmax > 4000000)
			new->xmax = 4000000;
		new->next = NULL;
	}
	return (new);
}

void	add_to_range_list(t_ranges **head, t_ranges *new)
{
	if (new == NULL)
		return ;
	new->next = *head;
	*head = new;
}

void	check_range(t_ranges *temp, int *minimumx, int *maximumx)
{
	if (temp->xmin <= *minimumx && temp->xmax >= *minimumx)
		*minimumx = temp->xmin;
	if (temp->xmax >= *maximumx && temp->xmin <= *maximumx)
		*maximumx = temp->xmax;
}

int	look_for_empty_spot(t_ranges *firstrange)
{
	int 		minimumx;
	int			maximumx;
	t_ranges	*temp;
	t_ranges	*head;

	minimumx = firstrange->xmin;
	maximumx = firstrange->xmax;
	head = firstrange;
	while (firstrange != (NULL))
	{
		temp = head;
		while (temp != NULL)
		{
			check_range(temp, &minimumx, &maximumx);
			temp = temp->next;
		}
		firstrange = firstrange->next;
		if (minimumx == 0 && maximumx == 4000000)
			return (-1);
	}
	if (maximumx == 4000000)
		return (minimumx - 1);
	else
		return (maximumx + 1);
}

void	printranges(t_ranges *firstrange)
{
	while (firstrange != NULL)
	{
		printf("%d %d\n", firstrange->xmin, firstrange->xmax);
		firstrange = firstrange->next;
	}
}

int	check_for_row_y(t_sensor *head, int y)
{
	t_ranges	*new;
	t_ranges	*firstrange;

	firstrange = NULL;
	while (head != NULL)
	{
		new = make_range_for_sensor(head, y);
		add_to_range_list(&firstrange, new);
		head = head->next;
	}
	// printf("\nrow y %d\n", y);
	// printranges(firstrange);
	return (look_for_empty_spot(firstrange));
}

void	find_beacon(t_sensor *head)
{
	int y = 0;
	int	x = 0;

	while (y < 4000001)
	{
		x = check_for_row_y(head, y);
		if (x != -1)
			break;
		y++;
	}
	printf ("beacon coordinates %d %d\n", x , y);
}

int	main()
{
	t_sensor		*head;

	head = get_sensor_list();
	// printsensors(head);
	find_beacon(head);

}