#include "one.h"

int				main(int argc, char **argv)
{
	int				*val;
	int				b;
	t_init			*init;

	b = -1;
	if (argc < 5 || 6 < argc)
		ft_perror("Wrong number of arguments");
	if (argc < 5 || 6 < argc)
		return (-1);
	if (!(val = check_args(argc, argv)))
		return (-1);
	if (!(init = malloc(sizeof(t_init))))
		return (deinit(init, val));
	if (!(init = main_init(val, init)))
		return (deinit(init, val));
	if (threading(init, argc, val) == -1)
		return (deinit(init, val));
	deinit(init, val);
	return (0);
}
