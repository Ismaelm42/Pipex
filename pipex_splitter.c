/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_splitter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoro-sa <imoro-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 12:01:29 by imoro-sa          #+#    #+#             */
/*   Updated: 2023/03/31 19:49:28 by imoro-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_len_malloc(char const *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\'' || s[i] == '"')
		{
			i++;
			while (s[i] != '\'' && s[i] != '"' && s[i] != '\0')
				i++;
		}
		if (s[i] != 32 && (s[i + 1] == 32 || s[i + 1] == '\0'))
		{
			count++;
			i++;
		}
		else
			i++;
	}
	return (count);
}

int	ft_string_len(char *str, int i)
{
	int		len;

	len = 0;
	if (str[i - 1] == '\'' || str[i - 1] == '"')
	{
		while (str[i] != 0 && str[i] != '\'' && str[i] != '"')
		{
			i++;
			len++;
		}
	}
	else if (str[i - 1] == 32 || i == 0)
	{
		if (i != 0)
			i++;
		while (str[i] != 0 && str[i] != 32)
		{
			i++;
			len++;
		}
	}
	return (len);
}

int	ft_advance(char *str, int i)
{
	while (str[i] != 0 && str[i] != 32)
		i++;
	while (str[i] == 32)
		i++;
	i--;
	if (str[i + 1] == '\'' || str[i + 1] == '"')
		i++;
	i++;
	return (i);
}

char	**ft_pipex_splitter(char *str)
{
	char	**str_return;
	int		i;
	int		n;
	int		len;

	i = 0;
	n = 0;
	len = ft_len_malloc(str);
	printf("len = %d\n", len);
	str_return = malloc(sizeof(char *) * len);
	if (str_return == NULL)
		return (NULL);
	while (n < len)
	{
		str_return[n] = ft_substr(str, i, ft_string_len(str, i));
		printf("str_return[%d] = %s\n", n, str_return[n]);
		printf("len = %d\n", ft_string_len(str, i));
		i = ft_advance(str, i);
		printf("i = %d\n", i);
		printf("n = %d\n", n);
		n++;
	}
	str_return[n] = 0;
	printf("str_return[%d] = %s", n, str_return[n]);
	return (str_return);
}

int	main(void)
{
	char	str[] = "awk hola1 hola2   'ahora viene lo chungo3'   hola4 'travez5'";
	char	**prueba;

	//printf("string_len = %d\n", ft_string_len(str, 0));
	prueba = ft_pipex_splitter(str);
	// printf("%s\n", prueba[0]);
	// printf("%s\n", prueba[1]);
	// printf("%s\n", prueba[2]);
	return (0);
}
