
#include <map>
#include <vector>
#include <string>


#include "binacpp.h"
#include "binacpp_websocket.h"
#include <json/json.h>

#define API_KEY 		"api key"
#define SECRET_KEY		"secret key"




using namespace std;

map < string, map <double,double> >  depthCache;
int lastUpdateId = 0;



//-----------------------------
int ws_onData( Json::Value &json_result) {

	cout << json_result << endl;
}



//------------------------------
void print_depthCache() {

	map < string, map <double,double> >::iterator it_i;

	for ( it_i = depthCache.begin() ; it_i != depthCache.end() ; it_i++ ) {
			
		string bid_or_ask = (*it_i).first ;
		cout << bid_or_ask << endl ;
		cout << "Price             Qty" << endl ;		

		map <double,double>::reverse_iterator it_j;

		for ( it_j = depthCache[bid_or_ask].rbegin() ; it_j != depthCache[bid_or_ask].rend() ; it_j++ ) {

			double price = (*it_j).first;
			double qty   = (*it_j).second;
			printf("%.08f          %.08f\n", price, qty );
		}
	}
}



//-------------
int ws_depth_onData( Json::Value &json_result ) {
	
	/*
	{
			"e": "depthUpdate",						// event type
			"E": 1499404630606, 					// event time
			"s": "ETHBTC", 							// symbol
			"u": 7913455, 							// updateId to sync up with updateid in /api/v1/depth
			"b": [									// bid depth delta
				[
					"0.10376590", 					// price (need to upate the quantity on this price)
					"59.15767010", 					// quantity
					[]								// can be ignored
				],
			],
			"a": [									// ask depth delta
				[
					"0.10376586", 					// price (need to upate the quantity on this price)
					"159.15767010", 				// quantity
					[]								// can be ignored
				],
				[
					"0.10383109",
					"345.86845230",
					[]
				],
				[
					"0.10490700",
					"0.00000000", 					//quantitiy=0 means remove this level
					[]
				]
			]
		}
	*/	
	
	int i;

	int new_updateId  	= json_result["u"].asInt();
	if ( new_updateId > lastUpdateId ) {
		for ( i = 0 ; i < json_result["b"].size() ; i++ ) {
			double price = atof( json_result["b"][i][0].asString().c_str());
			double qty 	 = atof( json_result["b"][i][1].asString().c_str());
			if ( qty == 0.0 ) {
				depthCache["bids"].erase(price);
			} else {
				depthCache["bids"][price] = qty;
			}
		}
		for ( i = 0 ; i < json_result["a"].size() ; i++ ) {
			double price = atof( json_result["a"][i][0].asString().c_str());
			double qty 	 = atof( json_result["a"][i][1].asString().c_str());
			if ( qty == 0.0 ) {
				depthCache["asks"].erase(price);
			} else {
				depthCache["asks"][price] = qty;
			}
		}		
		lastUpdateId = new_updateId;
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


	string api_key 		= API_KEY;
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


	/*
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



	// Example: Get Market Depth via WebSocket
	int i;
	string symbol = "BNBBTC";
	BinaCPP::get_depth( symbol.c_str(), 20, result ) ;
	for ( int i = 0 ; i < result["asks"].size(); i++ ) {

		double price = atof( result["asks"][i][0].asString().c_str() );
		double qty   = atof( result["asks"][i][1].asString().c_str() );
		depthCache["asks"][price] = qty;

	}
	for  ( int i = 0 ; i < result["bids"].size() ; i++ ) {

		double price = atof( result["bids"][i][0].asString().c_str() );
		double qty   = atof( result["bids"][i][1].asString().c_str() );
		depthCache["bids"][price] = qty;
	}
 	lastUpdateId = result["lastUpdateId"].asInt();

 	print_depthCache();
 	BinaCPP_websocket::init( ws_depth_onData ,"/ws/bnbbtc@depth" ); 


	

	return 0;
}