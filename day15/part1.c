#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"
#include "libft.h"
#include "structs.h"

void	add_to_string(int x, int y, char c, char *str_row_we_look_for)
{
	x = x + 1000000;
	if (*(str_row_we_look_for + x) != 'B')
		*(str_row_we_look_for + x) = c;
}

t_sensor	get_distance_and_position(char *str)
{
	t_sensor	sensor;
	sscanf(str, "%*s %*s x=%d, y=%d: %*s %*s %*s %*s x=%d, y=%d",\
	&sensor.sensorx, &sensor.sensory, &sensor.beaconx, &sensor.beacony);
	sensor.distance = abs(sensor.sensorx - sensor.beaconx) + abs(sensor.sensory - sensor.beacony);
	return (sensor);
}

void	check_positions_and_add_to_string(t_sensor sensor, char *str_row_we_look_for)
{
	int				row_to_check = 2000000;
	int				distance_sensor_row = abs(sensor.sensory - row_to_check);

	while (distance_sensor_row <= sensor.distance)
	{
		if (distance_sensor_row - sensor.distance == 0)
		{
			add_to_string(sensor.sensorx, row_to_check, '#', str_row_we_look_for);
		}
		else
		{
			add_to_string(sensor.sensorx - (sensor.distance - distance_sensor_row), row_to_check, '#', str_row_we_look_for);
			add_to_string(sensor.sensorx + (sensor.distance - distance_sensor_row), row_to_check, '#', str_row_we_look_for);
		}
		distance_sensor_row++;
	}
}

void	count_pounds(char *str_row_we_look_for)
{
	int	i = 0;
	int	j = 0;

	while (*(str_row_we_look_for + i) != '\0')
	{
		if (*(str_row_we_look_for + i) == '#')
			j++;
		i++;
	}
	printf("%d\n", j);
}

int	main()
{
	int				fd = open("input", O_RDONLY);
	char			*str;
	t_sensor		sensor;
	char			*str_row_we_look_for = (char *)ft_calloc(20000001, sizeof(char));
	ft_memset(str_row_we_look_for, '.', 20000000);

	while (1)
	{
		str = get_next_line(fd);
		if (str == NULL)
			break ;
		sensor = get_distance_and_position(str);
		if (sensor.beacony == 2000000)
			add_to_string(sensor.beaconx, sensor.beacony, 'B', str_row_we_look_for);
		check_positions_and_add_to_string(sensor, str_row_we_look_for);
	}
	count_pounds(str_row_we_look_for);
}