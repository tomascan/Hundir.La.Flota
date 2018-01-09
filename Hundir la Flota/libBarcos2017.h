/*----------------------------------------------------------------
 |	Autor: Professors de Fonaments de Programacio
 |	Data: Novembre 2016                 Versio: 2.0
 |-----------------------------------------------------------------|
 |   Nom projecte: libBarcos2017
 |   Nom fitxer: libBarcos2017.h
 |   Descripcio del Programa: capcaleres i rutines donades.
 |
 | ----------------------------------------------------------------*/

#ifndef VAIXELLS_H_INCLUDED
#define VAIXELLS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <stdbool.h>

#define DIM_MAX     10
#define COL_MAX     DIM_MAX
#define DIM_MIN     8

enum orientacio
{
    HORITZONTAL = 2,
    VERTICAL = 1
};

enum casella
{
    CASELLA_BUIDA = '?',
    CASELLA_AIGUA = '.',
    CASELLA_VAIXELL = '@',
    CASELLA_VAIXELL_TOCAT = 'X',
    CASELLA_AIGUA_TOCADA = '-'
};

enum tret
{
    RES_ERROR = -1,
    RES_REPETIT = 0,
    RES_AIGUA = 1,
    RES_TOCAT = 2,
    RES_ENFONSAT = 3
};

/** capcaleres funcions */
/** =========================================================================
 accio B_inicializa_barcos (var tablero_barcos:taula de caracters, dim:enter);

 - Inicialitza la disposicio dels vaixells dins del taulell de vaixells.

 - Parametres formals:
    dim: (per valor) dimensio del taulell, ha de ser > DIM_MIN i < DIM_MAX.
        Abans de fer la crida, s'ha de validar que dim sigui correcte.
    tablero_barcos: (per referencia) taula de dues dimensions
        DIM_MAX x DIM_MAX. La mida del taulell real dependra del
        parametre dim: dim x dim.
 =========================================================================*/
extern void B_inicializa_barcos (char tablero_barcos[][COL_MAX], unsigned int dim);

/** =========================================================================
 accio B_inicializa_barcos_fijo (var tablero_barcos:taula de caracter, dim:enter);

 - Inicialitza la disposicio dels vaixells dins del taulell de vaixells
 sempre amb la mateixa configuracio. Serveix per a fer proves.

 - Parametres formals:
 dim: (per valor) dimensio del taulell, ha de ser > DIM_MIN i < DIM_MAX.
 Abans de fer la crida, s'ha de validar que dim sigui correcte.
 taulell_vaixells: (per referencia) taula de dues dimensions
 DIM_MAX x DIM_MAX. La mida del taulell real dependra del
 parametre dim: dim x dim.
 =========================================================================*/
void B_inicializa_barcos_fijo (char tablero_barcos[][COL_MAX], unsigned int dim);

/** =========================================================================
 funcio B_dispara (f:caracter, c:enter, var tablero_barcos:taula de caracters,
                    var mida:enter) retorna enter;

 - Retorna el resultat del llancament (REPETIT-0, AIGUA-1...) i
 actualitza el taulell de vaixells amb les anotacions pertinents:
 CASELLA_VAIXELL_TOCAT o CASELLA_AIGUA_TOCADA.
 Si hi ha un error en la fila o columna, o en el contingut de la casella,
 retorna ERROR.

 - Parametres formals:
    fila: (per valor) lletra de la fila, en majuscules. Ha de ser
        correcta d'acord amb les dimensions del taulell.
    col: (per valor) n˙mero de la columna, ha de ser correcte d'acord
        amb les dimensions del taulell.
        Abans de fer la crida, s'ha de validar que fila i col siguin correctes!
        taulell_vaixells: (per referËncia) taula de dues dimensions
        DIM_MAX x DI

        M_MAX.
 =========================================================================*/
extern int B_dispara (char fila, int col, char tablero_barcos[][COL_MAX], int *mida);

#endif /* VAIXELLS_H_INCLUDED */
