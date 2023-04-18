/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_splitter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoro-sa <imoro-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 12:01:29 by imoro-sa          #+#    #+#             */
/*   Updated: 2023/04/13 13:58:01 by imoro-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_str_counter(char const *s)
{
	char	c;
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\'' || s[i] == '"')
		{
			c = s[i];
			i++;
			while (s[i] != c && s[i] != '\0')
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

char	*ft_advance(char *str)
{
	while (*str == 32)
		str++;
	if (*str == '\'' || *str == '"')
		str++;
	return (str);
}

int	ft_splitter_len(char *str)
{
	int		len;
	char	c;

	len = 0;
	c = 0;
	if (str[len - 1] == 32 || str[len - 1] == '\'' || str[len - 1] == '"')
		c = str[len - 1];
	if (c != 0)
		while (str[len] != c && str[len] != 0)
			len++;
	else
		while (str[len] != 32 && str[len] != '\''
			&& str[len] != '"' && str[len] != 0)
				len++;
	return (len);
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

char	**ft_pipex_splitter(char *str)
{
	char	**str_return;
	int		size;
	int		len;
	int		n;

	n = 0;
	size = ft_str_counter(str);
	str_return = malloc(sizeof(char *) * size + 1);
	if (str_return == NULL)
		return (NULL);
	while (n < size)
	{
		str = ft_advance(str);
		len = ft_splitter_len(str);
		str_return[n] = ft_substr(str, 0, len);
		if (str_return[n] == NULL)
			return (ft_free_split(str_return, n), NULL);
		while (len-- >= 0)
			str++;
		n++;
	}
	str_return[n] = 0;
	return (str_return);
}
