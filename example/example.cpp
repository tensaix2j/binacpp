
#include <map>
#include <vector>
#include <string>


#include "binacpp.h"
#include "binacpp_websocket.h"
#include <json/json.h>

#define API_KEY 		"api key goes here"
#define SECRET_KEY		"your secret key goes here"


using namespace std;

map < string, map <double,double> >  depthCache;



//-----------------------------
int ws_onData( Json::Value &json_result) {

	cout << json_result << endl;
}



//------------------------------
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



//-------------
int ws_aggTrade_onData( Json::Value &json_result ) {
	/*
	{
		"e": "aggTrade",		// event type
		"E": 1499405254326,		// event time
		"s": "ETHBTC",			// symbol
		"a": 70232,				// aggregated tradeid
		"p": "0.10281118",		// price
		"q": "8.15632997",		// quantity
		"f": 77489,				// first breakdown trade id
		"l": 77489,				// last breakdown trade id
		"T": 1499405254324,		// trade time
		"m": false,				// whehter buyer is a maker
		"M": true				// can be ignore
	}
	*/
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








//---------------------------
/*
	Examples of how to use BinaCPP Binance API library
	Simply uncomment out the code and compile with : 
	
	make example

	and run with

	./example.run.sh
*/

//--------------------------

int main() {


	string api_key = API_KEY;
	string secret_key = SECRET_KEY;
	BinaCPP::init( api_key , secret_key );


	/*
		The Json::value object each element can be access like hash map <>, 
		or vector <> if it is Json::array
	*/
	Json::Value result;
	long recvWindow = 10000;	

	
	//------------------------------------
	// Example : Get Server Time.
	BinaCPP::get_serverTime( result ) ;
	cout << result << endl;
	//*/

	/*-------------------------------------------------------------
	// Example : Get all Prices
	   BinaCPP::get_allPrices( result );
	  cout << result << endl;
	*/


	/*-------------------------------------------------------------
	//Example: Get price of single pair. Eg: BNBETH
	double bnbeth_price = BinaCPP::get_price( "BNBETH");
	cout << bnbeth_price << endl;
	//*/


	
	// -------------------------------------------------------------
	// Example: Get Account 
	BinaCPP::get_account( recvWindow , result );
	cout << result << endl;
	//*/



	/*-------------------------------------------------------------
	// Example : Get all bid/ask prices
	BinaCPP::get_allBookTickers( result );
	cout << result << endl;
	*/


	/*-------------------------------------------------------------
	// Example: Get bid/ask for single pair
	/*
	BinaCPP::get_bookTicker("bnbeth", result );
	cout << result << endl;
	*/


	/*-------------------------------------------------------------		
	// Example: Get Depth of single pair
	BinaCPP::get_depth( "ETHBTC", 5, result ) ;
	cout << result << endl;
	*/


	
	//-------------------------------------------------------------
	// Example: Placing a LIMIT order
	//BinaCPP::send_order( "BNBETH", "BUY", "LIMIT", "GTC", 20 , 0.00380000, "",0,0, recvWindow, result );
	//cout << result << endl;
	//*/


	/*-------------------------------------------------------------
	// Example: Placing a MARKET order
	BinaCPP::send_order( "BNBETH", "BUY", "MARKET", "GTC", 20 , 0,   "",0,0, recvWindow, result );
	cout << result << endl;
	*/

	/*-------------------------------------------------------------
	// Example: Placing an ICEBERG order
	//BinaCPP::send_order( "BNBETH", "BUY", "MARKET", "GTC", 1 , 0,   "",0,20, recvWindow , result );
	//cout << result << endl;


	/*-------------------------------------------------------------
	// Example: Check an order's status
	BinaCPP::get_order( "BNBETH", 12345678, "", recvWindow, result );
	cout << result << endl;	 
	*/

	/*-------------------------------------------------------------	
	// Example: Cancel an order
	BinaCPP::cancel_order("BNBETH", 12345678, "","", recvWindow, result);
	cout << result << endl;	 
	*/



	/*-------------------------------------------------------------
	// Example: Getting list of open orders for specific pair
	/*
	BinaCPP::get_openOrders( "BNBETH", recvWindow, result ) ;
	cout << result << endl;
	*/


	/*-------------------------------------------------------------
	// Example: Get all account orders; active, canceled, or filled.
	BinaCPP::get_allOrders( "BNBETH", 0,0, recvWindow, result ) 
	cout << result << endl;
	*/


	/*-------------------------------------------------------------
	// Example : Get all trades history
	/*
	BinaCPP::get_myTrades( "BNBETH", 0,0, recvWindow , result );
	cout << result << endl;	 
	*/

		
	/*-------------------------------------------------------------
	/*
	// Example: Getting 24hr ticker price change statistics for a symbol
	   BinaCPP::get_24hr( "ETHBTC", result ) ;
	   cout << result << endl;
	*/   

	
	/*-------------------------------------------------------------   
	/*
	// Example: Get Kline/candlestick data for a symbol
	  BinaCPP::get_klines( "ETHBTC", "1h", 10 , 0, 0, result );
	  cout << result << endl;
	*/


	/*-------------------------------------------------------------  
	/* Websockets Endpoints */
	
	/*
	// Example: Get Candlestick Updates via WebSocket
	BinaCPP_websocket::init( ws_onData ,"/ws/ethbtc@kline_1h" ); 
	*/

	/*-------------------------------------------------------------
	/*
	// Example: Get Market Depth via WebSocket
	BinaCPP_websocket::init( ws_onData ,"/ws/ethbtc@depth" ); 
	*/


	/*-------------------------------------------------------------
	/*
	// Example: Get Trade Updates via WebSocket
	BinaCPP::start_userDataStream( result );
	string path("/ws/");
	path.append( result["listenkey"].asString() );
	BinaCPP_websocket::init( ws_onData ,path.c_str() ); 
	
	*/	



	/*
	// /*-------------------------------------------------------------	
	// Example: Maintain Market Depth Cache Locally via WebSocket
	BinaCPP_websocket::init( ws_aggTrade_onData ,"/ws/ethbtc@aggTrade" ); 
	*/			
	

	return 0;
}