#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H


#include <unistd.h>
#include <stdlib.h>
#include <string.h>

# define BUFF_SIZE 32

# define MALLCHECK(x) if (!x) return (-1);
# define ERRCHECK(x, y, z) if (x < 0 || y == NULL || z < 0) return (-1);

typedef struct		s_file
{
	char			reserv[BUFF_SIZE + 1];
	int				fd;
	struct s_file	*next;
}					t_file;

int	get_next_line(int fd, char **line);

#endif