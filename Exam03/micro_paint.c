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

typedef struct s_square
{
	char fill;
	float x;
	float y;
	float width;
	float height;
	float a;
	float b;
	char c;
}	t_square;

int main(int argc, char **argv)
{
	FILE *fd;
	t_tab tab;
	t_square square;
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
	scan = fscanf(fd, "%c %f %f %f %f %c\n", &square.fill, &square.x, &square.y, &square.width, &square.height, &square.c);
	while (scan == 6)
	{
		square.a = square.x + square.width;
		square.b = square.y + square.height;
		while (cadre[i])
		{
			while (cadre[i][j])
			{
				if (square.fill == 'r')
				{
					if ((square.x <= j && j <= square.a) && (square.y <= i && i <= square.b))
					{
						if ((j - square.x < 1.00000000 || square.a - j < 1.00000000) || (i - square.y < 1.00000000 || square.b - i < 1.0000000))
							cadre[i][j] = square.c;
					}
				}
				else
				{
					if ((square.x <= j && j <= square.a) && (square.y <= i && i <= square.b))
					{
						cadre[i][j] = square.c;
					}
				}
				j++;
			}
			i++;
			j = 0;
		}
		i = 0;
		j = 0;
		scan = fscanf(fd, "%c %f %f %f %f %c\n", &square.fill, &square.x, &square.y, &square.width, &square.height, &square.c);
	}
	i = 0;
	while (cadre[i])
	{
		printf("%s\n", cadre[i]);
		i++;
	}
	return (0);
}