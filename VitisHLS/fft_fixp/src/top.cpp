

#include "top.h"



void Dh1(data_in Ain[FFT_LENGTH], data_out Aout[FFT_LENGTH]){
#pragma HLS INTERFACE mode=ap_fifo depth=1 port= Ain, Aout
#pragma HLS INTERFACE mode=ap_ctrl_none port=return

	data_in xn[FFT_LENGTH];
	data_out xk[FFT_LENGTH];

	dt_mover_in(Ain, xn);

	do_fft(xn, xk);

	dt_mover_out(xk, Aout);

}


void dt_mover_in(data_in vin[FFT_LENGTH], data_out vout[FFT_LENGTH]){
	L0:
	for (int k=0; k < FFT_LENGTH; k++){
		vout[k] = vin[k];
	}
}

void dt_mover_out(data_in vin[FFT_LENGTH], data_out vout[FFT_LENGTH]){
	L0:
	for (int k=0; k < FFT_LENGTH; k++){
		vout[k] = vin[k];
	}
}



void do_fft(
		data_in xn[FFT_LENGTH],
		data_out xk[FFT_LENGTH] )
{
#pragma HLS dataflow
#pragma HLS INLINE recursive

	config_t fft_config;
	status_t fft_status;

	fft_config.setDir(1);
	fft_config->setSch(0x2AB);

	hls::fft<config1>(xn, xk, &fft_status, &fft_config);
}
