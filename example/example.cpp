
#include <map>
#include <vector>
#include <string>


#include "binacpp.h"
#include "binacpp_websocket.h"
#include <json/json.h>

#define API_KEY 		"api key"
#define SECRET_KEY		"user key"


// Some code to make terminal to have colors
#define KGRN "\033[0;32;32m"
#define KCYN "\033[0;36m"
#define KRED "\033[0;32;31m"
#define KYEL "\033[1;33m"
#define KBLU "\033[0;32;34m"
#define KCYN_L "\033[1;36m"
#define KBRN "\033[0;33m"
#define RESET "\033[0m"


using namespace std;

map < string, map <double,double> >  depthCache;
map < long,   map <string,double> >  klinesCache;
map < long,   map <string,double> >  aggTradeCache;
map < long,   map <string,double> >  userTradeCache;
map < string, map <string,double> >  userBalance;


int lastUpdateId;





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





//------------------
void print_klinesCache() {

	map < long, map<string,double> >::iterator it_i;

	cout << "==================================" << endl;
	
	for ( it_i = klinesCache.begin() ; it_i != klinesCache.end() ; it_i++ ) {

		long start_of_candle 		= (*it_i).first;
		map <string,double> candle_obj 	= (*it_i).second;

		cout << "s:" << start_of_candle << ",";
		cout << "o:" << candle_obj["o"] << ",";
		cout << "h:" << candle_obj["h"] << ",";
		cout << "l:" << candle_obj["l"] << ",";
		cout << "c:" << candle_obj["c"] << ",";
		cout << "v:" << candle_obj["v"] ;
		cout << " " << endl;

	}
}


//---------------
void print_aggTradeCache() {

	map < long, map<string,double> >::iterator it_i;

	cout << "==================================" << endl;
	
	for ( it_i = aggTradeCache.begin() ; it_i != aggTradeCache.end() ; it_i++ ) {

		long timestamp 			= (*it_i).first;
		map <string,double> aggtrade_obj = (*it_i).second;

		cout << "T:" << timestamp << ", ";
		printf("p: %.08f, ", aggtrade_obj["p"] );
		printf("q: %.08f " , aggtrade_obj["q"] );
		cout << " " << endl;

	}
}





//---------------
void print_userBalance() {

	map < string, map<string,double> >::iterator it_i;

	cout << "==================================" << endl;
	
	for ( it_i = userBalance.begin() ; it_i != userBalance.end() ; it_i++ ) {

		string symbol 			= (*it_i).first;
		map <string,double> balance 	= (*it_i).second;

		cout << "Symbol :" << symbol << ", ";
		printf("Free   : %.08f, ", balance["f"] );
		printf("Locked : %.08f " , balance["l"] );
		cout << " " << endl;

	}

}








//-------------
int ws_depth_onData( Json::Value &json_result ) {
	
	int i;

	int new_updateId  = json_result["u"].asInt();
	
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






//-------------
int ws_klines_onData( Json::Value &json_result ) {
	
	long start_of_candle = json_result["k"]["t"].asInt64();
	klinesCache[start_of_candle]["o"] = atof( json_result["k"]["o"].asString().c_str() );
	klinesCache[start_of_candle]["h"] = atof( json_result["k"]["h"].asString().c_str() );
	klinesCache[start_of_candle]["l"] = atof( json_result["k"]["l"].asString().c_str() );
	klinesCache[start_of_candle]["c"] = atof( json_result["k"]["c"].asString().c_str() );
	klinesCache[start_of_candle]["v"] = atof( json_result["k"]["v"].asString().c_str() );
	
	print_klinesCache();	
}







//-----------
int ws_aggTrade_OnData( Json::Value &json_result ) {


	long timestamp = json_result["T"].asInt64();
	aggTradeCache[timestamp]["p"] = atof( json_result["p"].asString().c_str() );
	aggTradeCache[timestamp]["q"] = atof( json_result["q"].asString().c_str() );
		
	print_aggTradeCache();
}



//---------------
int ws_userStream_OnData( Json::Value &json_result ) {

	int i;
	string action = json_result["e"].asString();
	if ( action  == "executionReport" ) {

		string executionType = json_result["x"].asString();
		string orderStatus   = json_result["X"].asString();
		string reason        = json_result["r"].asString();
		string symbol 	     = json_result["s"].asString(); 	
		string side 	     = json_result["S"].asString();	
		string orderType     = json_result["o"].asString();	
		string orderId 	     = json_result["i"].asString();	
		string price 	     = json_result["p"].asString();
		string qty 	     = json_result["q"].asString();

		if ( executionType  == "NEW" ) {
			if ( orderStatus == "REJECTED" ) {
				printf(KRED"Order Failed! Reason: %s\n"RESET, reason.c_str() );
			}
			printf(KGRN"\n\n%s %s %s %s(%s) %s %s\n\n"RESET, symbol.c_str() , side.c_str() , orderType.c_str() , orderId.c_str() , orderStatus.c_str(), price.c_str(), qty.c_str() );
			return 0;
		}
		printf(KBLU"\n\n%s %s %s %s %s\n\n"RESET, symbol.c_str() , side.c_str() , executionType.c_str() , orderType.c_str() , orderId.c_str() );


	} else if ( action == "outboundAccountInfo" ) {

		// Update user balance
		for ( i = 0 ; i < json_result["B"].size() ; i++ ) {
			
			string symbol = json_result["B"][i]["a"].asString();
			userBalance[symbol]["f"] = atof( json_result["B"][i]["f"].asString().c_str() );
			userBalance[symbol]["l"] = atof( json_result["B"][i]["f"].asString().c_str() );
		}
		print_userBalance();

	}

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
	string secret_key 	= SECRET_KEY;
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

	
	 




		
	// Market Depth 
	int i;
	string symbol = "BNBBTC";
	BinaCPP::get_depth( symbol.c_str(), 20, result ) ;

	// Initialize the lastUpdateId
	lastUpdateId = result["lastUpdateId"].asInt();
 		
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
	print_depthCache();
 	



	
 	

 	
 	// Klines/CandleStick
 	BinaCPP::get_klines( "ETHBTC", "1h", 10 , 0, 0, result );
 	for ( int i = 0 ; i < result.size() ; i++ ) {
 		long start_of_candle = result[i][0].asInt64();
 		klinesCache[start_of_candle]["o"] = atof( result[i][1].asString().c_str() );
 		klinesCache[start_of_candle]["h"] = atof( result[i][2].asString().c_str() );
 		klinesCache[start_of_candle]["l"] = atof( result[i][3].asString().c_str() );
 		klinesCache[start_of_candle]["c"] = atof( result[i][4].asString().c_str() );
 		klinesCache[start_of_candle]["v"] = atof( result[i][5].asString().c_str() );
 	}
 	print_klinesCache();
 	

 	


	//  AggTrades 
	BinaCPP::get_aggTrades( "BNBBTC", 0, 0, 0, 10, result ); 
	for ( int i = 0 ; i < result.size() ; i++ ) {
		long timestamp = result[i]["T"].asInt64();
 		aggTradeCache[timestamp]["p"] =  atof( result[i]["p"].asString().c_str() );
 		aggTradeCache[timestamp]["q"] =  atof( result[i]["q"].asString().c_str() );
 	}
	print_aggTradeCache();

	
	


	// User Balance
	BinaCPP::get_account( recvWindow , result );
	for ( int i  = 0 ; i < result["balances"].size() ; i++ ) {
		string symbol = result["balances"][i]["asset"].asString();
		userBalance[symbol]["f"] = atof( result["balances"][i]["free"].asString().c_str() );
		userBalance[symbol]["l"] = atof( result["balances"][i]["locked"].asString().c_str() );
	}
	print_userBalance();






	// User data stream	
	BinaCPP::start_userDataStream(result );
	
	cout << result << endl;
	
	string ws_path = string("/ws/");
	ws_path.append( result["listenKey"].asString() );


	
	
	BinaCPP_websocket::init();
 	
 	BinaCPP_websocket::connect_endpoint( ws_aggTrade_OnData ,"/ws/bnbbtc@aggTrade" ); 
	BinaCPP_websocket::connect_endpoint( ws_userStream_OnData , ws_path.c_str() ); 
	BinaCPP_websocket::connect_endpoint( ws_klines_onData ,"/ws/bnbbtc@kline_1m" ); 
	BinaCPP_websocket::connect_endpoint( ws_depth_onData ,"/ws/bnbbtc@depth" ); 
 		
	BinaCPP_websocket::enter_event_loop(); 
	
	

	return 0;
}