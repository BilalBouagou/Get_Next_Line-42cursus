/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 14:01:09 by bbouagou          #+#    #+#             */
/*   Updated: 2022/11/05 13:26:20 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	if (!s)
		return (1);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(char *s, int c)
{
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	while (i <= ft_strlen(s))
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	return (NULL);
}

void	copy(char *dst, char *src, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}

char	*push_to_stash(char *stash, char *buff)
{
	size_t	size;
	size_t	size_stash;
	size_t	size_buff;
	char	*new_stash;

	if (stash == NULL)
	{
		stash = (char *)malloc(1);
		if (stash == NULL)
			return (NULL);
		*stash = '\0';
	}
	size_stash = ft_strlen(stash);
	size_buff = ft_strlen(buff);
	size = size_stash + size_buff;
	new_stash = (char *)malloc(size + 1);
	if (new_stash == NULL)
		return (NULL);
	copy(new_stash, stash, size_stash);
	copy(new_stash + size_stash, buff, size_buff);
	free (stash);
	return (new_stash);
}
