#include <stdio.h>

int main(void)
{
	int estado = 0;

	if (estado == 0) {
		puts("estado 0");
		estado = 1;
	} else if (estado == 1) {
		puts("estado 1");
		estado = 2;
	} else if (estado == 2) {
		puts("estado 2");
	}

	return 0;
}
