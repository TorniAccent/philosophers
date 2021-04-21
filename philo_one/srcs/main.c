#include "one.h"

int	main(int argc, char **argv)
{
	int				*val;
	int				b;
	t_init			*init;

	b = -1;
	if (argc < 5 || 6 < argc)
		ft_print_error("Wrong number of arguments");
	if (argc < 5 || 6 < argc)
		return (-1);
	val = ft_parse_args(argc, argv);
	if (!val)
		return (-1);
	init = malloc(sizeof(t_init));
	if (!init)
		return (ft_destruct(init, val));
	init = ft_init_init(val, init);
	if (!init)
		return (ft_destruct(init, val));
	if (ft_threading(init, argc, val) == -1)
		return (ft_destruct(init, val));
	ft_destruct(init, val);
	return (0);
}
