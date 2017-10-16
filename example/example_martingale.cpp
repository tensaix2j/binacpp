

#include <string>
#include "binacpp.h"
#include "binacpp_websocket.h"
#include <json/json.h>

//-------------------------------------------------------
/*
	This is an example to demonstrate how to do Martingale Betting Strategy using BinaCPP.
	DISCLAIMER: USE IT AT YOUR OWN RISK.

*/
//-------------------------------------------------------

#define API_KEY 		"myapikey"
#define SECRET_KEY		"mysecretkey"
#define SYMBOL  		"bnbeth"

double initial_betsize = 0.01;
double current_betsize = 0.01;
double max_betsize     = 0.16;
vector <int> ordered_id;

//-----------------------------
// OnTick gets called when websocket endpoint /ws/<symbol>@klines_<interval> has incoming data. 
//  json_result will be filled with data like this: 
/*
	"e": "kline",				// event type
	"E": 1499404907056,			// event time
	"s": "ETHBTC",				// symbol
	"k": {
		"t": 1499404860000, 		// start time of this bar
		"T": 1499404919999, 		// end time of this bar
		"s": "ETHBTC",			// symbol
		"i": "1m",			// interval
		"f": 77462,			// first trade id
		"L": 77465,			// last trade id
		"o": "0.10278577",		// open
		"c": "0.10278645",		// close
		"h": "0.10278712",		// high
		"l": "0.10278518",		// low
		"v": "17.47929838",		// volume
		"n": 4,				// number of trades
		"x": false,			// whether this bar is final
		"q": "1.79662878",		// quote volume
		"V": "2.34879839",		// volume of active buy
		"Q": "0.24142166",		// quote volume of active buy
		"B": "13279784.01349473"	// can be ignored
		}
	}
*/
int onTick( Json::Value &json_result) {

	if ( OrdersTotal() == 0 ) {
          
        	if ( OrdersHistoryTotal() > 0 ) {
        		OrderSelect( OrdersHistoryTotal() - 1, SELECT_BY_POS, MODE_HISTORY );
        		if ( OrderProfit() < 0 ) {
               			// Lose last round so, double it
               			if ( betsize * 2 <= max_betsize ) {
                  			betsize *= 2;
               			}
            		} else {
               			// Won last round so, back to initial
               			betsize = initial_betsize;
            		}
          	}
          
          	if ( MathRand() % 2 == 0 ) {  
            		OrderSend( Symbol(), OP_BUY, betsize, Ask, 3, Ask - 0.0030, Ask + 0.0030 );
          	} else {
            		OrderSend( Symbol(), OP_SELL, betsize, Bid, 3, Bid + 0.0030, Bid - 0.0030 );
          	}
      	} 

}






//-------------------------
int main() {

	string api_key = API_KEY;
	string secret_key = SECRET_KEY;

	BinaCPP::init( api_key, secret_key ) ;
	BinaCPP_websocket::init( onTick ,"/ws/ethbtc@kline_1m" ); 

	return 0;

}




