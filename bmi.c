#include <stdio.h>

int main()
{
   float peso,altura,imc;
   
    printf("ingrese su peso en Kg : ");
    scanf(" %f", &peso);
    printf("ingrese su altura en metros: ");
    scanf(" %f", &altura);
    imc = peso /(altura*altura);
    printf("Su Indice de Masa Corporal es : %.2f\n", imc);
    printf("      REFERENCIAS: \n ");
    printf("Menor a 18.5........BAJO PESO \n ");
    printf("ENTRE 18.5 Y 24.9......NORMAL \n ");
    printf("ENTRE 25.0 Y 29.9...SOBREPESO \n ");
    printf("MAYOR DE 30..........OBESIDAD \n ");
    return 0;
}
