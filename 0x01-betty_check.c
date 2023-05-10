#include <stdio.h>

/**
 * main - program entry point
 *
 * Return: 0 on success
 *
 */
int main(void)
{
	int sprint = 3;
	int alxswe_grad = 3;
	int i;

	printf("Alx graduation: %d\n", alxswe_grad);

	for (i = 0; i <= 3; i++)
	{
		sprint += alxswe_grad;
		printf("level reached: %d trimester: %d\n", i, sprint);
	}

	return (0);

}
