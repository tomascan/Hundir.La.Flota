/*----------------------------------------------------------------
 |  Autor1: nom.cognom@estudiants.urv.cat
 |  Autor2: nom.cognom@estudiants.urv.cat
 |  Data: Octubre 2017                 Versio: 2.0
 |-----------------------------------------------------------------|
 |	Nom projecte: .....
 |	Nom: juego.c
 |  Descripcio del Programa:   Programa principal.
 | ----------------------------------------------------------------*/

/* Incloure llibreries */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "libBarcos2017.h"
#include "tipus.h"
#include "proc.h"

/* Programa principal */
int main ()
{
    /* Declaracio de les variables del programa */
    char tablero_barcos[DIM_MAX][DIM_MAX];
    char tablero_disparos[DIM_MAX][DIM_MAX];
    int col, hundidos, f, c, i, resultado;
    char fila;
    unsigned int dim, dim2;
    data_t avui;


    /* Inicialitzacions generals */
    srand((int)time(NULL));

    system(NETEJA_PANTALLA);
    avui = P_data_avui();
    printf("%d - %d - %d\n", avui.dia, avui.mes, avui.any);

   /* Codi de l'algorisme */

    hundidos=0;
    f=0;
    col=0;
    i=0;


    printf("Introduce el la dimension deseada para las tablas(8, 9 o 10): ");
    scanf("%d", &dim);
    while((dim!=8) & (dim!=9) & (dim!=10)){
        printf("Introduce una dimension valida para las tablas(8, 9 o 10): ");
        scanf("%d", &dim);
    }

    /*escribo las dimensiones de las tablas*/
    printf("\n\nLas matrices son %d x %d\n\n", dim, dim);

    /*inicializo las dos matrices */
    P_inicializa_matriz(tablero_disparos,dim,dim,'?');
    B_inicializa_barcos(tablero_barcos,dim);


    P_muestra_dos_matrices(tablero_barcos,tablero_disparos,dim,dim);



    while (hundidos<=9){
            /*primero decido las coordenadas del disparo*/
            P_decide_disparo(&f, &col,tablero_disparos,dim);

            /*paso las filas a letras mayusculas porque en P_decide_disparo se nos pide que lo hagamos con f (que es int) y en
            B_dispara hay que usar fila(que es char)*/
            fila=P_a_letras(f);
            printf("\n\n\n\nLas coordenadas del disparo son: %c %d\n",fila,col);


            /*guardo la dimension en otra variable para pasar a B_dispara porque la funcion B_dispara me combierte la dimension que le paso a 0*/
            dim2=dim;

            /*compruebo el resultado del disparo*/
            resultado=B_dispara(fila,col,tablero_barcos,&dim2);

            /*con P_actualiza_disparos digo el resultado del disparo y cambio la tabla de disparos utilizando P_procesa hundido*/
            P_actualiza_disparos(f,col,tablero_disparos,resultado,dim);

            /*vuelvo a mostrar las dos matrices*/
            P_muestra_dos_matrices(tablero_barcos,tablero_disparos,dim,dim);

            if(resultado==3){

                hundidos++;
            }

            /*Pongo un contador para saber cuantos turnos llevo*/
            i++;
            printf("\n\n\nLleva %d turnos y %d barcos hundidos.", i, hundidos);

            //P_pausa();
    }

    printf("\n\n\nSe acabo la partida.");



system ("pause");


    return 0;
}
