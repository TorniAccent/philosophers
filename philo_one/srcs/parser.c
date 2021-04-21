#include "one.h"

// up
static int	is_number(char **argv)
{
	int		i;
	int		a;

	i = 0;
	while (argv[++i])
	{
		a = -1;
		while (argv[i][++a])
			if (argv[i][a] < '0' || argv[i][a] > '9')
				return (0);
	}
	return (1);
}

// up
int	*ft_parse_args(int argc, char **argv)
{
	int		*val;
	int		i;

	i = -1;
	if (!is_number(argv))
	{
		ft_print_error("Error: invalid value");
		return (NULL);
	}
	val = malloc(sizeof(int) * (argc - 1));
	if (!val)
		ft_print_error("Error: malloc error");
	if (!val)
		return (NULL);
	while (++i != (argc - 1))
	{
		val[i] = ft_atoi(argv[i + 1]);
		if (val[i] <= 0)
		{
			ft_print_error("Error: invalid value");
			free(val);
			return (NULL);
		}
	}
	return (val);
}
