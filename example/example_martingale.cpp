

#include <string>
#include "binacpp.h"
#include "binacpp_websocket.h"


#include <json/json.h>

#define API_KEY 		"myapikey"
#define SECRET_KEY		"mysecretkey"


//-----------------------------
int onTick( Json::Value &json_result) {

	cout << "<onTick>" << endl;
	cout << json_result << endl;

}

//-------------------------
int main() {

	string api_key = API_KEY;
	string secret_key = SECRET_KEY;

	BinaCPP::init( api_key, secret_key ) ;
	BinaCPP_websocket::init( onTick ,"/ws/ethbtc@kline_1m" ); 

	return 0;

}


