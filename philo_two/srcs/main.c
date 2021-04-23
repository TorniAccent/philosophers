#include "../includes/two.h"

// ok
int	main(int argc, char **argv)
{
	int		*val;
	t_init	init;

	if (argc < 5 || 6 < argc)
	{
		ft_print_error("Wrong number of arguments");
		return (-1);
	}
	val = ft_parse_args(argc, argv);
	if (!val)
		return (-1);
	if (!ft_init_init(val[0], &init))
		return (ft_destruct(&init, val));
	if (ft_threading(&init, argc, val) == -1)
		return (ft_destruct(&init, val));
	ft_destruct(&init, val);
	return (0);
}
