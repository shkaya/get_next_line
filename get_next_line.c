/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkaya <shkaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 14:35:51 by shuntakaya        #+#    #+#             */
/*   Updated: 2024/05/16 17:18:19 by shkaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// safely free func
static void	safe_free(char **ptr)
{
	if (ptr != (char **)0 && *ptr != (char *)0)
	{
		free(*ptr);
		*ptr = (char *)0;
	}
}

// read a line containing '\n' from file
// Save the line in basin_char
static int	read_and_save(int fd, char **basin_char)
{
	char	*buff;
	char	*basin_tmp;
	int		count_bytes;

	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buff == (char *)0)
		return (-1);
	while (1)
	{
		count_bytes = read(fd, buff, BUFFER_SIZE);
		if (count_bytes < 0)
			return (free(buff), -1);
		if (count_bytes == 0)
			break ;
		buff[count_bytes] = '\0';
		basin_tmp = *basin_char;
		*basin_char = ft_strjoin(*basin_char, buff);
		if (*basin_char == (char *)0)
			return (safe_free(&basin_tmp), free(buff), -1);
		safe_free(&basin_tmp);
		if (ft_strchr(*basin_char, '\n'))
			break ;
	}
	free(buff);
	return (0);
}

// Get string until '\n'
// if (still continuing) else (EOF)
// Sava string after '\n'
static char	*get_str_and_save(char **basin_char)
{
	char	*line;
	char	*newline_address;
	size_t	len;

	newline_address = ft_strchr(*basin_char, '\n');
	if (newline_address)
		len = newline_address - *basin_char + 1;
	else
		len = ft_strlen(*basin_char);
	line = (char *)malloc(sizeof(char) * (len + 1));
	if (!line)
		return ((char *)0);
	ft_memmove(line, *basin_char, len);
	line[len] = '\0';
	if (newline_address)
	{
		newline_address++;
		len = ft_strlen(newline_address);
		ft_memmove(*basin_char, newline_address, len + 1);
	}
	else
		safe_free(basin_char);
	return (line);
}

// get one line from file
char	*get_next_line(int fd)
{
	static char	*basin_char[MAX_FILE_DESCRIPTOR];
	char		*line;

	if (fd < 0 || fd > MAX_FILE_DESCRIPTOR)
		return ((char *)0);
	if (basin_char[fd] == (char *)0)
		basin_char[fd] = ft_strdup("");
	if (!basin_char[fd])
		return ((char *)0);
	if (read_and_save(fd, &basin_char[fd]) == -1 || *basin_char[fd] == '\0')
	{
		safe_free(&basin_char[fd]);
		return ((char *)0);
	}
	line = get_str_and_save(&basin_char[fd]);
	if (!line)
	{
		safe_free(&basin_char[fd]);
		return ((char *)0);
	}
	return (line);
}

// __attribute__((destructor))
// static void destructor() {
//     system("leaks -q a.out");
// }

// #include <fcntl.h>
// #include <stdio.h>
// int	main(void)
// {
// 	int	fd;
// 	char	*str;
// 	// char	*str2;

// 	fd = open("test.txt", O_RDONLY);
// 	str = get_next_line(fd);
// 	// str2 = get_next_line(fd);
//     close(fd);
// 	printf("%s", str);
// 	// printf("%s", str2);

// 	// fd = 0;
// 	// str = get_next_line(fd);
// 	// close(fd);
// 	// printf("%s", str);
// 	// free(str);

// 	free(str);
// 	// free(str2);
//     return (0);
// }