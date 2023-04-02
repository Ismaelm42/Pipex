#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int	ft_len_counter(char *str)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (str[i] != 0)
	{
		if ((str[i] != 32 && str[i] != '\t' && str[i] != '\n')
			&& (str[i + 1] == 32 || str[i + 1] == '\t' || str[i + 1] == '\n' || str[i + 1] == '\0'))
		{
			counter++;
			i++;
		}
		else
			i++;
	}
	return (counter);
}

int	ft_advance(char *str)
{
	int	i;

	i = 0;
	if (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' || str[i] == '\0')
		return (1);
	else
		return (0);
}

char	*ft_string(char *str)
{
	char	*new_str;
	int		i;

	i = 0;
	while (str[i] != ' ' && str[i] != '\t' && str[i] != '\n' && str[i] != '\0')
		i++;
	new_str = malloc(sizeof(char) * i + 1);
	if (new_str == NULL)
		return (NULL);
	i = 0;
	while (str[i] != ' ' && str[i] != '\t' && str[i] != '\n' && str[i] != '\0')
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}

char	**ft_split(char *str)
{
	char	**str_return;
	int		i;
	int		len;

	i = 0;
	len = ft_len_counter(str);
	str_return = malloc(sizeof(char *) * len + 1);
	if (str_return == NULL)
		return (NULL);
	while (i < len)
	{
		while (ft_advance(str) != 0)
			str++;
		str_return[i] = ft_string(str);
		while (ft_advance(str) == 0)
			str++;
		i++;
	}
	str_return[i] = 0;
	return (str_return);
}

int	main(void)
{
	char	str[] = "Hola, buenos dias     ";
	char	**ptr;

	ptr = ft_split(str);
	printf("%s", ptr[7]);
	return (0);
}