
#include <hls_stream.h>
#include <ap_axi_sdata.h>


// 32 bit integer with side channel
typedef ap_axis<32,2,5,6> intSdCh;


void doGain(hls::stream<intSdCh> &inStream, hls::stream<intSdCh> &outStream, int gain){
#pragma HLS TOP name=AplicarGanancia

#pragma HLS INTERFACE mode=axis port=outStream
#pragma HLS INTERFACE mode=axis port=inStream
#pragma HLS INTERFACE mode=s_axilite port=gain bundle=CRTL_BUS
#pragma HLS INTERFACE mode=s_axilite port=return bundle=CRTL_BUS


	for (int idx=0; idx < (1000); idx++ ){
#pragma HLS PIPELINE
		//read and cache
		intSdCh valIn = inStream.read();
		intSdCh valOut;

		valOut.data = valIn.data * gain;

		// just copy from the input the other side-channels (keep, strobe, id, dest, last)
		valOut.keep = valIn.keep;
		valOut.strb = valIn.strb;
		valOut.user = valIn.user;
		valOut.id = valIn.id;
		valOut.dest = valIn.dest;
		valOut.last = valIn.last;

		outStream.write(valOut);

	}

}





