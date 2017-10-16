

#include "binacpp.h"
#include <json/json.h>

#define API_KEY 		"myapikey"
#define SECRET_KEY		"mysecretkey"


int main() {

	/*
		The Json::value object each element can be access like hash map <>, 
		or vector <> if it is Json::array
	*/
	
	// Example of get all Prices
	Json::Value result;
	BinaCPP::get_allPrices( result );
	cout << result << endl;


	// Example of get all book tickers
	BinaCPP::get_allBookTickers( result );
	cout << result << endl;


	// Example of get depth
	BinaCPP::get_depth( "ETHBTC", 5, result ) ;
	cout << result << endl;


	// Example of get_account
	string api_key = API_KEY;
	string secret_key = SECRET_KEY;
	BinaCPP::init( api_key , secret_key );
	BinaCPP::get_account( result );
	cout << result;





	return 0;
}