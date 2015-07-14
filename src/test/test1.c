#include <stdio.h>
#include <stdlib.h>

char *f(char *nombre_archivo)
{
	nombre_archivo = "hola";
	return nombre_archivo;
}

int main(void)
{
	char *nombre_archivo;
	nombre_archivo = f(nombre_archivo);
	puts(nombre_archivo);
	return 0;
}
