# High Performance Computing Applications with Xilinx
Proyectos hechos con vivado, vitis IDE y vitis HLS.


---
### recordatorios cosas pendientes


-agregar lo del memory swap para ubuntu

-size hex para ver del .elf cuanto corresponde a codigo de programa.

-puerto fsl axi stream microblaze

- en el mapa de memoria de vivado como excluir regiones de memoria. configuracion cache microblaze
instruction cache y data cache

- parametros del dma y el fft ip cores

- CDMA majeno (pendiente)


- Axi4 Stream width converter

-fft floating point axi stream

- other IPs like slices floating point etc  


- clock domain crossing



- linker file
Heap stack size, memory sections.
microblaze gcc compiler directives.
unsigned char __attribute__((section(" .mem_location"))) buf[128] __attribute__ ((aligned(512)));
int __attribute__((at(  ADDRESS_HERE  ))) x;
etc
ver: mcuoneclipse.com/2012/11/01/defining-variables-at-absolute-address-with-gcc/
etc
data alignment.
