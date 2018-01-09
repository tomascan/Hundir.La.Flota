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

/** Procediments                 P_procesa_hundido(f,c,tablero_disparos,dim);auxiliars */
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
    printf("\n\nPulsa return/enter per a continuar! ");
    P_netejar_stdio();
}

/** PROCEDIMENTS BASICS */
/*
HECHO
 accio P_decide_disparo (var fila:enter, var col:enter, tablero_disparos: taula de caracters, dim:enter);

 Esta accion decide aleatoriamente a que casilla disparar, pero en el caso de que la casilla ya haya sido disparada elige otra casilla
 */
extern void P_decide_disparo (int *f, int *c, char tablero_disparos[][COL_MAX], int dim)
{
    *f = P_aleatorio(1,dim);
    *c = P_aleatorio(1,dim);

    if(tablero_disparos[*f-1][*c-1]!='?'){
        while(tablero_disparos[*f-1][*c-1]!='?'){
            *f = P_aleatorio(1,dim);
            *c = P_aleatorio(1,dim);
        }
    }
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
 while((tablero_disparos[f][c]=='@')&&(f<dim) && (f>=0) &&(c>=0)){

    /*para cada fila voy comprobando la comlumna hacia la derecha y voy poniendo puntos*/
    while((tablero_disparos[f][c]=='@')&&(c<dim) && (f>=0) &&(c>=0)){
        c++;
    }
    if(c<dim){
        tablero_disparos[f][c]= '.';
    }

    /*vuelco a la columna del principio para volver a empezar hacia la izquierda*/
    c = c_inicial;

    /*para cada fila voy comprobando la columna hacia la izquierda y voy poniendo puntos*/
    while((tablero_disparos[f][c]=='@')&&(c>=0) && (f>=0)){
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
 if((f<dim) && (f>=0) &&(c>=0)){
    tablero_disparos[f][c]= '.';
    if((c+1<dim) && (f>=0) &&(c>=0)){
        tablero_disparos[f][c+1]= '.';
    }
    if(c-1>=0){
        tablero_disparos[f][c-1]= '.';
    }
 }


 f = f_inicial;




/*Hago un mientras que se mueve hacia arriba que pone un punto cuando llega al extremo*/
 while((tablero_disparos[f][c]=='@')&&(f>=0) &&(c>=0)){

    /*para cada fila voy comprobando la comlumna hacia la derecha y voy poniendo puntos*/
    while((tablero_disparos[f][c]=='@')&&(c<dim) && (f>=0) &&(c>=0)){
        c++;
    }
    if((c<dim) && (f>=0) &&(c>=0)){
        tablero_disparos[f][c]= '.';
    }

    c = c_inicial;

    /*para cada fila voy comprobando la columna hacia la izquierda y voy poniendo puntos*/
    while((tablero_disparos[f][c]=='@')&&(c>=0) &&(f>=0)){
        c--;;
    }
    if((c>=0) && (f>=0)){
        tablero_disparos[f][c]= '.';
    }

    c = c_inicial;

    f--;
 }

 if((f<dim) && (f>=0) &&(c>=0)){
    tablero_disparos[f][c]= '.';
    if(c+1<dim){
        tablero_disparos[f][c+1]= '.';
    }
    if((c!=0) && (f>=0) &&(c>=0)){
        tablero_disparos[f][c-1]= '.';
    }
 }

 if((f>=dim) && (f>=0) &&(c>=0)){
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
    FILE *fitRecord;
    data_t fecha;
    bool guardat;

    fecha = record.data;
    fitRecord = fopen(fitxer_record, "a");
    guardat = true;

    if (fitRecord == NULL){
        guardat = false;
    } else {
        fprintf(fitRecord, "%d-%d-%d\t%s\t%d\n", fecha.dia, fecha.mes, fecha.any, record.nom, record.punts);

        fclose(fitRecord);
    }

    return guardat;

    return true;
}

/*
 funcio P_recupera_records (fitxer_record:taula de caracters, var records:taula de record_tipus, dim:enter ) retorna enter;
 */
extern int P_recupera_records (char fitxer_record[], record_t records[], int dim)
{

    /*
        0. Llegir els primers rècords, fins a omplir la taula.
        1. Llegir els rècords amb la millor puntuació.
        2. Llegir els rècords més recents.
     */

    FILE *fitRecord;
    data_t fecha;
    record_t record;
    char carControl;
    int i;

    i = 0;

    fitRecord = fopen(fitxer_record, "r");

    if (fitRecord == NULL){
        // printf("Error! Fitxer no existeix!");
        i = -1;
    } else {
        fscanf(fitRecord, "%d", &fecha.dia);

        if (feof(fitRecord)){
            printf("Seq. buida");
        } else {
            while(!feof(fitRecord) && i < dim){
                fscanf(fitRecord, "%c", &carControl);
                fscanf(fitRecord, "%d", &fecha.mes);
                fscanf(fitRecord, "%c", &carControl);
                fscanf(fitRecord, "%d", &fecha.any);
                fscanf(fitRecord, "%s", record.nom);
                fscanf(fitRecord, "%d", &record.punts);

                record.data = fecha;

                records[i] = record; // asignem el record a la taula
                i++;

                fscanf(fitRecord, "%d", &fecha.dia);
            }
        }

        fclose(fitRecord);
    }

    return i;;
}

/*accio P_muestra_records (records[]: record_T, dim: entero)*/
extern void P_muestra_records (record_t records[], int dim){

    record_t record;
    data_t fecha;

    int i;
    i = 0;

    while (i < dim) {
        record = records[i];
        fecha = records->data;
        ++i;
        printf("%d.\t%d-%d-%d\t%s\t%d\n", i+1, fecha.dia, fecha.mes, fecha.any, record.nom, record.punts);
    }
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


extern void P_jugar(char tablero_barcos[][COL_MAX], char tablero_disparos[][COL_MAX], int dim){

    int col, hundidos, f, c, i, resultado, mida;
    char fila;
    data_t avui;


    /*escribo las dimensiones de las tablas*/
    printf("\n\nLas matrices son %d x %d\n\n", dim, dim);


    P_muestra_dos_matrices(tablero_barcos,tablero_disparos,dim,dim);

    i = 0;
    hundidos = 0;
    while (hundidos<=9){
            /*primero decido las coordenadas del disparo*/
            P_decide_disparo(&f, &col,tablero_disparos,dim);

            /*paso las filas a letras mayusculas porque en P_decide_disparo se nos pide que lo hagamos con f (que es int) y en
            B_dispara hay que usar fila(que es char)*/
            fila = P_a_letras(f);
            printf("\n\n\n\nLas coordenadas del disparo son: %c %d\n",fila,col);


            /*compruebo el resultado del disparo*/
            resultado = B_dispara(fila,col,tablero_barcos,&mida);

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

}

extern int P_iniciar_partida(char tablero_barcos[][COL_MAX], char tablero_disparos[][COL_MAX]){

    int dim;
    printf("Introduce el la dimension deseada para las tablas(8, 9 o 10): ");
    scanf("%d", &dim);
    while((dim!= 8) && (dim!=9) && (dim!=10)){
        printf("Introduce una dimension valida para las tablas(8, 9 o 10): ");
        scanf("%d", &dim);
    }


    /*inicializo las dos matrices */
    P_inicializa_matriz(tablero_disparos,dim,dim,'?');
    B_inicializa_barcos(tablero_barcos,dim);

    return dim;

}


