
# Binance C++ API

#### Installation
    git clone https://github.com/tensaix2j/binacpp    

#### Dependencies
	
	jsoncpp-1.8.3
	libcurl-7.56.0
	libwebsockets-2.4.0



Depended shared libraries and their headers are included in the repository's lib directory 

use -I<include path> to include header paths for compiler to look for headers 

and -L<lib path> and -l<libname> for linker to link against shared libraries.

	libcurl_dir=../lib/libcurl-7.56.0
	libcurl_include=${libcurl_dir}/include
	libcurl_lib=${libcurl_dir}/lib
	
	jsoncpp_dir=../lib/jsoncpp-1.8.3
	jsoncpp_include=${jsoncpp_dir}/include
	jsoncpp_src=${jsoncpp_dir}/src
	
	libwebsockets_dir=../lib/libwebsockets-2.4.0
	libwebsockets_include=${libwebsockets_dir}/include
	libwebsockets_lib=${libwebsockets_dir}/lib
	
	libbinacpp_dir=../lib/libbinacpp
	libbinacpp_include=${libbinacpp_dir}/include
	libbinacpp_lib=${libbinacpp_dir}/lib



.
Then compile like this:


	g++ -I$(libcurl_include) -I$(jsoncpp_include) -I$(libwebsockets_include) -I$(libbinacpp_include) \
	example.cpp \
	-L$(libcurl_lib) \
	-L$(libwebsockets_lib) \
	-L$(libbinacpp_lib) \
	-lcurl -lcrypto -lwebsockets -lbinacpp -o example





And export LD\_LIBRARY\_PATH and run like this:

	libcurl_dir=../lib/libcurl-7.56.0
	libcurl_lib=${libcurl_dir}/lib

	libwebsockets_dir=../lib/libwebsockets-2.4.0
	libwebsockets_lib=${libwebsockets_dir}/lib

	libbinacpp_dir=../lib/libbinacpp
	libbinacpp_lib=${libbinacpp_dir}/lib

	export SSL_CERT_FILE=`pwd`/cacert.pem
	export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$libcurl_lib:$libwebsockets_lib:$libbinacpp_lib

	./example 





You can refer to the following Makefile to get a better picture...

	https://github.com/tensaix2j/binacpp/blob/master/example/Makefile


#### To Build Example
	
	cd example
	make example

---
## Coding with libBinaCPP

#### Headers to include

	#include "binacpp.h"	
	#include "binacpp_websocket.h"
	#include <json/json.h>


#### Init
	string api_key 		= API_KEY;
	string secret_key = SECRET_KEY;
	BinaCPP::init( api_key , secret_key );

---
#### Example : Get Server Time.
	
	Json::Value result;
	BinaCPP::get_serverTime( result ) ;

#### Example : Get all Prices

	Json::Value result;
	BinaCPP::get_allPrices( result );

#### Example: Get price of single pair. Eg: BNBETH

	double bnbeth_price = BinaCPP::get_price( "BNBETH");

#### Example: Get Account 
	
	Json::Value result;
	long recvWindow = 10000;	
	BinaCPP::get_account( recvWindow , result );

#### Example : Get all bid/ask prices
	
	Json::Value result;
	BinaCPP::get_allBookTickers( result );

#### Example: Get bid/ask for single pair
	
	Json::Value result;
	BinaCPP::get_bookTicker("bnbeth", result );
	
#### Example: Get Depth of single pair
	
	Json::Value result;
	BinaCPP::get_depth( "ETHBTC", 5, result ) ;
	

#### Example: Placing a LIMIT order
	
	long recvWindow = 10000;	
	Json::Value result;
	BinaCPP::send_order( "BNBETH", "BUY", "LIMIT", "GTC", 20 , 0.00380000, "",0,0, recvWindow, result );

#### Example: Placing a MARKET order

	long recvWindow = 10000;
	Json::Value result;
	BinaCPP::send_order( "BNBETH", "BUY", "MARKET", "GTC", 20 , 0,   "",0,0, recvWindow, result );

#### Example: Placing an ICEBERG order
	
	long recvWindow = 10000;
	Json::Value result;
	BinaCPP::send_order( "BNBETH", "BUY", "MARKET", "GTC", 1 , 0,   "",0,20, recvWindow , result );

#### Example: Check an order's status

	long recvWindow = 10000;
	Json::Value result;
	BinaCPP::get_order( "BNBETH", 12345678, "", recvWindow, result );

#### Example: Cancel an order

	long recvWindow = 10000;
	Json::Value result;
	BinaCPP::cancel_order("BNBETH", 12345678, "","", recvWindow, result);

#### Example: Getting list of open orders for specific pair
	
	long recvWindow = 10000;
	Json::Value result;
	BinaCPP::get_openOrders( "BNBETH", recvWindow, result ) ;

#### Example: Get all account orders; active, canceled, or filled.
	
	long recvWindow = 10000;
	Json::Value result;
	BinaCPP::get_allOrders( "BNBETH", 0,0, recvWindow, result ) 

#### Example : Get all trades history
	
	long recvWindow = 10000;
	Json::Value result;
	BinaCPP::get_myTrades( "BNBETH", 0,0, recvWindow , result );

#### Example: Getting 24hr ticker price change statistics for a symbol
	
	Json::Value result;
	BinaCPP::get_24hr( "ETHBTC", result ) ;

#### Example: Get Kline/candlestick data for a symbol
	
	Json::Value result;
	BinaCPP::get_klines( "ETHBTC", "1h", 10 , 0, 0, result );

---

### Websocket Endpoints ###


#### Example: Maintain Market Depth Cache Locally via Web Socket
	
	
[example_depthCache.cpp](https://github.com/tensaix2j/binacpp/blob/master/example/example_depthCache.cpp)

#### Example: KLine/Candlestick Cache and update via Web Socket
	

[example_klines.cpp](https://github.com/tensaix2j/binacpp/blob/master/example/example_klines.cpp)

#### Example: Aggregated Trades and update via Web Socket

[example_aggTrades.cpp](https://github.com/tensaix2j/binacpp/blob/master/example/example_aggTrades.cpp)


#### Example: User stream, Order Execution Status and Balance Update via Web Socket

[example_userStream.cpp](https://github.com/tensaix2j/binacpp/blob/master/example/example_userStream.cpp)


#### Example: To subscribe multiple streams at the same time, do something like this

	BinaCPP_websocket::init();
 	
 	BinaCPP_websocket::connect_endpoint( ws_aggTrade_OnData ,"/ws/bnbbtc@aggTrade" ); 
	BinaCPP_websocket::connect_endpoint( ws_userStream_OnData , ws_path.c_str() ); 
	BinaCPP_websocket::connect_endpoint( ws_klines_onData ,"/ws/bnbbtc@kline_1m" ); 
	BinaCPP_websocket::connect_endpoint( ws_depth_onData ,"/ws/bnbbtc@depth" ); 
 		
	BinaCPP_websocket::enter_event_loop(); 

[example.cpp](https://github.com/tensaix2j/binacpp/blob/master/example/example.cpp)

	


