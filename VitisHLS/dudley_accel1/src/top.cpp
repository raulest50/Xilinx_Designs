#include <complex>
#include "top.h"

void call_fft_ip(std::complex<float> fft_input[FFT_LENGTH_MAX], std::complex<float> fft_output[FFT_LENGTH_MAX],
        //unsigned size,
		bool direction) {
    config_t fft_config;
    status_t fft_status;
    fft_config.setDir(direction);
    //fft_config.setNfft(size);
    hls::fft<fft_param>(fft_input, fft_output, &fft_status, &fft_config);
}

void read_input_data_from_stream(fft_stream &stream_input, std::complex<float> fft_input[FFT_LENGTH_MAX]) {
    data_t data_in;
    int i = 0;
    do {
#pragma HLS PIPELINE II = 1
        data_in = stream_input.read();
        fft_input[i++] = data_in.data;
    } while (!data_in.last);
}

void write_output_data_to_stream(fft_stream &stream_output, std::complex<float> fft_output[FFT_LENGTH_MAX]){ //,
        //unsigned size) {
    data_t data_out;
    data_out.keep = -1;
    data_out.strb = -1;

    for (int i = 0; i < FFT_LENGTH_MAX; i++) {
#if defined(USE_FLOAT)
#pragma HLS PIPELINE //II = 2
        std::complex<float> data = fft_output[i];
        data_out.data = data.real();
        data_out.last = 0;
        stream_output.write(data_out);
        data_out.data = data.imag();
        data_out.last = (i == (FFT_LENGTH_MAX - 1));
        stream_output.write(data_out);
#else
#pragma HLS PIPELINE //II = 1
        data_out.data = fft_output[i];
        data_out.last = (i == (FFT_LENGTH_MAX - 1));
        stream_output.write(data_out);
#endif
    }
}

void top(fft_stream &stream_input, fft_stream &stream_output){ //, unsigned size) {
#pragma HLS INTERFACE axis port = stream_input
#pragma HLS INTERFACE axis port = stream_output
//#pragma HLS INTERFACE s_axilite port = size
#pragma HLS INTERFACE s_axilite port = return

    std::complex<float> Ain[FFT_LENGTH_MAX] __attribute__((no_ctor));
    std::complex<float> A_Dh[FFT_LENGTH_MAX] __attribute__((no_ctor));
    std::complex<float> fft_out[FFT_LENGTH_MAX] __attribute__((no_ctor));
    std::complex<float> ifft_out[FFT_LENGTH_MAX] __attribute__((no_ctor));

#pragma HLS STREAM variable = stream_input depth=8192 dim=1
#pragma HLS STREAM variable = stream_output depth=8192 dim=1
#pragma HLS STREAM variable = Ain depth=8192 dim=1
#pragma HLS STREAM variable = A_Dh depth=8192 dim=1
#pragma HLS STREAM variable = fft_out depth=8192 dim=1
#pragma HLS STREAM variable = ifft_out depth=8192 dim=1


#pragma HLS DATAFLOW
//#pragma HLS PIPELINE

    /*
    // FFT point must be at least 8(2^3) points
    if (size < 3) {
        // If size is smaller than 3, FFT is performed with the maximum value
        size = TWO_TO_THE_POWER_OF_N_MAX;
    }
	*/

    read_input_data_from_stream(stream_input, Ain);



    call_fft_ip(Ain, fft_out, true); // call_fft_ip(Ain, fft_out, size, true);

    Dispersion(fft_out, A_Dh);

    call_fft_ip(A_Dh, ifft_out, false); // call_fft_ip(fft_out, Ain, size, false);

    //call_fft_ip(Ain, fft_out, size, false);




    write_output_data_to_stream(stream_output, ifft_out); //, (1 << size));
}


void Dispersion(std::complex<float> Ain[FFT_LENGTH_MAX], std::complex<float> A_Dh[FFT_LENGTH_MAX]){
	for(int n=0; n<FFT_LENGTH_MAX; n++){
#pragma HLS PIPELINE
		A_Dh[n] = Ain[n]*D_half[n]*1.2264e-04f;
	}
}
