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
    int dim;
    char opcion;
    data_t avui;
    bool ampliado;
    record_t record,fitxer_record[DIM_MAX];


    /* Inicialitzacions generals */
    srand((int)time(NULL));

    system(NETEJA_PANTALLA);
    avui = P_data_avui();
    printf("%d - %d - %d\n", avui.dia, avui.mes, avui.any);

   /* Codi de l'algorisme */

    dim=0;

    ampliado=false;

    /* Codi de l'algorisme */
    printf("\nEstas en el juego de los barcos, teclea la letra de cada opcion para moverte por el menu.");
    ampliado=false;
    while(opcion!=102){

        if(!ampliado){
            printf("\n\nEstas en el menu reducido");
            printf("\n a.  Inicia una partida nova");
            printf("\n b.  Carregar una partida");
            printf("\n e.  Veure podium");
            printf("\n f.  Sortir del joc\n");

        }
        else if(ampliado){
            printf("\n\nEstas en el menu ampliado");
            printf("\n a.  Inicia una partida nova");
            printf("\n b.  Carregar una partida");
            printf("\n c.  Jugar partida");
            printf("\n d.  Emmagatzemar la partida");
            printf("\n e.  Veure podium");
            printf("\n f.  Sortir del joc\n");

        }

        printf("\nIntroduce la opcion deseada: ");
        fflush(stdin);
        scanf("%c", &opcion);

        switch(opcion){
            case 'a':
                printf("\nHas elegido la opcion: Iniciar una partida nova\n\n");
                dim = P_iniciar_partida(tablero_barcos, tablero_disparos);
                printf("\n\n\n%d",dim);
                ampliado = true;

                break;
            case 'b':
                printf("\nHas elegido la opcion: Carregar una partida");
                ampliado = true;
                break;
            case 'c':
                if(ampliado){
                    printf("\nHas elegido la opcion: Jugar partida\n\n");
                    P_jugar(tablero_barcos, tablero_disparos, dim);
                }

                else {
                    printf("\nOpcion no valida, trii otra opcion");
                }
                break;
            case 'd':
                if(ampliado){
                    printf("\nHas elegido la opcion: Emmagatzemar la partida");
                    P_guarda_record (fitxer_record, record);
                }
                else {
                    printf("\nOpcion no valida, trii otra opcion");
                }
                break;
            case 'e':
                printf("\nHas elegido la opcion: Veure podium");
                break;
            case 'f':
                printf("\nHas elegido la opcion: Sortir del joc.  Adeu i fins aviat! ");
                break;
            default:
                printf("\nOpcion no valida, trii otra opcion");
                break;

        }
        }



    return 0;
}
