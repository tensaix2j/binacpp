
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

### Websockets Endpoints ###

#### Example: Get Candlestick Updates via WebSocket

	int ws_onData( Json::Value &json_result) {
		cout << json_result << endl;
	}
	int main() {
		BinaCPP_websocket::init( ws_onData ,"/ws/ethbtc@kline_1h" ); 
	}

#### Example: Get Market Depth via WebSocket

	
	int ws_onData( Json::Value &json_result) {
		cout << json_result << endl;
	}

	int main() {
		BinaCPP_websocket::init( ws_onData ,"/ws/ethbtc@depth" ); 
	}

#### Example: Get Trade Updates via WebSocket

	

	int ws_onData( Json::Value &json_result) {
		cout << json_result << endl;
	}

	int main() {
	
		string api_key 		= API_KEY;
		string secret_key 	= SECRET_KEY;
		BinaCPP::init( api_key , secret_key );
		Json::Value result;

		BinaCPP::start_userDataStream( result );
		string path("/ws/");
		path.append( result["listenkey"].asString() );
		BinaCPP_websocket::init( ws_onData ,path.c_str() ); 
	}

#### Example: Maintain Market Depth Cache Locally via WebSocket

	map < string, map <double,double> >  depthCache;

.

	void print_depthCache() {
	
		map < string, map <double,double> >::iterator it_i;
		for ( it_i = depthCache.begin() ; it_i != depthCache.end() ; it_i++ ) {
			string symbol = (*it_i).first ;
			cout << "Symbol " << symbol << endl ;
			cout << "Price             Qty" << endl ;		
			map <double,double>::iterator it_j;
	
			for ( it_j = depthCache[symbol].begin() ; it_j != depthCache[symbol].end() ; it_j++ ) {
				double price = (*it_j).first;
				double qty   = (*it_j).second;
				printf("%.08f          %.08f\n", price, qty );
			}
		}
	}

.	
	
	int ws_aggTrade_onData( Json::Value &json_result ) {
		
		cout << json_result << endl;
	
		string symbol 		= json_result["s"].asString();
		double price  		= atof( json_result["p"].asString().c_str() );
		double qty    		= atof( json_result["q"].asString().c_str() );
		bool ismaker		= json_result["m"].asBool();
	
		if ( ismaker ) {
			if ( depthCache.find( symbol ) != depthCache.end() && depthCache[symbol].find( price ) != depthCache[symbol].end()  ) {
				depthCache[symbol][price] += qty;
			} else {
				depthCache[symbol][price] = qty;
			}
		} else {
			if ( depthCache.find( symbol ) != depthCache.end() && depthCache[symbol].find( price ) != depthCache[symbol].end()  ) {
				depthCache[symbol][price] -= qty;
			}
		}
		print_depthCache();
	}
	
.

	int main() {
		BinaCPP_websocket::init( ws_aggTrade_onData ,"/ws/ethbtc@aggTrade" ); 
	}
