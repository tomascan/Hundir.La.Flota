/*----------------------------------------------------------------
 |  Autor1: nom.cognom@estudiants.urv.cat
 |  Autor2: nom.cognom@estudiants.urv.cat
 |  Data: Octubre 2017                 Versio: 3.0
 |-----------------------------------------------------------------|
 |	Nom projecte: ...
 |	Nom: proc.h
 |  Descripcio del Programa:   Implementacio dels procediments.
 | ----------------------------------------------------------------*/
#include "proc.h"

/** Procediments auxiliars */
/*
 accio P_netejar_stdio();

 "Netejar" l'entrada estandard (buidar el buffer de teclat)
*/
void P_netejar_stdio(void)
{
    int ch;
    while (((ch = getchar()) != EOF) && (ch != '\n'));
}

/*
 funcio P_data_avui() retorna data_tipus;

 Retorna la data actual.
 */
data_t P_data_avui(void)
{
    data_t avui;
    struct tm *data;
    time_t tiempo;

    tiempo = time(NULL);
    data = localtime(&tiempo);
    avui.dia = data->tm_mday;
    avui.mes = data->tm_mon+1;
    avui.any = data->tm_year+1900;

    return avui;
}

/*
 accio P_pausa();

 Pausa el programa fins que se pulse return/enter.
 */
void P_pausa(void)
{
    printf("\nPulsa return/enter per a continuar! ");
    P_netejar_stdio();
}

/** PROCEDIMENTS BASICS */
/*
HECHO
 accio P_decide_disparo (var fila:enter, var col:enter, tablero_disparos: taula de caracters, dim:enter);
 Esta accion decide aleatoriamente a que casilla disparar, pero en el caso de que la casilla ya haya sido disparada elige otra casilla
 */
extern void P_decide_disparo (int *f, int *c, char tablero_disparos[][COL_MAX],int dim)
{
    *f = P_aleatorio(1,dim);
    *c = P_aleatorio(1,dim);
    printf("Procediment P_decide_disparo!\n");
}
/*
HECHO
 accio P_procesa_hundido (fila:enter, col:enter, var tablero_disparos: taula de caracters, dim:enter);
 */
extern void P_procesa_hundido (int f, int c, char tablero_disparos[][COL_MAX], int dim)
{
 int f_inicial, c_inicial;

 f=f-1;
 c=c-1;
 f_inicial = f;
 c_inicial = c;


/*Hago un mientras que se mueve hacia abajo y que pone un punto cuando llega al extremo*/
 while((tablero_disparos[f][c]=='@')&&(f<dim)){

    /*para cada fila voy comprobando la comlumna hacia la derecha y voy poniendo puntos*/
    while((tablero_disparos[f][c]=='@')&&(c<dim)){
        c++;
    }
    if(c<dim){
        tablero_disparos[f][c]= '.';
    }

    /*vuelco a la columna del principio para volver a empezar hacia la izquierda*/
    c = c_inicial;

    /*para cada fila voy comprobando la columna hacia la izquierda y voy poniendo puntos*/
    while((tablero_disparos[f][c]=='@')&&(c>=0)){
        c--;;
    }
    if(dim>=0){
        tablero_disparos[f][c]= '.';
    }

    /*vuelvo a la columna del principio*/
    c = c_inicial;

    /*avanzo de fila*/
    f++;
 }

/*coloco el punto del final de la fila*/
 if(f<dim){
    tablero_disparos[f][c]= '.';
    if(c+1<dim){
        tablero_disparos[f][c+1]= '.';
    }
    if(c-1>=0){
        tablero_disparos[f][c-1]= '.';
    }
 }


 f = f_inicial;




/*Hago un mientras que se mueve hacia arriba que pone un punto cuando llega al extremo*/
 while((tablero_disparos[f][c]=='@')&&(f>=0)){

    /*para cada fila voy comprobando la comlumna hacia la derecha y voy poniendo puntos*/
    while((tablero_disparos[f][c]=='@')&&(c<dim)){
        c++;
    }
    if(c<dim){
        tablero_disparos[f][c]= '.';
    }

    c = c_inicial;

    /*para cada fila voy comprobando la columna hacia la izquierda y voy poniendo puntos*/
    while((tablero_disparos[f][c]=='@')&&(c>=0)){
        c--;;
    }
    if(c>=0){
        tablero_disparos[f][c]= '.';
    }

    c = c_inicial;

    f--;
 }

 if(f<dim){
    tablero_disparos[f][c]= '.';
    if(c+1<dim){
        tablero_disparos[f][c+1]= '.';
    }
    if(c!=0){
        tablero_disparos[f][c-1]= '.';
    }
 }

 if(f>=dim){
    f = f_inicial;
 }
}
/*
HECHO
funcio P_aleatorio ( min: enter, max: enter) retorna enter;
Esta funcion crea un numero aleatorio entre el maximo y el minimo que se han introducido y usando la hora como semilla para el srand
 */
extern int P_aleatorio (int min, int max)
{
    int aleatorio;
    /*limito el numero aleatorio a la franja entre el min y el max*/
    aleatorio = rand() % (max-min+1) + min;
    return aleatorio;
}

/*
HECHO
accio P_coordenadas ( fila: caracter, var col: enter, var fila_entero: enter );
*/
extern void P_coordenadas (char fila, int *col, int *fila_entero)
{
    if('a' < fila && fila < 'z'){
        *fila_entero = fila - 'a';
    }
    else if('A' < fila && fila < 'Z'){
        *fila_entero = fila - 'A';
    }

    *col = *col - 1;

}


/*
NO HECHO
Esta funcion guarda el texto entroducido en una tabla de caracteres con una dimension y un centinela pasados
 funcio P_leer_cadena ( var cadena: taula de caracters, dim: enter, centinela: caracter) retorna enter;
 */
extern int P_leer_cadena (char cadena[], int dim, char centinela)
{
    int i;

    for(i=0; i<=dim; i++){
        scanf("%c", cadena[i]);
    }

    cadena[i] = centinela;


    return i-1;
}

/*
HECHO
Esta funcion llena la tabla que se le pasa con el caracter deseado
 accio P_inicializa_matriz ( var matriz: taula de caracters, nfilas: enter, int ncols, car: caracter) es;
 */
extern void P_inicializa_matriz (char matriz[][COL_MAX], int nfilas, int ncols, char car)
{
    int i, j;

    for(i=0; i<=nfilas; i++){
        for(j=0; j<=nfilas; j++){
            matriz[i][j] = car;
        }
    }
}

/*
HECHO
 accio P_muestra_una_matriz ( matriz: taula de caracters, nfilas: enter, ncols: enter) es;
 */
extern void P_muestra_una_matriz (char matriz[][COL_MAX], int nfilas, int ncols)
{
    int i, j;
    char fila;

    /*primero digo el tamaño de tabla*/
    printf("La matriz es %d x %d\n", nfilas, ncols);

    /*ahora escribo las coordenadas de la tabla*/
    for(i=1; i<=ncols; i++){
        printf("    %d", i);
    }

    /*ahora voy escribiendo la coordenada de cada columna y su contenido*/
    i=0;
    for(i=0; i<nfilas; i++){
        fila = 'A'+i;
        printf("\n\n%c", fila);
        for(j=0; j<ncols; j++){
            printf("    %c", matriz[i][j]);
        }
    }
    printf("\n\n\n\n\n");
}

/*
HECHO
 accio P_muestra_dos_matrices ( matriz1: taula de caracters,matriz2: taula de caracters, nfilas: enter, ncols: enter) es;
 */
extern void P_muestra_dos_matrices (char matriz1[][COL_MAX], char matriz2[][COL_MAX], int nfilas, int ncols)
{
    int i, j;
    char fila;

    /*escribo las coordenadas de columnas de la primera tabla*/
    for(i=1; i<=ncols; i++){
        printf("    %d", i);
    }

    /*escribo las coordenadas de comlumnas de la segunda tabla*/
    printf("            ");
    for(i=1; i<=ncols; i++){
        printf("    %d", i);
    }

    for(j=0; j<nfilas; j++){
        fila = 'A'+j;
        printf("\n\n%c", fila);
        for(i=0; i<ncols; i++){
            printf("    %c", matriz1[j][i]);
        }
        printf("            %c", fila);
        for(i=0; i<ncols; i++){
            printf("    %c", matriz2[j][i]);
        }
    }
}

/*
 funcio P_guarda_record (fitxer_record:taula de caracters, record:record_t) retorna boolea;
 */
extern bool P_guarda_record (char fitxer_record[], record_t record)
{
    return 0;
}
/*
 funcio P_recupera_records (fitxer_record:taula de caracters, var records:taula de record_tipus, dim:enter ) retorna enter;
 */
extern int P_recupera_records (char fitxer_record[], record_t records[], int dim)
{
    return 0;
}

/*accio P_muestra_records (records[]: record_T, dim: entero)*/
extern void P_muestra_records (record_t records[], int dim){

    return 0;
}
/** -------------------------------------------------------
 PROCEDIMENTS ADDICIONALS A DESENVOLUPAR
 ------------------------------------------------------- */

/*
funcio P_nuevo_disparo (var f:caracter, var c:enter, dim:enter) retorna boolea;
 */
extern bool P_nova_jugada (char *f, int *c, int dim)
{
    printf("Procediment P_nova_jugada\n");
    return true;
}

/*
 funcio P_guarda_partida (nom_fitxer:taula de caracters, dim:enter, modo_juego:enter, turno:enter, jugadores:taula de jugador_t) retorna boolea;
 */
extern bool P_guarda_partida (char fitxer_record[], int dim, int modo_juego, int turno, jugador_t jugadores[])
{
    printf("Procediment P_guardar_partida\n");
    return true;
}

/*
 funcio P_recupera_partida (nom_fitxer:taula de caracters, var dim:enter, var modo_juego: enter,
 var turno:enter, var jugadores:taula de jugador_t) retorna boolea;
 */
extern bool P_recupera_partida (char fitxer_record[], int *dim, int *modo_juego, int *turno, jugador_t jugadores[])

{
    printf("Procediment P_recupera_partida\n");
    return true;
}

/*
 funcio P_coloca_barcos (var tablero_barcos:taula de caracters, dim: enter) retorna boolea;
 */
extern bool P_coloca_barcos (char tablero_barcos[][DIM_MAX], int dim)
{
    printf("Procediment P_coloca_barcos\n");
    return  true;
}


/** -------------------------------------------------------
 PROCEDIMIENTOS AÑADIDOS POR NOSOTROS
 ------------------------------------------------------- */


/*
Esta funcion actualiza la tabla de disparos dependiendo del resultado que nos de B_dispara
accio P_actualiza_disparos(f : entero, c : entero, tabla_disparos : tabla[][] de caracter, resultado : entero, dim : entero)
*/
extern void P_actualiza_disparos(int f, int c, char tablero_disparos[][COL_MAX], int resultado, int dim){

    int fil, col;

    fil=f-1;
    col=c-1;

    switch (resultado){
        case -1: printf("\nError, coordenadas fuera de rango\n\n\n\n");
                 break;
        case 0: printf("\nCasilla repetida\n\n");
                break;
        case 1: tablero_disparos[f-1][c-1]='.';
                printf("\nAgua\n\n");
                break;
        case 2: tablero_disparos[f-1][c-1]='@';
                printf("\nTocado!\n\n");
                break;
        case 3: tablero_disparos[f-1][c-1]='@';
                printf("\nTocado y hundido!\n\n");
                P_procesa_hundido(f,c,tablero_disparos,dim);
                break;
        default: printf("\nError\n\n");
                break;
    }
}

/*
Esta funcion pasa las coordenadas de filas de entero a caracter poque en P_decide_disparo tratamos las filas como entero pero en B_dispara lo trata como caracter
accio P_a_letras ( fila: caracter) retorna caracter;
*/
extern char P_a_letras (int f){
    char fila;

    fila=f +'A'-1;

    return fila;
}



