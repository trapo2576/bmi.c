/******************************************************************************
*******************************************************************************/
#include <stdio.h>

#define TAM 5 // Constante simbólica para la cantidad de productos

int main() {
    long codigos[TAM];
    float precios[TAM];
     int pos_max = 0;
    int pos_min = 0;

printf("Ingrese %d productos, se solicitará el código y precio:\n", TAM);

// carga de datos
   for(int i = 0 ; i < TAM ; i ++){
    
    do{
    printf("Ingrese el código de barras (1-999999999):  \n");
     scanf("%ld",&codigos[i]);
        // validacion
        if(codigos[i] < 1 || codigos[i] > 999999999){
             printf("Error. El código de barras debe estar entre 1 y 999999999\n");
        }
    }
  
        while(codigos[i] < 1 || codigos[i] > 999999999);
  
  do {
      printf("Ingrese el precio:\n");
      scanf("%f",&precios[i]);
      // validacion
       if(precios[i] < 0 ){
           printf("Error. El precio no puedo ser negativo\n");
       }
  }
      while(precios[i] < 0);
   }  
 // muestra de productos 
printf("\n  Codigo:     Precio:\n");
 for(int i = 0 ; i < TAM ; i ++){
 printf("%9ld\t %.2f\n",codigos[i], precios[i]);
 }
 
 // comparacion mas caro y mas barato
 for(int i = 0 ; i < TAM ; i ++){
     if( precios[i] > precios[pos_max]){
         pos_max = i;
     }
     if( precios[i] < precios[pos_min]){
         pos_min = i;
     }
 }
    // imprimo mas caro y mas barato
      printf("\nMas caro:   [%9ld]\t %.2f\n",codigos[pos_max], precios[pos_max]);
      printf("Mas barato: [%9ld]\t %.2f",codigos[pos_min], precios[pos_min]);    
 
 
 return 0;

}
