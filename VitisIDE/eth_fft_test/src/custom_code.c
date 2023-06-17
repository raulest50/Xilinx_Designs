


#include "custom_code.h"
#include <stdio.h>
#include <string.h>
#include "mb_interface.h"
#include "lwip/tcp.h"


void eth_interaction(struct pbuf *p, u32 *estado,
						struct tcp_pcb *tpcb,
						float *Ain, float *Aout,
						u32 *c_count,
						signed char *err);



char *res;



void eth_interaction(struct pbuf *p, u32 *estado,
						struct tcp_pcb *tpcb,
						float *Ain, float *Aout,
						u32 *c_count,
						signed char *err){

	char *dest = (char *) Ain;
	char *src = (char *) p->payload;

	switch(*estado){

		case STATE_WAIT:
			char c0, c1;
			c0 = src[0];
			c1 = src[1];
			if(c0=='$' && c1=='d'){
				*estado = STATE_RECEIVE;
				*err = tcp_write(tpcb, "&rc\n", 4, 1);
			}
		break;



		case STATE_RECEIVE:
			if(*c_count < TOTAL_CHUNCKS - 2 ){ // chunck count < n-2 transfers
				memcpy( dest + CHUNCK_SIZE*(*c_count), src, CHUNCK_SIZE);
				*c_count = *c_count + 1;
				//xil_printf("chunck : %d \n", *c_count);
				//*err = tcp_write(tpcb, "&rc\n", 4, 1);
			} else{ // n-1 trasfer
				memcpy( dest + CHUNCK_SIZE*(*c_count), src, CHUNCK_SIZE);
				*c_count = *c_count + 1;
				*estado = STATE_RECEIVE_LAST_N_COMPUTE;
				//xil_printf("chunck : %d \n", *c_count);
				//xil_printf("last paquet remaining \n");
				//*err = tcp_write(tpcb, "&rc\n", 4, 1);
			}

		break;



		case STATE_RECEIVE_LAST_N_COMPUTE: // the n chunck transfer

			memcpy( dest + CHUNCK_SIZE*(*c_count), src, CHUNCK_SIZE);
			doFFT(Ain, Aout);
			res = (char *) Aout;

			//xil_printf("chunck : %d \n", *c_count);
			*err = tcp_write(tpcb, res + 8192*4, 8192*4, 1);
			*c_count = 0;
			*estado = STATE_SEND_2ND_PART;
		break;



		case STATE_SEND_2ND_PART:
			*err = tcp_write(tpcb, res, 8192*4, 1);
			*c_count = 0;
			*estado = STATE_WAIT;
		break;


		default:
			*c_count = 0;
			*estado = STATE_WAIT;

	}

}



void doFFT(float *Ain, float *Aout){
	nputfsl( (u32) 1, AXIS_INTERFACE_FFT_CONFIG);
	usleep(10);
	for(int i=0; i<2*N; i++){
		nputfsl(Ain[i], AXIS_INTERFACE_FFT_IN);
	}
	usleep(500);
	for(int i=0; i<2*N; i++){
		ngetfsl(Aout[i], AXIS_INTERFACE_FFT_OUT);
	}
}
