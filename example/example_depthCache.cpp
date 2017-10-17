
#include <map>
#include <vector>
#include <string>


#include "binacpp.h"
#include "binacpp_websocket.h"
#include <json/json.h>



using namespace std;

map < string, map <double,double> >  depthCache;
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


//---------------------------
/*
	To compile, type
	make example_depthCache

*/

//--------------------------

int main() {

	Json::Value result;
	long recvWindow = 10000;	

		
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
 	

	BinaCPP_websocket::init();
 	BinaCPP_websocket::connect_endpoint( ws_depth_onData ,"/ws/bnbbtc@depth" ); 
 	BinaCPP_websocket::enter_event_loop(); 
	
}