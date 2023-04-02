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

int	ft_str_counter(char const *s)
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

int	ft_splitter_len(char *str, int ptr)
{
	int		i;

	i = ptr;
	if (str[i - 1] == '\'' || str[i - 1] == '"')
	{
		while (str[i] != 0 && (str[i] != '\'' && str[i] != '"'))
			i++;
	}
	else if (str[i] == '\'' || str[i] == '"')
	{
		i++;
		while (str[i] != 0 && (str[i] != '\'' && str[i] != '"'))
			i++;
		i++;
	}
	else if (str[i - 1] == 32 || i == 0)
	{
		while (str[i] != 0 && str[i] != 32)
			i++;
	}
	return (i - ptr);
}

char	**ft_free_split(char **str, int n)
{
	while (n > 0)
	{
		free (str[n - 1]);
		n--;
	}
	free (str);
	return (NULL);
}

int	ft_advance(char *str, int len, int i)
{
	i = i + len;
	while (str[i] != 0 && str[i] != 32)
		i++;
	while (str[i] == 32)
		i++;
	if ((str[i] == '\'' || str[i] == '"')
		/*&& ft_strnstr(str, "awk", ft_strlen(str)) != NULL*/)
			i++;
	//ver si esto del awk es un error en linux. Funciona correctamente pero comandos como sed necesitan también no tener comillas
	return (i);
}

char	**ft_pipex_splitter(char *str)
{
	char	**str_return;
	int		malloc_len;
	int		len;
	int		i;
	int		n;

	i = 0;
	n = 0;
	len = 0;
	malloc_len = ft_str_counter(str);
	str_return = malloc(sizeof(char *) * (malloc_len + 1));
	if (str_return == NULL)
		return (NULL);
	while (n < malloc_len)
	{
		len = ft_splitter_len(str, i);
		str_return[n] = ft_substr(str, i, len);
		if (str_return[n] == NULL)
			return (ft_free_split(str_return, n));
		i = ft_advance(str, len, i);
		n++;
	}
	str_return[n] = 0;
	return (str_return);
}

// int	main(void)
// {
// 	char	str[] = "tr 'a' 'A'";
// 	char	**ptr;
// 	int		i = 0;

// 	ptr = ft_pipex_splitter(str);
// 	printf("\n");
// 	printf("\n");
// 	printf("\n");
// 	while (ptr[i] != NULL)
// 	{
// 		printf("%s\n", ptr[i]);
// 		i++;
// 	}
// 	return (0);
// }
