
#include <map>
#include <vector>
#include <string>


#include "binacpp.h"
#include "binacpp_websocket.h"
#include <json/json.h>



using namespace std;
map < long,   map <string,double> >  klinesCache;


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






//---------------------------
/*
	To compile, type
	make example_klines
*/

//--------------------------

int main() {

	Json::Value result;
	long recvWindow = 10000;	
	
	// Klines/CandleStick
 	BinaCPP::get_klines( "BNBBTC", "1h", 10 , 0, 0, result );
 	for ( int i = 0 ; i < result.size() ; i++ ) {
 		long start_of_candle = result[i][0].asInt64();
 		klinesCache[start_of_candle]["o"] = atof( result[i][1].asString().c_str() );
 		klinesCache[start_of_candle]["h"] = atof( result[i][2].asString().c_str() );
 		klinesCache[start_of_candle]["l"] = atof( result[i][3].asString().c_str() );
 		klinesCache[start_of_candle]["c"] = atof( result[i][4].asString().c_str() );
 		klinesCache[start_of_candle]["v"] = atof( result[i][5].asString().c_str() );
 	}
 	print_klinesCache();
 		
 	// Klines/Candlestick update via websocket
 	BinaCPP_websocket::init();
 	BinaCPP_websocket::connect_endpoint( ws_klines_onData ,"/ws/bnbbtc@kline_1m" ); 
	BinaCPP_websocket::enter_event_loop(); 
	
	return 0;
}