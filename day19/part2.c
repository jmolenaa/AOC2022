#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"
#include "libft.h"
#include "structs.h"
#include <math.h>

void	get_geodes(t_blueprint *blueprint, t_stones stones, int minutes);

void	print_blueprint(t_blueprint *blueprint)
{
	printf("Blueprint %d\nCost of ore robot : %f ore\nCost of clay robot %f ore\n", blueprint->id, blueprint->cost_of_ore, blueprint->cost_of_clay);
	printf("Cost of obsidian robot: %f ore, %f clay\nCost of geode robot : %f ore, %f obsidian\n", *(blueprint->cost_of_obsidian), *(blueprint->cost_of_obsidian + 1), *blueprint->cost_of_geode, *(blueprint->cost_of_geode + 1));
}

void	printstones(t_stones *stones)
{
	printf("Amount of stones:\nore : %d, clay : %d, obsidian: %d, geodes: %d\n", (int)stones->ore, (int)stones->clay, (int)stones->obsidian, (int)stones->geode);
	printf("robots :\nore : %d, clay : %d, obsidian : %d, geode : %d\n", (int)stones->orerobot, (int)stones->clayrobot, (int)stones->obsrobot, (int)stones->geoderobot);
}

t_stones	make_stones(void)
{
	t_stones	stones;
	stones.ore = 0;
	stones.clay = 0;
	stones.obsidian = 0;
	stones.geode = 0;
	stones.orerobot = 1;
	stones.clayrobot = 0;
	stones.obsrobot = 0;
	stones.geoderobot = 0;
	return (stones);
}

void	add_stones(t_stones *stones)
{
	stones->ore = stones->ore + stones->orerobot - *stones->made;
	stones->clay = stones->clay + stones->clayrobot - *(stones->made + 1);
	stones->obsidian = stones->obsidian + stones->obsrobot - *(stones->made + 2);
	stones->geode = stones->geode + stones->geoderobot - *(stones->made + 3);
}

void	make_geode_robot(t_stones stones, t_blueprint *blueprint, int minutes)
{
	if (stones.obsidian >= *(blueprint->cost_of_geode + 1) && stones.ore >= *(blueprint->cost_of_geode))
	{
		stones.geoderobot++;
		stones.obsidian = stones.obsidian - *(blueprint->cost_of_geode + 1);
		stones.ore = stones.ore - *(blueprint->cost_of_geode);
		(*(stones.made + 3))++;
		add_stones(&stones);
		get_geodes(blueprint, stones, minutes + 1);
	}
}

void	make_obsidian_robot(t_stones stones, t_blueprint *blueprint, int minutes)
{
	if (stones.clay >= *(blueprint->cost_of_obsidian + 1) && stones.ore >= *(blueprint->cost_of_obsidian))
	{
		stones.obsrobot++;
		stones.clay = stones.clay - *(blueprint->cost_of_obsidian + 1);
		stones.ore = stones.ore - *(blueprint->cost_of_obsidian);
		(*(stones.made + 2))++;
		add_stones(&stones);
		get_geodes(blueprint, stones, minutes + 1);
	}
}

void	make_clay_robot(t_stones stones, t_blueprint *blueprint, int minutes)
{
	if (stones.ore >= blueprint->cost_of_clay)
	{
		stones.clayrobot++;
		stones.ore = stones.ore - blueprint->cost_of_clay;
		(*(stones.made + 1))++;
		add_stones(&stones);
		get_geodes(blueprint, stones, minutes + 1);
	}
}

void	make_ore_robot(t_stones stones, t_blueprint *blueprint, int minutes)
{
	if (stones.orerobot >= blueprint->cost_of_clay && stones.orerobot >= *(blueprint->cost_of_obsidian)\
		&& stones.orerobot >= *blueprint->cost_of_geode)
		return ;
	if (stones.ore >= blueprint->cost_of_ore)
	{
		stones.orerobot++;
		stones.ore = stones.ore - blueprint->cost_of_ore;
		(*stones.made)++;
		add_stones(&stones);
		get_geodes(blueprint, stones, minutes + 1);
	}
}

void	set_checks(t_stones *stones)
{
	*stones->made = 0;
	*(stones->made + 1) = 0;
	*(stones->made + 2) = 0;
	*(stones->made + 3) = 0;
}

int	check_for_max(t_stones stones, int minutes, t_blueprint *blueprint)
{
	int	geodes = stones.geode;

	while (minutes < 33)
	{
		geodes = geodes + stones.geoderobot;	
		stones.geoderobot++;
		minutes++;
	}
	if (geodes < blueprint->amount_of_geodes)
		return (1);
	return (0);
}

void	get_geodes(t_blueprint *blueprint, t_stones stones, int minutes)
{
	if (minutes < 33)
	{
		if (check_for_max(stones, minutes, blueprint))
			return ;
		set_checks(&stones);
		make_geode_robot(stones, blueprint, minutes);
		make_obsidian_robot(stones, blueprint, minutes);
		make_clay_robot(stones, blueprint, minutes);
		make_ore_robot(stones, blueprint, minutes);
		add_stones(&stones);
		get_geodes(blueprint, stones, minutes + 1);
	}
	else
	{
		if (stones.geode > blueprint->amount_of_geodes)
			blueprint->amount_of_geodes = stones.geode;
	}
}

int	main()
{
	int	fd = open("inputpart2", O_RDONLY);
	t_blueprint *blueprint;
	t_stones stones;
	int	multiplication = 1;

	int i = 0;
	while (1)
	{
		stones = make_stones();
		i++;
		blueprint = get_blueprint(fd);
		if (blueprint == NULL)
			break ;
		get_geodes(blueprint, stones, 1);
		// print_blueprint(blueprint);
		printf("%d : %d\n", blueprint->id, blueprint->amount_of_geodes);
		multiplication = multiplication * blueprint->amount_of_geodes;
		free(blueprint);
		// printf("%d\n", blueprint->amount_of_geodes);
	}
	printf("%d\n", multiplication);
}
