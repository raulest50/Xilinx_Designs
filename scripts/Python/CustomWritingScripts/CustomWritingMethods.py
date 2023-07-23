import numpy as np


def cmpxArray2str(np_array, el_pr):
    """ numpy array to std::complex form (c++) as string for copy and pasting """
    s = ""
    n = 1
    for x in np_array[0:-1]:
        s += f"{{ {np.real(x)}, {np.imag(x)} }}," # writes up to N-1 complex numbers with ending comma
        if n%el_pr == 0:
            s += "\n" # adds new line each el_pr elements
        n += 1
    s += f"{{ {np.real( np_array[-1] )}, {np.imag( np_array[-1] )} }}" # writes the last one without ending comma
    return s