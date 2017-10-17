
#include <map>
#include <vector>
#include <string>


#include "binacpp.h"
#include "binacpp_websocket.h"
#include <json/json.h>



using namespace std;
map < long,   map <string,double> >  aggTradeCache;


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



//-----------
int ws_aggTrade_OnData( Json::Value &json_result ) {


	long timestamp = json_result["T"].asInt64();
	aggTradeCache[timestamp]["p"] = atof( json_result["p"].asString().c_str() );
	aggTradeCache[timestamp]["q"] = atof( json_result["q"].asString().c_str() );
		
	print_aggTradeCache();
}


//---------------------------
/*
	To compile, type
	make example_aggTrades
*/

//--------------------------

int main() {

	Json::Value result;
	long recvWindow = 10000;	
	
	//  AggTrades 
	BinaCPP::get_aggTrades( "BNBBTC", 0, 0, 0, 10, result ); 
	for ( int i = 0 ; i < result.size() ; i++ ) {
		long timestamp = result[i]["T"].asInt64();
 		aggTradeCache[timestamp]["p"] =  atof( result[i]["p"].asString().c_str() );
 		aggTradeCache[timestamp]["q"] =  atof( result[i]["q"].asString().c_str() );
 	}
	print_aggTradeCache();


	BinaCPP_websocket::init();
 	BinaCPP_websocket::connect_endpoint( ws_aggTrade_OnData ,"/ws/bnbbtc@aggTrade" ); 
	BinaCPP_websocket::enter_event_loop(); 
	
	return 0;
}