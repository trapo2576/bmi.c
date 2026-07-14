#include <stdio.h>

int main()
{
	float peso,altura,imc;
	
	do {
		printf("ingrese su peso en Kg : ");
	    scanf(" %f", &peso);
		if(peso < 0){
			printf("error: el numero debe ser positivo\n");
		}
	}
	while(peso < 0);
	
	do {
		printf("\ningrese su altura en metros: ");
	    scanf(" %f", &altura);
		if(altura < 0){
			printf("error: el numero debe ser positivo\n");
		}
	
	} while(altura < 0 );
	
	imc = peso /(altura*altura);
	printf("\nSu Indice de Masa Corporal es : %.2f\n", imc);
	printf("      REFERENCIAS: \n ");
	printf("Menor a 18.5........BAJO PESO \n ");
	printf("ENTRE 18.5 Y 24.9......NORMAL \n ");
	printf("ENTRE 25.0 Y 29.9...SOBREPESO \n ");
	printf("MAYOR DE 30..........OBESIDAD \n ");
	
	if(imc < 18.5) 
	{
		printf("Su IMC indica BAJO PESO\n");
	}
	else if(imc <= 24.9)
	{
		printf("Su IMC es NORMAL\n");
	}
	else if(imc <= 29.9)
	{
		printf("Su IMC indica SOBREPESO\n");
	}
	else {
		printf("Su IMC indica OBESIDAD\n");
	}
	return 0;
}
