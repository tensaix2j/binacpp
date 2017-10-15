

libcurl_dir=../lib/libcurl-7.56.0
libcurl_include=${libcurl_dir}/include
libcurl_lib=${libcurl_dir}/lib

jsoncpp_dir=../lib/jsoncpp-1.8.3
jsoncpp_include=${jsoncpp_dir}/include
jsoncpp_src=${jsoncpp_dir}/src


build_dir=../bin
objects=$(build_dir)/jsoncpp.o $(build_dir)/binacpp_utils.o $(build_dir)/binacpp_logger.o $(build_dir)/binacpp.o 





example: $(objects)
	g++ -I$(libcurl_include) -I$(jsoncpp_include) -I$(jsoncpp_include)  \
	example.cpp \
	-L$(libcurl_lib) \
	$(objects) \
	-lcurl -lcrypto -lsqlite3 -o ${build_dir}/example


$(build_dir)/binacpp.o: binacpp.cpp binacpp.h 
	g++ -I$(jsoncpp_include) -c binacpp.cpp  -o ${build_dir}/binacpp.o 


$(build_dir)/binacpp_logger.o: binacpp_logger.cpp binacpp_logger.h 
	g++ -c binacpp_logger.cpp  -o ${build_dir}/binacpp_logger.o 



$(build_dir)/binacpp_utils.o: binacpp_utils.cpp binacpp_utils.h 
	g++ -c binacpp_utils.cpp -o ${build_dir}/binacpp_utils.o 


$(build_dir)/jsoncpp.o: $(jsoncpp_src)/jsoncpp.cpp
	g++ -I$(jsoncpp_include) -c $(jsoncpp_src)/jsoncpp.cpp -o  ${build_dir}/jsoncpp.o

clean:
	rm ${build_dir}/*.o
	rm ${build_dir}/binawatch





