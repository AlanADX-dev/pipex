#include "pipex.h"

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(2, &str[i], 1);
		i++;
	}
}

void	ft_error(char *msg)
{
	ft_putstr(msg);
	exit(1);
}

char    *ft_gnl(int fd)
{
    char	*res;
	int		size;

	res = malloc(sizeof(char) * 100);
	if (!res)
		ft_error("ERROR : Malloc error\n");
	size = read(fd, res, 100);
	if (size == -1)
	{
		free(res);
		ft_error("ERROR : Read error\n");
	}
	if (size == 0)
	{
		res[0] = '\0';
		return (res);
	}
	res[size - 1] = '\0';
	return (res);
}

void    ft_freeargs(char **cmd)
{
    int     i;

    i = 0;
    while(cmd[i])
    {
        free(cmd[i]);
        i++;
    }
    free(cmd);
}
