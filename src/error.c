#include "main.h"

void		myerror(char *mess)
{
	int r;

	(void)r;
	r = write(2, mess, ft_strlen(mess));
	exit(-1);
}