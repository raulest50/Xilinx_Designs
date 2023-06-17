
#define STATE_WAIT 0
#define STATE_RECEIVE 1
#define STATE_RECEIVE_LAST_N_COMPUTE 3
#define STATE_SEND_2ND_PART 2

#define N 8192 // cantidad de puntos de la fft

#define CHUNCK_SIZE 1024 // cada paquete de tcp/ip contendra 1024 bytes siempre

#define TOTAL_BYTE_TRANSFER 8192*2*4

#define TOTAL_CHUNCKS (TOTAL_BYTE_TRANSFER/CHUNCK_SIZE) // amount of 1024 chuncks of bytes


#define AXIS_INTERFACE_FFT_IN 0
#define AXIS_INTERFACE_FFT_OUT 0
#define AXIS_INTERFACE_FFT_CONFIG 1


void usleep(unsigned long useconds);


void doFFT(float *Ain, float *Aout);


