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
void P_decide_disparo (int *f, int *c, char tablero_disparos[][COL_MAX], int dim, bool tocado, int primero_tocado_c, int primero_tocado_f, int *orientacion)
{

    /*esto es para que en el caso de que el anterior fuera un tocado dispare cerca hasta hundirlo*/

   /*esto es para que cuando ha tocado un barco lo hunda sin seguir aleatoriamente*/
    if(tocado){

        *orientacion=0;

        /*esto comprueba si el barco esta en posicion vertical o horizontal(1=vertical, 2=horizontal, 0=no hay barco tocado)*/
        if(tablero_disparos[primero_tocado_f][primero_tocado_c-1]=='@'){
            *orientacion = 1;
        }
        else if(tablero_disparos[primero_tocado_f-2][primero_tocado_c-1]=='@'){
            *orientacion = 1;
        }
        else if(tablero_disparos[primero_tocado_f-1][primero_tocado_c]=='@'){
            *orientacion = 2;
        }
        else if(tablero_disparos[primero_tocado_f-1][primero_tocado_c-2]=='@'){
            *orientacion = 2;
        }


        /*estos primeros if son para cuando ha tocado un nuevo barco y tiene que comprobar si esta en posicion vertical o horizontal(1=vertical, 2=horizontal, 0=no hay barco tocado)*/
        if(*orientacion==0){
            if((tablero_disparos[primero_tocado_f][primero_tocado_c-1]=='?')&&(primero_tocado_f+1<=dim)){
                *f = primero_tocado_f+1;
            }
            else if((tablero_disparos[primero_tocado_f-2][primero_tocado_c-1]=='?')&&(primero_tocado_f-1>=0)){
                *f = primero_tocado_f-1;
            }
            else if((tablero_disparos[primero_tocado_f-1][primero_tocado_c]=='?')&&(primero_tocado_c+1<=dim)){
                *f = primero_tocado_f;
                *c = primero_tocado_c+1;
            }
            else if((tablero_disparos[primero_tocado_f-1][primero_tocado_c-2]=='?')&&(primero_tocado_c-1>=0)){
                *f = primero_tocado_f;
                *c = primero_tocado_c-1;
            }
        }

        /*ahora es para cuando el anterior era tocado y esta en posicion vertical*/
        /*primero hacia abajo*/
        if((tocado)&&(*orientacion==1)){
            /*primero me desplazo hacia abajo*/
            while(tablero_disparos[primero_tocado_f-1][primero_tocado_c-1]=='@'){
                primero_tocado_f++;
            }
            /*voy disparando hacia abajo hasta llegar al final de barco*/
            if((tablero_disparos[primero_tocado_f-1][primero_tocado_c-1]=='?')&&(primero_tocado_f<=dim)){
                *f = primero_tocado_f;
            }
            /*ahora hacia arriba*/
            else{
                primero_tocado_f--;
                while(tablero_disparos[primero_tocado_f-1][primero_tocado_c-1]=='@'){
                    primero_tocado_f--;
                }
                if ((tablero_disparos[primero_tocado_f-1][primero_tocado_c-1]=='?')&&(primero_tocado_f>=0)){
                    *f = primero_tocado_f;
                }
            }
        }

        /*ahora para el horizontal*/
        /*primero hacia la derecha*/
        if((tocado)&&(*orientacion==2)){
            /*primero me despazo hasta la derecha*/
            while(tablero_disparos[primero_tocado_f-1][primero_tocado_c-1]=='@'){
                primero_tocado_c++;
            }
            /*voy disparando hasta el final del barco*/
            if ((tablero_disparos[primero_tocado_f-1][primero_tocado_c-1]=='?')&&(primero_tocado_c<=dim)){
                *c = primero_tocado_c;
            }
            /*ahora hacia la izquierda*/
            else{
                primero_tocado_c--;
                while(tablero_disparos[primero_tocado_f-1][primero_tocado_c-1]=='@'){
                    primero_tocado_c--;
                }
                if ((tablero_disparos[primero_tocado_f-1][primero_tocado_c-1]=='?')&&(primero_tocado_c>=0)){
                    *c = primero_tocado_c;
                }
            }
        }
    }

    /*esto es para cuando ya ha hundido el anterior barco y dispara aleatoriamente*/
    else{

        *f = P_aleatorio(1,dim);
        *c = P_aleatorio(1,dim);

        if(tablero_disparos[*f-1][*c-1]!='?'){
            while(tablero_disparos[*f-1][*c-1]!='?'){
                *f = P_aleatorio(1,dim);
                *c = P_aleatorio(1,dim);
            }
        }
    }

}

/*
HECHO
 accio P_procesa_hundido (fila:enter, col:enter, var tablero_disparos: taula de caracters, dim:enter);
 */
void P_procesa_hundido (int f, int c, char tablero_disparos[][COL_MAX], int dim)
{

    int orientacion;

        orientacion=-1;

        /*esto comprueba si el barco esta en posicion vertical o horizontal(1=vertical, 2=horizontal, 0=es de una casilla)*/
        if(tablero_disparos[f][c-1]=='@'){
            orientacion = 1;
        }
        else if(tablero_disparos[f-2][c-1]=='@'){
            orientacion = 1;
        }
        else if(tablero_disparos[f-1][c]=='@'){
            orientacion = 2;
        }
        else if(tablero_disparos[f-1][c-2]=='@'){
            orientacion = 2;
        }
        else{
            orientacion = 0;
        }

        /*primero para los barcos de una casilla*/
        if(orientacion==0){


            /*el de la izquierda*/
            if(c-2>=0){
                tablero_disparos[f-1][c-2]='.';
            }
            /*el de la derecha*/
            if(c<dim){
                tablero_disparos[f-1][c]='.';
            }
            /*el de encima*/
            if(f-2>=0){
                tablero_disparos[f-2][c-1]='.';
            }
            /*el de debajo*/
            if(f<dim){
                tablero_disparos[f][c-1]='.';
            }
            /*esquina superior izquierda*/
            if((c-2>=0)&&(f-2>=0)){
                tablero_disparos[f-2][c-2]='.';
            }
            /*esquina superior derecha*/
            if((c<dim)&&(f-2>=0)){
                tablero_disparos[f-2][c]='.';
            }
            /*esquina inferior izquierda*/
            if((c-2>=0)&&(f<dim)){
                tablero_disparos[f][c-2]='.';
            }
            /*esquina inferior derecha*/
            if((c<dim)&&(f<dim)){
                tablero_disparos[f][c]='.';
            }

        }

        /*ahora para el vertical*/
        if(orientacion==1){

            /*primero me desplazo hasta abajo*/
            while(tablero_disparos[f-1][c-1]=='@'){
                f++;
            }
            /*ahora pongo el agua de debajo*/
            if(f-1<dim){
                tablero_disparos[f-1][c-1]='.';
            }
            /*esquina inferior izquierda*/
            if((c-2>=0)&&(f-1<dim)){
                tablero_disparos[f-1][c-2]='.';
            }
            /*esquina inferior derecha*/
            if((c<dim)&&(f-1<dim)){
                tablero_disparos[f-1][c]='.';
            }
            /*ahora me despazp para arriba poniendo los lados*/
            f--;
            while(tablero_disparos[f-1][c-1]=='@'){
                f--;
                /*el de la izquierda*/
                if(c-2>=0){
                    tablero_disparos[f][c-2]='.';
                }
                /*el de la derecha*/
                if(c<dim){
                    tablero_disparos[f][c]='.';
                }
            }
            /*el de encima*/
            if(f-1>=0){
                tablero_disparos[f-1][c-1]='.';
            }
            /*esquina superior izquierda*/
            if((c-2>=0)&&(f-1>=0)){
                tablero_disparos[f-1][c-2]='.';
            }
            /*esquina superior derecha*/
            if((c<dim)&&(f-1>=0)){
                tablero_disparos[f-1][c]='.';
            }
        }

        /*para los horizontales*/
        if(orientacion==2){
            /*primero me despazo hasta la derecha*/
            while(tablero_disparos[f-1][c-1]=='@'){
                c++;
            }
            /*el de la derecha*/
            if(c-1<dim){
                tablero_disparos[f-1][c-1]='.';
            }
            /*esquina derecha superior*/
            if((c-1<dim)&&(f-2>=0)){
                tablero_disparos[f-2][c-1]='.';
            }
            /*esquina derecha inferior*/
            if((c-1<dim)&&(f<dim)){
                tablero_disparos[f][c-1]='.';
            }
            c--;
            while(tablero_disparos[f-1][c-1]=='@'){
                c--;
                /*el de encima*/
                if(f-2>=0){
                    tablero_disparos[f-2][c]='.';
                }
                /*el de debajo*/
                if(f<dim){
                    tablero_disparos[f][c]='.';
                }
            }
            /*el de la izquierda*/
            if(c-1>=0){
                tablero_disparos[f-1][c-1]='.';
            }
            /*esquina izquierda superior*/
            if((c-1>=0)&&(f-2>=0)){
                tablero_disparos[f-2][c-1]='.';
            }
            /*esquina izquierda inferior*/
            if((c-1>=0)&&(f<dim)){
                tablero_disparos[f][c-1]='.';
            }


        }

}

/*
HECHO
funcio P_aleatorio ( min: enter, max: enter) retorna enter;
Esta funcion crea un numero aleatorio entre el maximo y el minimo que se han introducido y usando la hora como semilla para el srand
 */
int P_aleatorio (int min, int max)
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
void P_coordenadas (char fila, int *col, int *fila_entero)
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
int P_leer_cadena (char cadena[], int dim, char centinela)
{
    int i;

    for(i=0; i<=dim; i++){
        scanf("%c", &cadena[i]);
    }

    cadena[i] = centinela;


    return i-1;
}

/*
HECHO
Esta funcion llena la tabla que se le pasa con el caracter deseado
 accio P_inicializa_matriz ( var matriz: taula de caracters, nfilas: enter, int ncols, car: caracter) es;
 */
void P_inicializa_matriz (char matriz[][COL_MAX], int nfilas, int ncols, char car)
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
void P_muestra_una_matriz (char matriz[][COL_MAX], int nfilas, int ncols)
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
void P_muestra_dos_matrices (char matriz1[][COL_MAX], char matriz2[][COL_MAX], int nfilas, int ncols)
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
bool P_guarda_record (char fitxer_record[], record_t record)
{
    FILE *f;
    data_t fecha;
    bool guardado;

    fecha = record.data;
    f = fopen(fitxer_record, "a");


    if (f == NULL){
        guardado = false;
    }
    else {
        fprintf(f, "%s %d %d %d %d", record.nom, record.punts, fecha.dia, fecha.mes, fecha.any);
        guardado = true;
    }

    fclose(f);

    return guardado;
}

/*
 esta funcion guarda los records de un firchero en una tabla y devuelve cuantos records hay
 funcio P_recupera_records (fitxer_record:taula de caracters, var records:taula de record_tipus, dim:enter ) retorna enter;
 */
int P_recupera_records (char fitxer_record[], record_t records[], int dim)
{

    FILE *f;
    int i;

    i = 0;

    f = fopen(fitxer_record, "r");

    if (f == NULL){
         printf("\n\nError! El fichero no existe!\n");
        i = -1;
    }
    else {
        if (feof(f)){
            printf("\n\nSecuencia vacia\n");
        }
        else {
            while(!feof(f) && i < dim){
                fscanf(f, "%s", records[i].nom);
                fscanf(f, "%d %d %d %d", &records[i].punts, &records[i].data.dia, &records[i].data.mes, &records[i].data.any);
                i++;
            }

        }

        fclose(f);
    }

    return i;
}


/** -------------------------------------------------------
 PROCEDIMENTS ADDICIONALS A DESENVOLUPAR
 ------------------------------------------------------- */

/*
funcio P_nuevo_disparo (var f:caracter, var c:enter, dim:enter) retorna boolea;
 */
bool P_nova_jugada (char *f, int *c, int dim)
{
    printf("Procediment P_nova_jugada\n");
    return true;
}

/*
 funcio P_guarda_partida (nom_fitxer:taula de caracters, dim:enter, modo_juego:enter, turno:enter, jugadores:taula de jugador_t) retorna boolea;
 */
bool P_guarda_partida (char fitxer_record[], int dim, int modo_juego, int turno, jugador_t jugadores[])
{
    printf("Procediment P_guardar_partida\n");
    return true;
}

/*
 funcio P_recupera_partida (nom_fitxer:taula de caracters, var dim:enter, var modo_juego: enter,
 var turno:enter, var jugadores:taula de jugador_t) retorna boolea;
 */
bool P_recupera_partida (char fitxer_record[], int *dim, int *modo_juego, int *turno, jugador_t jugadores[])

{
    printf("Procediment P_recupera_partida\n");
    return true;
}

/*
 funcio P_coloca_barcos (var tablero_barcos:taula de caracters, dim: enter) retorna boolea;
 */
bool P_coloca_barcos (char tablero_barcos[][DIM_MAX], int dim)
{
    printf("Procediment P_coloca_barcos\n");
    return  true;
}


/** -------------------------------------------------------
 PROCEDIMIENTOS AÑADIDOS POR NOSOTROS
 ------------------------------------------------------- */


/*
Esta funcion actualiza la tabla de disparos dependiendo del resultado que nos de B_dispara
accio P_actualiza_disparos(f : entero, c : entero, var tabla_disparos : tabla de caracter, resultado : entero, dim : entero)
*/
void P_actualiza_disparos(int f, int c, char tablero_disparos[][COL_MAX], int resultado, int dim){


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
char P_a_letras (int f){
    char fila;

    fila=f +'A'-1;

    return fila;
}


void P_jugar0(char tablero_barcos[][COL_MAX], char tablero_disparos[][COL_MAX], int dim){

    int col, hundidos, f, i, resultado, mida, primero_tocado_c, primero_tocado_f, orientacion, resultado_lanzamiento;
    float puntuacion, efectividad_total,efectividad;
    char fila;
    bool tocado;
    record_t record;


    /*escribo las dimensiones de las tablas*/
    printf("\n\nLas matrices son %d x %d\n\n", dim, dim);


    P_muestra_dos_matrices(tablero_barcos,tablero_disparos,dim,dim);

    i = 0;
    efectividad=0;
    resultado_lanzamiento = 0;
    efectividad_total=0;
    hundidos = 0;
    tocado = false;
    orientacion = 0;
    primero_tocado_c=-1;

    while (hundidos<=9){
            /*primero decido las coordenadas del disparo*/
            P_decide_disparo(&f, &col,tablero_disparos,dim,tocado, primero_tocado_c, primero_tocado_f,&orientacion);

            /*paso las filas a letras mayusculas porque en P_decide_disparo se nos pide que lo hagamos con f (que es int) y en
            B_dispara hay que usar fila(que es char)*/
            fila = P_a_letras(f);
            printf("\nLas coordenadas del disparo son: %c %d\n",fila,col);


            /*compruebo el resultado del disparo*/
            resultado = B_dispara(fila,col,tablero_barcos,&mida);

            /*dependiendo del resultado P_decide_disparo se comportara diferente*/
            if (resultado==2){
                tocado=true;
                if(primero_tocado_c==-1){
                    primero_tocado_c = col;
                    primero_tocado_f = f;
                }

            }
            else if(resultado==3){
                /*notificacion de sonido de hundir barco*/
                printf("%c", 7);
                tocado=false;
                orientacion = 0;
                primero_tocado_c=-1;
            }

            resultado_lanzamiento = resultado_lanzamiento + 4 - resultado;

            /*con P_actualiza_disparos digo el resultado del disparo y cambio la tabla de disparos utilizando P_procesa hundido*/
            P_actualiza_disparos(f,col,tablero_disparos,resultado,dim);

            /*vuelvo a mostrar las dos matrices*/
            P_muestra_dos_matrices(tablero_barcos,tablero_disparos,dim,dim);

            if(resultado==3){

                hundidos++;
                efectividad = ((2*(float)mida)-1)/(float)resultado_lanzamiento;
                efectividad_total = efectividad_total + (float)efectividad;
                resultado_lanzamiento = 0;
            }

            /*Pongo un contador para saber cuantos turnos llevo*/
            i++;
            printf("\n\n\nLleva %d turnos y %d barcos hundidos.", i, hundidos);

            P_pausa();
            system(NETEJA_PANTALLA);
    }

    puntuacion = (100.0 * (float)dim / (float)i) * (float)efectividad_total;

    record.punts = puntuacion;
    printf("\nIntroduce tu nombre: ");
    scanf("%s", record.nom);
    printf("\n\n%s", record.nom);
    record.data=P_data_avui();

    P_guarda_record("records.txt", record);

    printf("\n\n\nSe acabo la partida.");

}

int P_iniciar_partida(char tablero_barcos[][COL_MAX], char tablero_disparos[][COL_MAX], int *modo){

    int dim;

    printf("Introduce el la dimension deseada para las tablas(8, 9 o 10): ");
    scanf("%d", &dim);
    while((dim!= 8) && (dim!=9) && (dim!=10)){
        printf("Introduce una dimension valida para las tablas(8, 9 o 10): ");
        scanf("%d", &dim);
    }

    printf("Introduce el modo de juego deseado (0 o 1): ");
    scanf("%d", modo);
    while((*modo!= 0) && (*modo!=1)){
        printf("Introduce el modo de juego deseado (0 o 1): ");
        scanf("%d", modo);
    }


    /*inicializo las dos matrices */
    P_inicializa_matriz(tablero_disparos,dim,dim,'?');
    B_inicializa_barcos(tablero_barcos,dim);

    return dim;

}



/*
esta funcion coje la tabla de records y la dimension de cuentos records hay(no de la tabla);
accio P_muestra_records (records[]: record_T, dim: entero)*/
void P_muestra_records (record_t records[], int dim){

    char fichero[12]={"records.txt"};
    int i, j, pos, dim_tabla;
    record_t maxim;

    /*leo los records del fichero en la tabla*/

    dim_tabla=P_recupera_records(fichero, records, dim);

    /*aplico un algoritmo de ordenacion*/
    i=0;
    j=0;

    for(i=0; i<dim_tabla-1; i++){
        maxim=records[i];
        pos=i;
        for(j=i+1; j<dim_tabla; j++){
            if(records[j].punts>maxim.punts){
                maxim=records[j];
                pos=j;
            }
        }
        records[pos]=records[i];
        records[i]=maxim;

    }

    /*escribo los primero diez records*/
    i=0;

    while(i<10){
        printf("\n\n%da posicion:        %s    %d puntos    %d/%d/%d", i+1, records[i].nom, records[i].punts, records[i].data.dia, records[i].data.mes, records[i].data.any);
        i++;
    }

}

void P_jugar1(char tablero_barcos[][COL_MAX], char tablero_disparos[][COL_MAX], int dim){

    int col, hundidos, f, i, resultado, mida, resultado_lanzamiento;
    char fila;
    float puntuacion, efectividad_total, efectividad;
    record_t record;


    /*escribo las dimensiones de las tablas*/
    printf("\n\nLas matrices son %d x %d\n\n", dim, dim);
    P_muestra_una_matriz(tablero_disparos, dim, dim);

    i = 0;
    resultado_lanzamiento = 0;
    efectividad_total=0;
    hundidos = 0;
    efectividad=0;
    puntuacion=0;

    while (hundidos<=9){



            /*primero pregunto las coordenadas del disparo*/
            printf("\n\nintroduce la fila y columna deseada: ");
            scanf("%c%d", &fila, &col);

            if(('a'<=fila)&&(fila<='z')){
                fila=fila-'a'+'A';
            }

            /*lo pongo despues de leer las coordenadas para que el jugador pueda mirar a donde quiere disparar*/
            system(NETEJA_PANTALLA);

            /*paso la fila a numeros para usarlo en la funcion P_actualiza_disparos*/
            f=fila-'A'+1;


            printf("\nLas coordenadas del disparo son: %c %d\n",fila,col);


            /*compruebo el resultado del disparo*/
            resultado = B_dispara(fila,col,tablero_barcos,&mida);


            resultado_lanzamiento = resultado_lanzamiento + 4 - resultado;

            /*con P_actualiza_disparos digo el resultado del disparo y cambio la tabla de disparos utilizando P_procesa hundido*/
            P_actualiza_disparos(f,col,tablero_disparos,resultado,dim);

            /*vuelvo a mostrar las dos matrices*/
            P_muestra_una_matriz(tablero_disparos, dim, dim);

            if(resultado==3){
                /*notificacion de sonido de hundir barco*/
                printf("%c", 7);
                hundidos++;
                efectividad = ((2*(float)mida)-1)/(float)resultado_lanzamiento;
                efectividad_total = efectividad_total + (float)efectividad;
                resultado_lanzamiento = 0;
            }

            /*Pongo un contador para saber cuantos turnos llevo*/

            i=i+1;

            /*tengo que poner i/2 porque me cuenta i++  de dos en dos y no encontramos la razon*/
            printf("Lleva %d turnos y %d barcos hundidos.", i/2, hundidos);
    }

    P_muestra_dos_matrices(tablero_barcos,tablero_disparos,dim,dim);

    puntuacion = (100.0 * (float)dim / (float)i/2) * (float)efectividad_total;

    record.punts = puntuacion;
    printf("\nIntroduce tu nombre: ");
    scanf("%s", record.nom);
    printf("\n\n%s", record.nom);
    record.data=P_data_avui();

    P_guarda_record("records.txt", record);
    printf("\n\n\nSe acabo la partida.");
}



