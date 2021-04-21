#include "one.h"

static int	is_number(char **argv)
{
	int		i;
	int		a;

	i = 1;
	while (argv[i] != NULL)
	{
		a = 0;
		while (argv[i][a] != '\0')
		{
			if (argv[i][a] < 48 || argv[i][a] > 57)
				return (0);
			a++;
		}
		i++;
	}
	return (1);
}

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
	if (!(val = malloc(sizeof(int) * (argc - 1))))
	{
		ft_print_error("Error: malloc error");
		return (NULL);
	}
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
