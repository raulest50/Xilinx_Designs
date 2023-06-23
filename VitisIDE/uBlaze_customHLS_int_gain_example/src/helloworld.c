

#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"

#include "xparameters.h"
#include "xtop_entity.h"
#include "mb_interface.h"

void usleep(ULONG useconds);

void pipeline(int *Ain, int *Aout, int len, int gap);

int main()
{
    init_platform();

    xil_printf("started \n");

    int A[1024];
    int R[1024];

    for(int n=0; n<1024; n++){
    	A[n] = n;
    }

    XTop_entity top;
    XTop_entity_Config *cfg;

    cfg = XTop_entity_LookupConfig(XPAR_TOP_ENTITY_0_DEVICE_ID);
    XTop_entity_CfgInitialize(&top, cfg);

    XTop_entity_Start(&top);

    /*
    for(int n=0; n<1028; n++){
    	if(n<1024){
    		nputfsl(A[n],0);
    	}
    	if(n>2){
    		ngetfsl(R[n-3], 0);
    	}
	}
	*/

    pipeline(A, R, 1024, 3);

    for(int n=0; n<6; n++){
		xil_printf(" [%d] - %d \n", n, R[n]);
	}

    for(int n=1018; n<1024; n++){
		xil_printf(" [%d] - %d \n", n, R[n]);
	}

    cleanup_platform();
    return 0;
}


/**
 * en hls la latencia es de 1027 para 1024 muestras. es decir que pasan 3 muestras antes de tener la primera muestra a la salida
 * por eso primero hay que hacer 3 nputs antes de empezar a hacer un nget. de esta forma no hay que hacer ningun usleep para empezar a obtener
 * resultados. ademas si no se sigue esta dinamica quedan trocados 1 o 2 indices los resultados. posiblemente se deba a la cantidad de registros
 * internos del bloque custom hecho con hls. hay un espacio de 3 muestras antes de que se empiece a propagar a la salida las respuestas del bloque.
 */
void pipeline(int *Ain, int *Aout, int len, int gap){
	for(int n=0; n < (len+gap) ; n++){
		if(n<len){
			nputfsl(Ain[n],0);
		}
		if(n > gap-1){
			ngetfsl(Aout[n-gap], 0);
		}
	}
}
