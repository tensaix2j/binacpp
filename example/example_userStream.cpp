
#include <map>
#include <vector>
#include <string>


#include "binacpp.h"
#include "binacpp_websocket.h"
#include <json/json.h>



using namespace std;


#define API_KEY 		"api key"
#define SECRET_KEY		"secret_key"


// Some code to make terminal to have colors
#define KGRN "\033[0;32;32m"
#define KCYN "\033[0;36m"
#define KRED "\033[0;32;31m"
#define KYEL "\033[1;33m"
#define KBLU "\033[0;32;34m"
#define KCYN_L "\033[1;36m"
#define KBRN "\033[0;33m"
#define RESET "\033[0m"

map < string, map <string,double> >  userBalance;


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
	To compile, type
	make example_userStream

*/

//--------------------------

int main() {

	Json::Value result;
	long recvWindow = 10000;	

	string api_key 		= API_KEY;
	string secret_key 	= SECRET_KEY;
	BinaCPP::init( api_key , secret_key );

		
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
 	BinaCPP_websocket::connect_endpoint( ws_userStream_OnData , ws_path.c_str() ); 
	BinaCPP_websocket::enter_event_loop(); 
	
	
}