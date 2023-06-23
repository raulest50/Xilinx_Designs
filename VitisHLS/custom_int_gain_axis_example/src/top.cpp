#include <hls_stream.h>


#define N 1024




void top_entity(hls::stream<int> &Ain, hls::stream<int> &Aout){
#pragma HLS TOP name=top_entity
#pragma HLS INTERFACE mode=axis port=Ain
#pragma HLS INTERFACE mode=axis port=Aout
#pragma HLS INTERFACE mode=s_axilite port=return bundle=CRTL_BUS

	for(int n=0; n < N; n++){
#pragma HLS PIPELINE
		int vin = Ain.read();
		int vout = vin*2;
		Aout.write(vout);
	}
}
