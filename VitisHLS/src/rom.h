
#include <complex>

typedef std::complex<dty_fft_in> data_in;
typedef std::complex<dty_fft_out> data_out;

typedef ap_fixed<FFT_IN_WIDTH, 1> dty_fft_in;
typedef ap_fixed<FFT_IN_WIDTH, 1> dty_fft_out;

data_in test_signal[FFT_LENGTH] = { };
