#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct s_jet
{
	char	*begin;
	char	*jetpattern;
}			t_jet;

typedef	struct s_rocks
{
	char	**rock;
	int		ymax;
	int		rockid;
	struct s_rocks	*nextrock;
}				t_rocks;

typedef struct s_chamber
{
	char	**chamber;
	int		ymax;
	int		currentheight;
	int		rockheight;
	int		bottomrock;
	int		rockid;
	int		leftrock;
	int		rockwidth;
}			t_chamber;


t_jet	*get_jet_pattern(void);
t_rocks	*get_rocks(void);


#endif