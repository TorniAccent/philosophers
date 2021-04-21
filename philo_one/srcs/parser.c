#include "one.h"

static int	isdigit_arg(char **argv)
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

int	*check_args(int argc, char **argv)
{
	int		*val;
	int		i;

	i = -1;
	if (!isdigit_arg(argv))
	{
		ft_perror("Error: invalid value");
		return (NULL);
	}
	if (!(val = malloc(sizeof(int) * (argc - 1))))
	{
		ft_perror("Error: malloc error");
		return (NULL);
	}
	while (++i != (argc - 1))
	{
		val[i] = ft_atoi(argv[i + 1]);
		if (val[i] <= 0)
		{
			ft_perror("Error: invalid value");
			free(val);
			return (NULL);
		}
	}
	return (val);
}
