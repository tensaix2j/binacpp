

#include <string>
#include "binacpp.h"
#include "binacpp_websocket.h"


#include <json/json.h>

#define API_KEY 		"myapikey"
#define SECRET_KEY		"mysecretkey"


//-----------------------------
int ws_klines_onData( Json::Value &json_result) {

	cout << json_result << endl;

}

//-------------------------
int main() {

	string api_key = API_KEY;
	string secret_key = SECRET_KEY;

	BinaCPP::init( api_key, secret_key ) ;
	
	BinaCPP_websocket::init();
 	BinaCPP_websocket::connect_endpoint( ws_klines_onData ,"/ws/bnbbtc@kline_1m" ); 
	BinaCPP_websocket::enter_event_loop(); 
	
	return 0;

}


