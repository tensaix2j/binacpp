



This is the source of libBinaCPP which is CPP Library for Binance API, running make in this folder will compile libbinacpp.so from source.

The libbinacpp.so compiled will be generated in ../lib/libbinacpp/lib and the headers in ../lib/libbinacpp/include 

You only need to recompile the src here if you need to modify the source of libBinaCPP.





To use the library in your C++ project,  just do -I<path to libBinaCPP include> and -L<path to libBinaCPP lib> and a -lbinacpp for linker.

You can view the examples in ../example folder for references on how to use libBinaCPP.





