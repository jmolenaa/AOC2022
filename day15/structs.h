#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct s_coordinates
{
	int					x;
	int					y;
	char				c;
	struct s_coordinates	*next;
}							t_coordinates;

typedef	struct s_sensor
{
	int		sensorx;
	int		sensory;
	int		beaconx;
	int		beacony;
	int		distance;
	struct s_sensor *next;
}			t_sensor;

typedef struct s_ranges
{
	int				xmin;
	int				xmax;
	struct s_ranges	*next;
}					t_ranges;

#endif