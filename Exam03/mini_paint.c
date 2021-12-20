#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

typedef struct s_tab
{
	int width;
	int height;
	char c;
}	t_tab;

typedef struct s_circle
{
	char fill;
	float x;
	float y;
	float radius;
	char c;
}	t_circle;

int main(int argc, char **argv)
{
	FILE *fd;
	t_tab tab;
	t_circle circle;
	int scan;
	int i;
	int j;
	float distance;
	char **cadre;

	i = 0;
	j = 0;
	distance = 0;
	scan = 0;
	if (argc != 2)
	{
		write (1, "Error: argument\n", 16);
		return (1);
	}
	fd = fopen(argv[1], "r");
	if (fd == NULL)
	{
		write(1, "Error: Operation file corrupted\n", 32);
		return (1);
	}
	if (fscanf(fd, "%d %d %c\n", &tab.width, &tab.height, &tab.c) != 3)
		return (1);
	if (tab.width <= 0 || tab.width >= 300)
		return (1);
	if (tab.height <= 0 || tab.height >= 300)
		return (1);
	if (!tab.c)
		return (1);
	cadre = malloc(sizeof(char *) * (tab.height + 1));
	if (!cadre)
		return (1);
	cadre[tab.height] = 0;
	while (i < tab.height)
	{
		cadre[i] = malloc(sizeof(char) * (tab.width + 1));
		if (!cadre[i])
			return (1);
		while (j < tab.width)
		{
			cadre[i][j] = tab.c;
			j++;
		}
		cadre[i][j] = '\0';
		i++;
		j = 0;
	}
	i = 0;
	j = 0;
	scan = fscanf(fd, "%c %f %f %f %c\n", &circle.fill, &circle.x, &circle.y, &circle.radius, &circle.c);
	if (!circle.c || circle.radius <= 0)
		return (1);
	if (circle.fill != 'c' && circle.fill != 'C')
		return (1);
	while (scan == 5)
	{
		while (cadre[i])
		{
			while (cadre[i][j])
			{
				distance = sqrtf((j - circle.x) * (j - circle.x) + (i - circle.y) * (i - circle.y));
				if (circle.fill =='c')
				{
					if (distance <= circle.radius)
					{
						if (circle.radius - distance <= 1.00000000)
							cadre[i][j] = circle.c;
					}
				}
				else
				{
					if (distance <= circle.radius)
						cadre[i][j] = circle.c;
				}
				j++;
			}
			i++;
			j = 0;
		}
		i = 0;
		j = 0;
		scan = fscanf(fd, "%c %f %f %f %c\n", &circle.fill, &circle.x, &circle.y, &circle.radius, &circle.c);
		if (!circle.c || circle.radius <= 0)
			return (1);
		if (circle.fill != 'c' && circle.fill != 'C')
			return (1);
	}
	i = 0;
	j = 0;
	while (cadre[i])
	{
		while (cadre[i][j])
		{
			write(1, &cadre[i][j], 1);
			j++;
		}
		write(1, "\n", 1);
		i++;
		j = 0;
	}
	i = 0;
	while (cadre[i])
	{
		free(cadre[i]);
		i++;
	}
	free(cadre);
	return (0);
}