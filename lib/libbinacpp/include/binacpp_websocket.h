


#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <exception>

#include <json/json.h>
#include <libwebsockets.h>


#define BINANCE_WS_HOST "stream.binance.com"
#define BINANCE_WS_PORT 9443


using namespace std;

class BinaCPP_websocket {


	static struct lws 			*ws_handle ;
	static struct lws_protocols protocols[]; 
	static int (*user_cb)( Json::Value &json_result );

	public:
		static int  event_cb( struct lws *wsi, enum lws_callback_reasons reason, void *user, void *in, size_t len );
		static void init(
			int (*user_cb)( Json::Value &json_result ),
			const char* path
		);

};
