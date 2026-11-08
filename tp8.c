
#include <stdio.h>
#include <stdlib.h>
#define TAM 20

int cuantas_piezas(int);
int rectificable(float, float);
int rechazada(float, float);
void cargar_piezas(float *, int);
int contar(int (*)(float, float), float, float *, int);
float* reserva_memoria(int);
void segregar(int (*)(float, float), float, float *, int, float *);
void mostrar_piezas(char *, float *, int);

/////////////////////////////////////////////////////////
int main (void) {
    float diametros[TAM];
    int n;
    float max = 12;
    float min = 10;
    
    n = cuantas_piezas(TAM);

cargar_piezas(diametros, n);

    int n_rectificar = contar(rectificable, max, diametros, n);

   float *p_rectificables = reserva_memoria(n_rectificar);

   segregar(rectificable, max, diametros, n, p_rectificables);

int n_rechazar = contar(rechazada, min, diametros, n);

float *p_rechazadas = reserva_memoria(n_rechazar);

  segregar(rechazada, min, diametros, n, p_rechazadas);

   mostrar_piezas("rectificables", p_rectificables, n_rectificar);

mostrar_piezas("rechazadas", p_rechazadas, n_rechazar);
   free (p_rectificables);
   free (p_rechazadas);
    return 0;
}
// FUNCIONES 
int cuantas_piezas(int cant_max) {
    int cant;
    do {
        printf("Cuántas piezas ingresará? ");
        scanf("%d", &cant);
        if (cant <= 0 || cant > cant_max) {
            printf("Error: entre 1 y %d\n", cant_max);
        }
          } while (cant <=0 || cant> cant_max);
    return cant;
}

void cargar_piezas(float *diam, int n) {
    for ( int i = 0 ; i < n ;i++ ) {
        do{
            printf("Ingrese diámetro de pieza %d: ", i);
        scanf("%f", diam+i);
        
        if (*(diam +i) <=  0) printf("Error: debe ser positivo\n");
        } while (*(diam+ i) <= 0) ;
        }
    }




int rectificable(float diametro, float max) {
    return diametro > max ; // este return da 0 o 1 directamente
}


int rechazada(float diametro, float min) {
    return diametro < min; // este return da 0 o 1 directamente
}




int contar(int (*criterio)(float, float), float valor, float *p, int n) {
    int contador = 0;
    for (int i = 0; i < n; i++) {
        if (criterio(*( p+i),valor )) {
            contador++;
     }
     }
    return contador;
}

float* reserva_memoria(int n) {
    float *p =malloc(n * sizeof(float));
    
    if (p == NULL) {
        printf("Error: No se pudo reservar memoria.\n");
        exit(1);
    }
    
    return p;
}

void segregar(int (*criterio)(float, float), float valor, float *p, int n, float *q) {
    int u = 0; 
    for (int i = 0; i < n; i++) {
        if (criterio(*(p + i), valor)) {
            *(q +u)= *(p+ i);
        u++;
        }
    }
}

void mostrar_piezas(char *mensaje, float *p, int n) {
    printf("Piezas %s:\n", mensaje);
    for (int i = 0; i < n; i++) {
        printf("Diámetro: %.2f\n", *(p + i));
    }
}
