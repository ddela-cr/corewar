/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_header.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddela-cr <ddela-cr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/18 17:44:12 by ddela-cr          #+#    #+#             */
/*   Updated: 2016/08/18 17:44:16 by ddela-cr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void		ft_get_comment(char *line, t_header *header)
{
	char	*start;
	int		len;

	start = ft_strchr(line, '"') + 1;
	len = 0;
	while (start[len] && start[len] != '"')
		len++;
	ft_strncpy(header->comment, start, len);
}

static void		ft_get_name(char *line, t_header *header)
{
	char	*start;
	int		len;

	start = ft_strchr(line, '"') + 1;
	len = 0;
	while (start[len] && start[len] != '"')
		len++;
	ft_strncpy(header->prog_name, start, len);
}

t_header		*ft_get_header(int fd)
{
	t_header	*header;
	char		*line;
	int			kind;

	if (!(header = (t_header *)malloc(sizeof(t_header))))
		return (NULL);
	kind = 0;
	header->magic = COREWAR_EXEC_MAGIC;
	while (get_next_line(fd, &line) > 0)
	{
		kind = line_kind(line);
		if (kind == IS_CHAMP_NAME)
			ft_get_name(line, header);
		else if (kind == IS_CHAMP_COMMENT)
			ft_get_comment(line, header);
		else
		{
			free(line);
			break;
		}
		free(line);
	}
	lseek(fd, 0, SEEK_SET);
	return (header);
}