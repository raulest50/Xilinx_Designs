


#include <hls_fft.h>
#include <ap_fixed.h>

#include "rom.h"

const char FFT_CONF_WIDTH = 16;
const char FFT_IN_WIDTH = 12;
const char FFT_NFFT_MAX = 13;
const char FFT_LENGTH = 1 << FFT_NFFT_MAX; // = 2^FFT_NFFT_MAX

struct config1 : hls::ip_fft::params_t{
	static const unsigned ordering_opt = hls::ip_fft::natural_order;
	static const unsigned config_width = FFT_CONF_WIDTH;

};


typedef hls::ip_fft::config_t<config1> config_t;
typedef hls::ip_fft::status_t<config1> status_t;


void do_fft(
		data_in Ain[FFT_LENGTH],
		data_out Aout[FFT_LENGTH]
		);

void Dh1(data_in Ain[FFT_LENGTH], data_out Aout[FFT_LENGTH]);




