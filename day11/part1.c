#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"
#include "libft.h"
#include "day11.h"

int	main()
{
	t_monkey	*firstmonkey;
	firstmonkey = parseinput();
	print_monkeys(firstmonkey);
}