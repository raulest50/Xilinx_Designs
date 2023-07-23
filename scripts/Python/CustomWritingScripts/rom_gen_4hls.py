

import numpy as np
from numpy import sin, linspace, pi
from matplotlib import pyplot as plt
from CustomWritingMethods import cmpxArray2str as ar2str
from fxpmath import Fxp

def view_signal(signal):
    sk = np.fft.fft(signal)
    skf = np.abs(np.fft.fftshift(sk))

    fig, axs = plt.subplots(2)
    axs[0].plot(signal)
    fig.suptitle("Signal and its Spectrum")
    axs[1].plot(skf)
    plt.show()


file_name = "rom.h"

N = 8192
impulse = np.zeros(N)
impulse[4000:4010] = 50
chirp = sin(linspace(0, 2*pi, N)**8/10000)
view_signal(chirp)

chirp_fxp = Fxp(chirp, signed=True, n_word=12, n_frac=10)
view_signal(chirp_fxp)
complex_data_string = ar2str(chirp_fxp, 4)

body = f"""
#include <complex>

const char FFT_CONF_WIDTH = 16;
const char FFT_IN_WIDTH = 12;
const char FFT_NFFT_MAX = 13;
const char FFT_LENGTH = 1 << FFT_NFFT_MAX; // = 2^FFT_NFFT_MAX

typedef ap_fixed<FFT_IN_WIDTH, 1> dty_fft_in;
typedef ap_fixed<FFT_IN_WIDTH, 1> dty_fft_out;

typedef std::complex<dty_fft_in> data_in;
typedef std::complex<dty_fft_out> data_out;

data_in test_signal[FFT_LENGTH] = {{
 
{complex_data_string}

}};

"""

file = open(file_name, 'w')
file.write(body)
file.close()