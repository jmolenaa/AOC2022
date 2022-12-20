#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct s_blueprint
{
	int	id;
	double	cost_of_ore;
	double	cost_of_clay;
	double	cost_of_obsidian[2];
	double	cost_of_geode[2];
	int		amount_of_geodes;
}	t_blueprint;

typedef	struct s_stones
{
	double	ore;
	double	clay;
	double	obsidian;
	double	geode;
	double	orerobot;
	double	clayrobot;
	double	obsrobot;
	double	geoderobot;
	int		made[4];
}		t_stones;

t_blueprint	*get_blueprint(int fd);

#endif