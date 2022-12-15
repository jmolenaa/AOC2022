#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct s_coordinates
{
	int					x;
	int					y;
	struct s_coordinates	*next;
}							t_coordinates;

typedef	struct s_sensor
{
	int		sensorx;
	int		sensory;
	int		beaconx;
	int		beacony;
	int		distance;
}			t_sensor;

#endif