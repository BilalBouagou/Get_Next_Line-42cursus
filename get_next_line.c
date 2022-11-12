/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 14:01:23 by bbouagou          #+#    #+#             */
/*   Updated: 2022/11/05 16:45:25 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
** This function is called one a line has been extracted, it's used
** to remove the extracted line from the stash.
** It starts by skipping the line that was returned (same logic
** used in grab_line()).
** After the line was skipped, it checks if the current character
** is not a NUL-terminator (as that would mean the line to be
** removed is the last line in the file), and the character after
** the current character isn't a NUL-terminator (as that would mean
** the last line was a \n).
** If that's the case, then it simply frees the stash and NULL is returned.
** Otherwise the length of the stash minus the index of the last character
** of the returned line is allocated to the new stash, and new stash is
** then filled with remaining characters using the function copy, which
** takes the new stash, the stash plus the index of character plus one
** (because we do not want to include the last character in the copying)
** and the lenght of the stash minus the index minus one is fed as a
** the number of characters to be copied (- 1 because the NUL-terminator
** should not be taken into consideration when using the function copy())
** Lastly, the stash is freed and new stash is returned.
*/

char	*clean_stash(char *stash)
{
	char	*new_stash;
	int		i;

	i = 0;
	while (stash[i] != '\n' && stash[i])
		i++;
	if (stash[i] != '\0' && stash[i + 1] != '\0')
	{
		new_stash = (char *)malloc(ft_strlen(stash) - i);
		if (new_stash == NULL)
			return (NULL);
		copy(new_stash, stash + i + 1, ft_strlen(stash) - i - 1);
		free (stash);
		return (new_stash);
	}
	free (stash);
	return (NULL);
}

/*
** This function extractes a valid line to be returned from the stash.
** The stash fed to the grab_line() is guaranteed to have a valid line
** to return, that's because if the stash gets empty, it will be
** caught in the process_file() function.
** The function starts by skipping the characters as long as they're
** != \n and the stash hasn't ended yet (because push_to_stash() function
** does NUL-terminate the stash).
** After skipping the line, there are two cases, either the line contains
** \n, or the line is the last line in the file.
** If it's the first case then it allocates an additional two bytes,
** one for the \n, and one for the NUL-terminator.
** Otherwise, it just allocates an extra byte for the NUL-terminator.
** It then copies the line in the variable menace, using the function
** copy(), which takes a dst, an src, and how much charactes to be copied
** fed i because i has been incremented in the allocation. 
*/

char	*grab_line(char *stash)
{
	int		i;
	char	*menace;

	i = 0;
	while (stash[i] != '\n' && stash[i])
		i++;
	if (!stash[i])
		menace = (char *)malloc(i + 1);
	else
		menace = (char *)malloc(i + 2);
	if (menace == NULL)
		return (NULL);
	if (!stash[i])
		copy(menace, stash, i);
	else
		copy(menace, stash, i + 1);
	return (menace);
}

/*
** This function takes both the file descriptor and the stash as params
** it attempts to read from the fd and stores what it read until either
** a valid line is read or EOF is reached.
** It starts by first allocating the buff with the provided buffer size
** it adds one to the number of bytes to be allocated (room of '\0')
** just in case the buffer size equals or less than the actual line read.
** It then sets bytes_read to 1 to enter the loop, it keeps reading as long
** as \n character hasn't been encountered and bytes_read is greater than 0.
** To check if the stash has a \n character in it, it simply uses strchr of
** the lenght of the stash minus the bytes read as to only search the newly
** added buffer for the \n (FOR OPTIMISATION!!!!).
** If it attempts to read but it reaches EOF and the stash is NULL, it frees
** the buffer and returns NULL, it does that because the only cases in which
** that condition is going to be true is when the file was empty or the lines
** have already been read and there's nothing left to read.
** After it reads, it sets the byte that's beside the last character
** read to \0 because the function read() does not produce NUL-terminated
** string on it's own. It then uses the push_to_stash() function to concat
** both the stash (containing what was previously read or NULL if it was never
** filled before) and the buffer. Lastly, it sets size to the lenght of the
** stash - 1, as to only search the new characters what were read in the next
** iteration for optimisation purposes.
** if there's nothing else to read (either because \n was encountered or
** EOF was reached), the buffer is freed and NULL is returned.
*/

char	*process_file(int fd, char *stash)
{
	char	*buff;
	ssize_t	bytes_read;

	buff = (char *)malloc(BUFFER_SIZE + 1);
	if (buff == NULL)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(&stash[ft_strlen(stash) - bytes_read], '\n')
		&& bytes_read)
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if ((bytes_read == 0 && stash == NULL) || bytes_read < 0)
		{
			if (stash)
				free (stash);
			free (buff);
			return (NULL);
		}
		buff[bytes_read] = '\0';
		stash = push_to_stash(stash, buff);
	}
	free (buff);
	return (stash);
}

/*
** the get_next_line function reads from an fd and returns a line read form
** that fd, one line at a time, in case of failure, the function returns
** NULL.
*/

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*return_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = process_file(fd, stash);
	if (stash == NULL)
		return (NULL);
	return_line = grab_line(stash);
	stash = clean_stash(stash);
	return (return_line);
}
