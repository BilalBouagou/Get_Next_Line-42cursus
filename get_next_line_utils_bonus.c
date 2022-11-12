/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 15:22:22 by bbouagou          #+#    #+#             */
/*   Updated: 2022/11/05 13:25:05 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	char	*new_stash;

	if (buff == NULL)
		return (NULL);
	if (stash == NULL)
	{
		stash = (char *)malloc(1);
		if (stash == NULL)
			return (NULL);
		*stash = '\0';
	}
	size = ft_strlen(stash) + ft_strlen(buff);
	new_stash = (char *)malloc(size + 1);
	if (new_stash == NULL)
		return (NULL);
	copy(new_stash, stash, ft_strlen(stash));
	copy(new_stash + ft_strlen(stash), buff, ft_strlen(buff));
	free (stash);
	return (new_stash);
}
