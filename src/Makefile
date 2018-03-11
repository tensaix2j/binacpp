

libcurl_dir=../lib/libcurl-7.56.0
libcurl_include=${libcurl_dir}/include
libcurl_lib=${libcurl_dir}/lib

jsoncpp_dir=../lib/jsoncpp-1.8.3
jsoncpp_include=${jsoncpp_dir}/include
jsoncpp_src=${jsoncpp_dir}/src


libwebsockets_dir=../lib/libwebsockets-2.4.0
libwebsockets_include=${libwebsockets_dir}/include
libwebsockets_lib=${libwebsockets_dir}/lib


build_dir=../lib/libbinacpp/lib
objects=$(build_dir)/jsoncpp.o $(build_dir)/binacpp_utils.o $(build_dir)/binacpp_logger.o $(build_dir)/binacpp.o  $(build_dir)/binacpp_websocket.o

build_include=../lib/libbinacpp/include


$(build_dir)/libbinacpp.so: $(objects)
	g++ -I$(libcurl_include) -I$(jsoncpp_include) -I$(libwebsockets_include)  \
	-L$(libcurl_lib) \
	-L$(libwebsockets_lib) \
	$(objects) \
	-shared \
	-lcurl -lcrypto -lwebsockets -fPIC -o $@

	# Make a new copy of the header too
	cp *.h  $(build_include)




$(build_dir)/binacpp.o: binacpp.cpp binacpp.h 
	g++ -I$(libcurl_include) -I$(jsoncpp_include) -c binacpp.cpp  -fPIC   -o $(build_dir)/binacpp.o 


$(build_dir)/binacpp_websocket.o: binacpp_websocket.cpp binacpp_websocket.h 
	g++ -I$(libwebsockets_include) -I$(jsoncpp_include) -c binacpp_websocket.cpp  -fPIC   -o $(build_dir)/binacpp_websocket.o


$(build_dir)/binacpp_logger.o: binacpp_logger.cpp binacpp_logger.h 
	g++ -c binacpp_logger.cpp  -fPIC   -o $(build_dir)/binacpp_logger.o 



$(build_dir)/binacpp_utils.o: binacpp_utils.cpp binacpp_utils.h 
	g++ -c binacpp_utils.cpp -fPIC   -o $(build_dir)/binacpp_utils.o 


$(build_dir)/jsoncpp.o: $(jsoncpp_src)/jsoncpp.cpp
	g++ -I$(jsoncpp_include) -c $(jsoncpp_src)/jsoncpp.cpp -fPIC  -o  $(build_dir)/jsoncpp.o

clean:
	rm $(build_dir)/*.o
	rm $(build_dir)/*.so






