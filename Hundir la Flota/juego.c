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


#define DIM_RECORDS         1000 /*es la dimension de la tabla que guarda matrices*/
/* Programa principal */
int main ()
{
    /* Declaracio de les variables del programa */
    char tablero_barcos[DIM_MAX][DIM_MAX];
    char tablero_disparos[DIM_MAX][DIM_MAX];
    int dim, modo, salir_podium;
    char opcion;
    data_t avui;
    record_t records[DIM_RECORDS];
    bool ampliado;



    /* Inicialitzacions generals */
    srand((int)time(NULL));

    system(NETEJA_PANTALLA);

    avui = P_data_avui();
    printf("%d - %d - %d\n", avui.dia, avui.mes, avui.any);

   /* Codi de l'algorisme */

    system("color B0");

    dim=0;

    ampliado=false;



/*   /$$   /$$ /$$   /$$ /$$   /$$ /$$$$$$$  /$$$$$$ /$$$$$$$        /$$        /$$$$$$        /$$$$$$$$ /$$        /$$$$$$  /$$$$$$$$ /$$$$$$
    | $$  | $$| $$  | $$| $$$ | $$| $$__  $$|_  $$_/| $$__  $$      | $$       /$$__  $$      | $$_____/| $$       /$$__  $$|__  $$__//$$__  $$
    | $$  | $$| $$  | $$| $$$$| $$| $$  \ $$  | $$  | $$  \ $$      | $$      | $$  \ $$      | $$      | $$      | $$  \ $$   | $$  | $$  \ $$
    | $$$$$$$$| $$  | $$| $$ $$ $$| $$  | $$  | $$  | $$$$$$$/      | $$      | $$$$$$$$      | $$$$$   | $$      | $$  | $$   | $$  | $$$$$$$$
    | $$__  $$| $$  | $$| $$  $$$$| $$  | $$  | $$  | $$__  $$      | $$      | $$__  $$      | $$__/   | $$      | $$  | $$   | $$  | $$__  $$
    | $$  | $$| $$  | $$| $$\  $$$| $$  | $$  | $$  | $$  \ $$      | $$      | $$  | $$      | $$      | $$      | $$  | $$   | $$  | $$  | $$
    | $$  | $$|  $$$$$$/| $$ \  $$| $$$$$$$/ /$$$$$$| $$  | $$      | $$$$$$$$| $$  | $$      | $$      | $$$$$$$$|  $$$$$$/   | $$  | $$  | $$
    |__/  |__/ \______/ |__/  \__/|_______/ |______/|__/  |__/      |________/|__/  |__/      |__/      |________/ \______/    |__/  |__/  |__/

*/

    /* Codi de l'algorisme */
    printf("\n\n\n     *           *   *                                                                                ");
    printf("\n       **           *   *                                                     *               *  *        ");
    printf("\n         **              **                                               *               *  *   *        ");
    printf("\n           **             **                                            *   *              *  *           ");
    printf("\n            ***            ***                                        *  * *              * *     ");
    printf("\n            # #            # #                                       # #              # #         ");
    printf("\n            # #            # #                                       # #              # #         ");
    printf("\n            # #            # #                                       # #              # #         ");
    printf("\n            # #            # #                                       # #              # #         ");
    printf("\n    #####   # #            # #                                       # #              # # #####   ");
    printf("\n    #####______________________________                     ______________________________#####   ");
    printf("\n    ###################################                     ###################################   ");
    printf("\n     #####0##0##0##0##0##0##0#######                           #######0##0##0##0##0##0##0#####    ");
    printf("\n      ############################                               ############################     ");
    printf("\n      ##########################                                  ###########################     ");
    printf("\n_________________________________________________________________________________________________________________\n");
    printf("\n\nEstas en el juego de los barcos, teclea la letra de cada opcion para moverte por el menu.");



    ampliado=false;
    while(opcion!='f'){


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

        system(NETEJA_PANTALLA);

        switch(opcion){
            case 'a':
                printf("\nHas elegido la opcion: Iniciar una partida nova\n\n");
                dim = P_iniciar_partida(tablero_barcos, tablero_disparos, &modo);
                ampliado = true;

                break;
            case 'b':
                printf("\nHas elegido la opcion: Carregar una partida");
                printf("\n\nLa opcion seleccionada no esta disponible");
                break;
            case 'c':
                if(ampliado){
                    printf("\nHas elegido la opcion: Jugar partida\n\n");
                    if(modo==0){
                        P_jugar0(tablero_barcos, tablero_disparos, dim);
                    }
                    else if(modo==1){
                        P_jugar1(tablero_barcos, tablero_disparos, dim);
                    }
                }

                else {
                    printf("\nOpcion no valida, trii otra opcion");
                }
                break;
            case 'd':
                if(ampliado){
                    printf("\nHas elegido la opcion: Emmagatzemar la partida");
                    printf("\n\nLa opcion seleccionada no esta disponible");

                }
                else {
                    printf("\nOpcion no valida, trii otra opcion");
                }
                break;
            case 'e':
                printf("\nHas elegido la opcion: Veure podium");
                P_muestra_records(records, DIM_RECORDS);
                printf("\n\nintroduce 1 para volver al menu ");
                scanf("%d", &salir_podium);
                break;
            case 'f':
                printf("\n\n\n                                             Has elegido la opcion: Sortir del joc.");
                printf("\n\n\n                                                     ADEU I FINS AVIAT!\n\n\n\n\n\n\n\n");
                    printf("\n\n\n     *           *   *                                                                                ");
                printf("\n       **           *   *                                                     *               *  *        ");
                printf("\n         **              **                                               *               *  *   *        ");
                printf("\n           **             **                                            *   *              *  *           ");
                printf("\n            ***            ***                                        *  * *              * *     ");
                printf("\n            # #            # #                                       # #              # #         ");
                printf("\n            # #            # #                                       # #              # #         ");
                printf("\n            # #            # #                                       # #              # #         ");
                printf("\n            # #            # #                                       # #              # #         ");
                printf("\n    #####   # #            # #                                       # #              # # #####   ");
                printf("\n    #####______________________________                     ______________________________#####   ");
                printf("\n    ###################################                     ###################################   ");
                printf("\n     #####0##0##0##0##0##0##0#######                           #######0##0##0##0##0##0##0#####    ");
                printf("\n      ############################                               ############################     ");
                printf("\n      ##########################                                  ###########################     ");
                printf("\n_________________________________________________________________________________________________________________\n");
                break;
            default:
                printf("\nOpcion no valida, trii otra opcion");
                break;

        }

        }



    return 0;
}
