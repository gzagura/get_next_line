/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzagura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/24 20:45:58 by gzagura           #+#    #+#             */
/*   Updated: 2018/03/24 20:46:00 by gzagura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int				main(void)
{
	char		*line;
	int			fd;
	int			ret;
	int			count_lines;
	char		*filename;
	int			errors;

	filename = "gnl7_1.txt";
	fd = open(filename, O_RDONLY);
	line = NULL;
	ret = 0;
	
	//char	*lolo;

	//lolo = "taras molodec\ngleb toje molodec";
	//printf("%s\n",ft_strchr(lolo, '\n'));

	count_lines = 0;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		count_lines++;
		printf("%s\n",line);
	}
	printf("count_lines = %d\n", count_lines);
	return (0);
}


t_getlist	*ft_newlist(int fd)
{
	t_getlist	*new;

	new = (t_getlist*)malloc(sizeof(t_getlist));
	new->next = NULL;
	new->content = ft_strnew(BUFF_SIZE);
	new->num_fd = fd;
	return (new);
}

t_getlist	*ft_worklist(t_getlist *head, int fd)
{
	if (head == NULL)
	{
		head = ft_newlist(fd);
		return (head);
	}
	while (head != NULL)
	{
		if(head->num_fd == fd)
			return (head);
		else if (head->next)
			head = head->next;
		else
			break ;
	}
	head->next = ft_newlist(fd);
	return (head->next);
}

int		ft_crazy(char *buffe, int fd, char **line, int bytes)
{
	static t_getlist *tmp = NULL;
	t_getlist *head;
	char *suka;

	*line = NULL;
	if (!tmp)
	{
		tmp = ft_worklist(tmp, fd);
		head = tmp;
	}
	else
		head = ft_worklist(tmp, fd);
	*line = ft_strjoin(head->content, buffe);
	free(head->content);
	//ft_bzero(head->content, ft_strlen(head->content));
	head->content = ft_strdup(*line);
	free(*line);
	if (ft_strchr(head->content, '\n')) 
	{
        *line = ft_strsub(head->content, 0, (int)(ft_strchr(head->content, '\n') - head->content));
        suka = ft_strdup(ft_strchr(head->content, '\n') + 1);
        ft_bzero(head->content, ft_strlen(head->content));
        head->content = ft_strdup(suka);
        // printf("suka = %s\n",suka );
        //printf("!---! %s\n?---?\n", suka);
        return (1);
    }
    if (bytes == 0 && ft_strchr(head->content, '\0'))
    {
    	*line = ft_strsub(head->content, 0, (int)(ft_strchr(head->content, '\0') - head->content));
        suka = ft_strdup(ft_strchr(head->content, '\n') + 1);
        ft_bzero(head->content, ft_strlen(head->content));
        head->content = ft_strdup(suka);
    }
    // if (ft_strchr(head->content, '\n') )
    // {
    // 	/* code */
    // }
	return (0);
}

int		get_next_line(const int fd, char **line)
{
	int		bytes = 1;
    int     re = 1;
	char	buffe[BUFF_SIZE + 1];

	buffe[BUFF_SIZE] = '\0';

	if (!line)
		return (-1);
	while ((bytes = read(fd, buffe, BUFF_SIZE)) > -1)
	{
		while (ft_crazy(buffe, fd, line, bytes) != 0)
		{
			return (1);
		}
		if (bytes == 0)
			return(0);
        if (bytes < 0)
            return (-1);
        return (0);
	}
	return (0);
}

