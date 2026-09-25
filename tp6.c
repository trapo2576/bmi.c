#include <stdio.h>
#define PI 3.141592

double calcularAreaRectangulo(double longitud, double altura){
    return longitud * altura;
}

double calcularPerimetroRectangulo(double longitud, double altura){
    return 2 * (longitud + altura);
}

double calcularAreaCirculo(double radio){
    return  PI * (radio * radio);
}

double calcularPerimetroCirculo(double radio){
    return  2 * PI * radio;
}

void imprimirResultados(double area, double perimetro, int figura){
    if(figura == 1){
        printf("El área del rectángulo es: %.2f cm cuadrados\n", area);
        printf("El perímetro del rectángulo es: %.2f cm\n", perimetro);
    }
    
    else{
        printf("El área del círculo es: %.2f cm cuadrados\n", area);
        printf("El perímetro del círculo es: %.2f cm\n", perimetro);
    }
}

int main()
{
    int opcion;
    double radio, longitud, altura;
    
	do{
	    printf("Ingrese la figura que desea calcular (1: rectángulo, 2: círculo): \n");
	    scanf("%d", &opcion);
	    if(opcion == 1) {
	        printf("Opción de rectángulo seleccionada\n");
	        printf("Ingrese la longitud del rectángulo:\n");
	        scanf("%lf", &longitud);
	        printf("Ingrese la altura del rectángulo:\n");
	        scanf("%lf", &altura);
	        imprimirResultados(calcularAreaRectangulo(longitud,altura),calcularPerimetroRectangulo(longitud,altura),opcion);
	        
	    }
	    if(opcion == 2) {
	        printf("Opción de circulo seleccionada\n");
	        printf("Ingrese el radio del circulo:\n");
	        scanf("%lf", &radio);
	        
	        imprimirResultados(calcularAreaCirculo(radio),calcularPerimetroCirculo(radio),opcion);
	  
	    }
	    if(opcion != 1 && opcion != 2)printf("Opción NO VALIDA!!\n");
	} 
	while(opcion != 1 && opcion != 2);

	return 0;
}
