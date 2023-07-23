


#include <hls_fft.h>
#include <ap_fixed.h>

#include "rom.h"

using namespace std;

struct config1 : hls::ip_fft::params_t {
	static const unsigned ordering_opt = hls::ip_fft::natural_order;
	static const unsigned config_width = FFT_CONF_WIDTH;
	static const unsigned input_width = 12;
	static const unsigned output_width = 12;
	static const unsigned scaling_opt = hls::ip_fft::scaled;
	static const unsigned rounding_opt = hls::ip_fft::truncation;
};


typedef hls::ip_fft::config_t<config1> config_t;
typedef hls::ip_fft::status_t<config1> status_t;


void do_fft(
		data_in Ain[FFT_LENGTH],
		data_out Aout[FFT_LENGTH]
		);

void Dh1(data_in Ain[FFT_LENGTH], data_out Aout[FFT_LENGTH]);

void dt_mover_in(data_in vin[FFT_LENGTH], data_out vout[FFT_LENGTH]);

void dt_mover_out(data_in vin[FFT_LENGTH], data_out vout[FFT_LENGTH]);




