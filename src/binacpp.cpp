

/*
	Author: tensaix2j
	Date  : 2017/10/15
	
	C++ library for Binance API.
*/





#include "binacpp.h"
#include "binacpp_logger.h"
#include "binacpp_utils.h"




string BinaCPP::api_key = "";
string BinaCPP::secret_key = "";




//---------------------------------
void 
BinaCPP::init( string &api_key, string &secret_key ) 
{
	BinaCPP::api_key = api_key;
	BinaCPP::secret_key = secret_key;
}







//--------------------
// Get Latest price for all symbols.
void 
BinaCPP::get_allPrices( Json::Value &json_result ) 
{	

	BinaCPP_logger::write_log( "<BinaCPP::get_allPrices>" ) ;

	string url(BINANCE_HOST);  
	url += "/api/v1/ticker/allPrices";

	string str_result;
	curl_api( url, str_result ) ;

	if ( str_result.size() > 0 ) {
		
		try {
			Json::Reader reader;
			json_result.clear();	
			reader.parse( str_result , json_result );
	    		
		} catch ( exception &e ) {
		 	BinaCPP_logger::write_log( "<BinaCPP::get_allPrices> Error ! %s", e.what() ); 
		}   
		BinaCPP_logger::write_log( "<BinaCPP::get_allPrices> Done." ) ;
	
	} else {
		BinaCPP_logger::write_log( "<BinaCPP::get_allPrices> Failed to get anything." ) ;
	}
}




//--------------------
// Get Best price/qty on the order book for all symbols.

void 
BinaCPP::get_allBookTickers(  Json::Value &json_result ) 
{	

	BinaCPP_logger::write_log( "<BinaCPP::get_allBookTickers>" ) ;

	string url(BINANCE_HOST);  
	url += "/api/v1/ticker/allBookTickers";

	string str_result;
	curl_api( url, str_result ) ;

	if ( str_result.size() > 0 ) {
		
		try {
			Json::Reader reader;
			json_result.clear();	
	    		reader.parse( str_result , json_result );
	    		
	    	} catch ( exception &e ) {
		 	BinaCPP_logger::write_log( "<BinaCPP::get_allBookTickers> Error ! %s", e.what() ); 
		}   
		BinaCPP_logger::write_log( "<BinaCPP::get_allBookTickers> Done." ) ;
	
	} else {
		BinaCPP_logger::write_log( "<BinaCPP::get_allBookTickers> Failed to get anything." ) ;
	}
}







//--------------------
// Get Market Depth
void 
BinaCPP::get_depth( const char *symbol, int limit, Json::Value &json_result ) 
{	

	BinaCPP_logger::write_log( "<BinaCPP::get_depth>" ) ;

	string url(BINANCE_HOST);  
	url += "/api/v1/depth?";

	string querystring("symbol=");
	querystring.append( symbol );
	querystring.append("&limit=");
	querystring.append( to_string( limit ) );

	url.append( querystring );
	BinaCPP_logger::write_log( "<BinaCPP::get_depth> url = |%s|" , url.c_str() ) ;
	
	string str_result;
	curl_api( url, str_result ) ;

	if ( str_result.size() > 0 ) {
		
		try {
			Json::Reader reader;
			json_result.clear();	
	    		reader.parse( str_result , json_result );
	    		
		} catch ( exception &e ) {
		 	BinaCPP_logger::write_log( "<BinaCPP::get_depth> Error ! %s", e.what() ); 
		}   
		BinaCPP_logger::write_log( "<BinaCPP::get_depth> Done." ) ;
	
	} else {
		BinaCPP_logger::write_log( "<BinaCPP::get_depth> Failed to get anything." ) ;
	}
}







//--------------------
// Get Aggregated Trades list
/*
Name		Type	Mandatory	Description
symbol		STRING	YES	
fromId		LONG	NO		ID to get aggregate trades from INCLUSIVE.
startTime	LONG	NO		Timestamp in ms to get aggregate trades from INCLUSIVE.
endTime		LONG	NO		Timestamp in ms to get aggregate trades until INCLUSIVE.
limit		INT	NO		Default 500; max 500.
*/

void 
BinaCPP::get_aggTrades( const char *symbol, int fromId, time_t startTime, time_t endTime, int limit, Json::Value &json_result ) 
{	

	BinaCPP_logger::write_log( "<BinaCPP::get_aggTrades>" ) ;

	string url(BINANCE_HOST);  
	url += "/api/v1/aggTrades?";

	string querystring("symbol=");
	querystring.append( symbol );

	
	if ( startTime != 0 && endTime != 0 ) {

		querystring.append("&startTime=");
		querystring.append( to_string( startTime ) );

		querystring.append("&endTime=");
		querystring.append( to_string( endTime ) );
	
	} else {
		querystring.append("&fromId=");
		querystring.append( to_string( fromId ) );

		querystring.append("&limit=");
		querystring.append( to_string( limit ) );
	}

	url.append( querystring );
	BinaCPP_logger::write_log( "<BinaCPP::get_aggTrades> url = |%s|" , url.c_str() ) ;
	
	string str_result;
	curl_api( url, str_result ) ;
	
	if ( str_result.size() > 0 ) {
		
		try {
			Json::Reader reader;
			json_result.clear();	
	    		reader.parse( str_result , json_result );
	    		
		} catch ( exception &e ) {
		 	BinaCPP_logger::write_log( "<BinaCPP::get_aggTrades> Error ! %s", e.what() ); 
		}   
		BinaCPP_logger::write_log( "<BinaCPP::get_aggTrades> Done." ) ;
	
	} else {
		BinaCPP_logger::write_log( "<BinaCPP::get_aggTrades> Failed to get anything." ) ;
	}
}









//--------------------
// Get 24hr ticker price change statistics
/*
Name	Type	Mandatory	Description
symbol	STRING	YES	
*/
void 
BinaCPP::get_24hr( const char *symbol, Json::Value &json_result ) 
{	

	BinaCPP_logger::write_log( "<BinaCPP::get_24hr>" ) ;

	string url(BINANCE_HOST);  
	url += "/api/v1/ticker/24hr?";

	string querystring("symbol=");
	querystring.append( symbol );


	
	url.append( querystring );
	BinaCPP_logger::write_log( "<BinaCPP::get_24hr> url = |%s|" , url.c_str() ) ;
	
	string str_result;
	curl_api( url, str_result ) ;

	if ( str_result.size() > 0 ) {
		
		try {
			Json::Reader reader;
			json_result.clear();	
	    		reader.parse( str_result , json_result );
	    		
		} catch ( exception &e ) {
		 	BinaCPP_logger::write_log( "<BinaCPP::get_24hr> Error ! %s", e.what() ); 
		}   
		BinaCPP_logger::write_log( "<BinaCPP::get_24hr> Done." ) ;
	
	} else {
		BinaCPP_logger::write_log( "<BinaCPP::get_24hr> Failed to get anything." ) ;
	}
}





//-----------------
/*

Get KLines( Candle stick / OHLC )

Name		Type	Mandatory	Description
symbol		STRING	YES	
interval	ENUM	YES	
limit		INT	NO	Default 500; max 500.
startTime	LONG	NO	
endTime		LONG	NO	

*/

void 
BinaCPP::get_klines( const char *symbol, const char *interval, int limit, time_t startTime, time_t endTime,  Json::Value &json_result ) 
{		

	BinaCPP_logger::write_log( "<BinaCPP::get_klines>" ) ;

	string url(BINANCE_HOST);  
	url += "/api/v1/klines?";

	string querystring("symbol=");
	querystring.append( symbol );

	querystring.append( "&interval=" );
	querystring.append( interval );

	if ( startTime != 0 && endTime != 0 ) {

		querystring.append("&startTime=");
		querystring.append( to_string( startTime ) );

		querystring.append("&endTime=");
		querystring.append( to_string( endTime ) );
	
	} else {
		querystring.append("&limit=");
		querystring.append( to_string( limit ) );
	}

	
	url.append( querystring );
	BinaCPP_logger::write_log( "<BinaCPP::get_klines> url = |%s|" , url.c_str() ) ;
	
	string str_result;
	curl_api( url, str_result ) ;

	if ( str_result.size() > 0 ) {
		
		try {
			Json::Reader reader;
	    		json_result.clear();	
			reader.parse( str_result , json_result );
	    		
		} catch ( exception &e ) {
		 	BinaCPP_logger::write_log( "<BinaCPP::get_klines> Error ! %s", e.what() ); 
		}   
		BinaCPP_logger::write_log( "<BinaCPP::get_klines> Done." ) ;
	
	} else {
		BinaCPP_logger::write_log( "<BinaCPP::get_klines> Failed to get anything." ) ;
	}
}














//--------------------
// Get current account information. (SIGNED)
/*
Parameters:
Name		Type	Mandatory	Description
recvWindow	LONG	NO	
timestamp	LONG	YES
*/


void 
BinaCPP::get_account(  Json::Value &json_result ) 
{	

	BinaCPP_logger::write_log( "<BinaCPP::get_account>" ) ;

	if ( api_key.size() == 0 || secret_key.size() == 0 ) {
		BinaCPP_logger::write_log( "<BinaCPP::get_account> API Key and Secret Key has not been set." ) ;
		return ;
	}


	string url(BINANCE_HOST);
	url += "/api/v3/account?";

	string querystring("timestamp=");
	querystring.append( to_string( get_current_ms_epoch() ) );

	string signature =  hmac_sha256( secret_key.c_str() , querystring.c_str() );
	querystring.append( "&signature=");
	querystring.append( signature );

	url.append( querystring );
	vector <string> extra_http_header;
	string header_chunk("X-MBX-APIKEY: ");
	header_chunk.append( api_key );
	extra_http_header.push_back(header_chunk);

	BinaCPP_logger::write_log( "<BinaCPP::get_account> url = |%s|" , url.c_str() ) ;
	
	string action = "GET";
	string post_data = "";
	
	string str_result;
	curl_api_with_header( url, str_result , extra_http_header , post_data , action ) ;


	if ( str_result.size() > 0 ) {
		
		try {
			Json::Reader reader;
			json_result.clear();	
			reader.parse( str_result , json_result );
	    		
	    	} catch ( exception &e ) {
		 	BinaCPP_logger::write_log( "<BinaCPP::get_account> Error ! %s", e.what() ); 
		}   
		BinaCPP_logger::write_log( "<BinaCPP::get_account> Done." ) ;
	
	} else {
		BinaCPP_logger::write_log( "<BinaCPP::get_account> Failed to get anything." ) ;
	}

	BinaCPP_logger::write_log( "<BinaCPP::get_account> Done.\n" ) ;

}








//--------------------
// Get trades for a specific account and symbol. (SIGNED)
/*
Name		Type	Mandatory	Description
symbol		STRING	YES	
limit		INT	NO	Default 500; max 500.
fromId		LONG	NO	TradeId to fetch from. Default gets most recent trades.
recvWindow	LONG	NO	
timestamp	LONG	YES
	
*/


void 
BinaCPP::get_myTrades( const char *symbol, Json::Value &json_result ) 
{	

	BinaCPP_logger::write_log( "<BinaCPP::get_myTrades>" ) ;

	if ( api_key.size() == 0 || secret_key.size() == 0 ) {
		BinaCPP_logger::write_log( "<BinaCPP::get_myTrades> API Key and Secret Key has not been set." ) ;
		return ;
	}


	string url(BINANCE_HOST);
	url += "/api/v3/myTrades?";

	string querystring("symbol=");
	querystring.append( symbol );
	querystring.append("&timestamp=");
	querystring.append( to_string( get_current_ms_epoch() ) );

	string signature =  hmac_sha256( secret_key.c_str() , querystring.c_str() );
	querystring.append( "&signature=");
	querystring.append( signature );

	url.append( querystring );
	vector <string> extra_http_header;
	string header_chunk("X-MBX-APIKEY: ");
	header_chunk.append( api_key );
	extra_http_header.push_back(header_chunk);

	BinaCPP_logger::write_log( "<BinaCPP::get_myTrades> url = |%s|" , url.c_str() ) ;
	
	string action = "GET";
	string post_data = "";

	string str_result;
	curl_api_with_header( url, str_result , extra_http_header , post_data , action ) ;


	if ( str_result.size() > 0 ) {
		
		try {
			Json::Reader reader;
			json_result.clear();	
			reader.parse( str_result , json_result );
	    		
	    	} catch ( exception &e ) {
		 	BinaCPP_logger::write_log( "<BinaCPP::get_myTrades> Error ! %s", e.what() ); 
		}   
		BinaCPP_logger::write_log( "<BinaCPP::get_myTrades> Done." ) ;
	
	} else {
		BinaCPP_logger::write_log( "<BinaCPP::get_myTrades> Failed to get anything." ) ;
	}

	BinaCPP_logger::write_log( "<BinaCPP::get_myTrades> Done.\n" ) ;

}








//--------------------
// All Orders (SIGNED)
/*
Name		Type	Mandatory	Description
symbol		STRING	YES	
orderId		LONG	NO	
limit		INT	NO		Default 500; max 500.
recvWindow	LONG	NO	
timestamp	LONG	YES	
*/

void 
BinaCPP::get_allOrders( const char *symbol, Json::Value &json_result ) 
{	

	BinaCPP_logger::write_log( "<BinaCPP::get_allOrders>" ) ;

	if ( api_key.size() == 0 || secret_key.size() == 0 ) {
		BinaCPP_logger::write_log( "<BinaCPP::get_allOrders> API Key and Secret Key has not been set." ) ;
		return ;
	}


	string url(BINANCE_HOST);
	url += "/api/v3/allOrders?";

	string querystring("symbol=");
	querystring.append( symbol );

	querystring.append("&timestamp=");
	querystring.append( to_string( get_current_ms_epoch() ) );

	string signature =  hmac_sha256( secret_key.c_str(), querystring.c_str() );
	querystring.append( "&signature=");
	querystring.append( signature );

	url.append( querystring );
	vector <string> extra_http_header;
	string header_chunk("X-MBX-APIKEY: ");
	header_chunk.append( api_key );
	extra_http_header.push_back(header_chunk);

	
	string action = "GET";
	string post_data ="";
		
	BinaCPP_logger::write_log( "<BinaCPP::get_allOrders> url = |%s|" , url.c_str() ) ;
	
	string str_result;
	curl_api_with_header( url, str_result , extra_http_header, post_data , action ) ;


	if ( str_result.size() > 0 ) {
		
		try {
			Json::Reader reader;
			json_result.clear();	
			reader.parse( str_result , json_result );
	    		
	    	} catch ( exception &e ) {
		 	BinaCPP_logger::write_log( "<BinaCPP::get_allOrders> Error ! %s", e.what() ); 
		}   
		BinaCPP_logger::write_log( "<BinaCPP::get_allOrders> Done." ) ;
	
	} else {
		BinaCPP_logger::write_log( "<BinaCPP::get_allOrders> Failed to get anything." ) ;
	}
	
	BinaCPP_logger::write_log( "<BinaCPP::get_allOrders> Done.\n" ) ;

}



//------------
/*
send order (SIGNED)

Name			Type		Mandatory	Description
symbol			STRING		YES	
side			ENUM		YES	
type			ENUM		YES	
timeInForce		ENUM		YES	
quantity		DECIMAL		YES	
price			DECIMAL		YES	
newClientOrderId	STRING		NO		A unique id for the order. Automatically generated by default.
stopPrice		DECIMAL		NO		Used with STOP orders
icebergQty		DECIMAL		NO		Used with icebergOrders
recvWindow		LONG		NO	
timestamp		LONG		YES	
*/

void 
BinaCPP::send_order( 
	const char *symbol, 
	const char *side,
	const char *type,
	const char *timeInForce,
	double quantity,
	double price,
	long recvWindow,
	Json::Value &json_result ) 
{	

	BinaCPP_logger::write_log( "<BinaCPP::send_order>" ) ;

	if ( api_key.size() == 0 || secret_key.size() == 0 ) {
		BinaCPP_logger::write_log( "<BinaCPP::send_order> API Key and Secret Key has not been set." ) ;
		return ;
	}

	string url(BINANCE_HOST);
	url += "/api/v3/order?";

	string action = "POST";
	
	string post_data("symbol=");
	post_data.append( symbol );
	
	post_data.append("&side=");
	post_data.append( side );

	post_data.append("&type=");
	post_data.append( type );

	post_data.append("&timeInForce=");
	post_data.append( timeInForce );



	post_data.append("&quantity=");
	post_data.append( to_string( quantity) );

	post_data.append("&price=");
	post_data.append( to_string( price) );

	post_data.append("&recvWindow=");
	post_data.append( to_string( recvWindow) );
	

	post_data.append("&timestamp=");
	post_data.append( to_string( get_current_ms_epoch() ) );

	string signature =  hmac_sha256( secret_key.c_str(), post_data.c_str() );
	post_data.append( "&signature=");
	post_data.append( signature );


	vector <string> extra_http_header;
	string header_chunk("X-MBX-APIKEY: ");
	header_chunk.append( api_key );
	extra_http_header.push_back(header_chunk);

	BinaCPP_logger::write_log( "<BinaCPP::send_order> url = |%s|, post_data = |%s|" , url.c_str(), post_data.c_str() ) ;
	
	string str_result;
	curl_api_with_header( url, str_result , extra_http_header, post_data, action ) ;

	if ( str_result.size() > 0 ) {
		
		try {
			Json::Reader reader;
			json_result.clear();	
			reader.parse( str_result , json_result );
	    		
	    	} catch ( exception &e ) {
		 	BinaCPP_logger::write_log( "<BinaCPP::send_order> Error ! %s", e.what() ); 
		}   
		BinaCPP_logger::write_log( "<BinaCPP::send_order> Done." ) ;
	
	} else {
		BinaCPP_logger::write_log( "<BinaCPP::send_order> Failed to get anything." ) ;
	}
	
	BinaCPP_logger::write_log( "<BinaCPP::send_order> Done.\n" ) ;

}


//------------------
/*
// get order (SIGNED)
Name			Type	Mandatory	Description
symbol			STRING	YES	
orderId			LONG	NO	
origClientOrderId	STRING	NO	
recvWindow		LONG	NO	
timestamp		LONG	YES	
*/

void 
BinaCPP::get_order( 
	const char *symbol, 
	long orderId,
	Json::Value &json_result ) 
{	

	BinaCPP_logger::write_log( "<BinaCPP::get_order>" ) ;

	if ( api_key.size() == 0 || secret_key.size() == 0 ) {
		BinaCPP_logger::write_log( "<BinaCPP::get_order> API Key and Secret Key has not been set." ) ;
		return ;
	}

	string url(BINANCE_HOST);
	url += "/api/v3/order?";

	string querystring("symbol=");
	querystring.append( symbol );
	
	querystring.append("&orderId=");
	querystring.append( to_string( orderId ) );

	querystring.append("&timestamp=");
	querystring.append( to_string( get_current_ms_epoch() ) );

	string signature =  hmac_sha256( secret_key.c_str(), querystring.c_str() );
	querystring.append( "&signature=");
	querystring.append( signature );

	url.append( querystring );
	
	vector <string> extra_http_header;
	string header_chunk("X-MBX-APIKEY: ");
	header_chunk.append( api_key );
	extra_http_header.push_back(header_chunk);

	string action = "GET";
	string post_data = "";
	
	BinaCPP_logger::write_log( "<BinaCPP::get_order> url = |%s|" , url.c_str() ) ;
	
	string str_result;
	curl_api_with_header( url, str_result , extra_http_header, post_data , action ) ;

	if ( str_result.size() > 0 ) {
		
		try {
			Json::Reader reader;
			json_result.clear();	
			reader.parse( str_result , json_result );
	    		
	    	} catch ( exception &e ) {
		 	BinaCPP_logger::write_log( "<BinaCPP::get_order> Error ! %s", e.what() ); 
		}   
		BinaCPP_logger::write_log( "<BinaCPP::get_order> Done." ) ;
	
	} else {
		BinaCPP_logger::write_log( "<BinaCPP::get_order> Failed to get anything." ) ;
	}

	
	BinaCPP_logger::write_log( "<BinaCPP::get_order> Done.\n" ) ;

}









//--------------------
//Start user data stream (API-KEY)

void 
BinaCPP::start_userDataStream( Json::Value &json_result ) 
{	
	BinaCPP_logger::write_log( "<BinaCPP::start_userDataStream>" ) ;

	if ( api_key.size() == 0 ) {
		BinaCPP_logger::write_log( "<BinaCPP::start_userDataStream> API Key has not been set." ) ;
		return ;
	}


	string url(BINANCE_HOST);
	url += "/api/v1/userDataStream";

	vector <string> extra_http_header;
	string header_chunk("X-MBX-APIKEY: ");
	

	header_chunk.append( api_key );
	extra_http_header.push_back(header_chunk);

	BinaCPP_logger::write_log( "<BinaCPP::start_userDataStream> url = |%s|" , url.c_str() ) ;
	
	string action = "POST";
	string post_data = "";

	string str_result;
	curl_api_with_header( url, str_result , extra_http_header , post_data , action ) ;

	if ( str_result.size() > 0 ) {
		
		try {
			Json::Reader reader;
			json_result.clear();	
			reader.parse( str_result , json_result );
	    		
	    	} catch ( exception &e ) {
		 	BinaCPP_logger::write_log( "<BinaCPP::start_userDataStream> Error ! %s", e.what() ); 
		}   
		BinaCPP_logger::write_log( "<BinaCPP::start_userDataStream> Done." ) ;
	
	} else {
		BinaCPP_logger::write_log( "<BinaCPP::start_userDataStream> Failed to get anything." ) ;
	}

	BinaCPP_logger::write_log( "<BinaCPP::start_userDataStream> Done.\n" ) ;

}









//--------------------
//Keepalive user data stream (API-KEY)
void 
BinaCPP::keep_userDataStream( const char *listenKey ) 
{	
	BinaCPP_logger::write_log( "<BinaCPP::keep_userDataStream>" ) ;

	if ( api_key.size() == 0 ) {
		BinaCPP_logger::write_log( "<BinaCPP::keep_userDataStream> API Key has not been set." ) ;
		return ;
	}


	string url(BINANCE_HOST);
	url += "/api/v1/userDataStream";

	vector <string> extra_http_header;
	string header_chunk("X-MBX-APIKEY: ");
	

	header_chunk.append( api_key );
	extra_http_header.push_back(header_chunk);

	string action = "PUT";
	string post_data("listenKey=");
	post_data.append( listenKey );

	BinaCPP_logger::write_log( "<BinaCPP::keep_userDataStream> url = |%s|, post_data = |%s|" , url.c_str() , post_data.c_str() ) ;
	
	string str_result;
	curl_api_with_header( url, str_result , extra_http_header , post_data , action ) ;

	if ( str_result.size() > 0 ) {
		
		BinaCPP_logger::write_log( "<BinaCPP::keep_userDataStream> Done." ) ;
	
	} else {
		BinaCPP_logger::write_log( "<BinaCPP::keep_userDataStream> Failed to get anything." ) ;
	}

	BinaCPP_logger::write_log( "<BinaCPP::keep_userDataStream> Done.\n" ) ;

}





//--------------------
//Keepalive user data stream (API-KEY)
void 
BinaCPP::close_userDataStream( const char *listenKey ) 
{	
	BinaCPP_logger::write_log( "<BinaCPP::close_userDataStream>" ) ;

	if ( api_key.size() == 0 ) {
		BinaCPP_logger::write_log( "<BinaCPP::close_userDataStream> API Key has not been set." ) ;
		return ;
	}


	string url(BINANCE_HOST);
	url += "/api/v1/userDataStream";

	vector <string> extra_http_header;
	string header_chunk("X-MBX-APIKEY: ");
	

	header_chunk.append( api_key );
	extra_http_header.push_back(header_chunk);

	string action = "DELETE";
	string post_data("listenKey=");
	post_data.append( listenKey );

	BinaCPP_logger::write_log( "<BinaCPP::close_userDataStream> url = |%s|, post_data = |%s|" , url.c_str() , post_data.c_str() ) ;
	
	string str_result;
	curl_api_with_header( url, str_result , extra_http_header , post_data , action ) ;

	if ( str_result.size() > 0 ) {
		
		BinaCPP_logger::write_log( "<BinaCPP::close_userDataStream> Done." ) ;
	
	} else {
		BinaCPP_logger::write_log( "<BinaCPP::close_userDataStream> Failed to get anything." ) ;
	}

	BinaCPP_logger::write_log( "<BinaCPP::close_userDataStream> Done.\n" ) ;

}















//-----------------
// Curl's callback
size_t 
BinaCPP::curl_cb( void *content, size_t size, size_t nmemb, std::string *buffer ) 
{	
	BinaCPP_logger::write_log( "<BinaCPP::curl_cb> " ) ;

	size_t newLength = size*nmemb;
	size_t oldLength = buffer->size();
	try {
		buffer->resize(oldLength + newLength);
	
	} catch(std::bad_alloc &e) {
		//handle memory problem
		return 0;
	}

	std::copy((char*)content,(char*)content + newLength,buffer->begin()+oldLength);
	BinaCPP_logger::write_log( "<BinaCPP::curl_cb> done" ) ;
	return size*nmemb;
}






//--------------------------------------------------
void 
BinaCPP::curl_api( string &url, string &result_json ) {
	vector <string> v;
	string action = "GET";
	string post_data = "";
	curl_api_with_header( url , result_json , v, post_data , action );	
} 



//--------------------
// Do the curl
void 
BinaCPP::curl_api_with_header( string &url, string &str_result, vector <string> &extra_http_header , string &post_data , string &action ) 
{
	BinaCPP_logger::write_log( "<BinaCPP::curl_api>" ) ;

	CURL *curl;
	CURLcode res;
	
	curl_global_init(CURL_GLOBAL_DEFAULT);

	curl = curl_easy_init();
	
	if( curl ) { 

		curl_easy_setopt(curl, CURLOPT_URL, url.c_str() );
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, BinaCPP::curl_cb);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &str_result );
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);

		if ( extra_http_header.size() > 0 ) {
			
			struct curl_slist *chunk = NULL;
			for ( int i = 0 ; i < extra_http_header.size() ;i++ ) {
				chunk = curl_slist_append(chunk, extra_http_header[i].c_str() );
			}
 			curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);
 		}

 		if ( post_data.size() > 0 || action == "POST" || action == "PUT" || action == "DELETE" ) {

 			if ( action == "PUT" || action == "DELETE" ) {
 				curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, action.c_str() );
 			}
 			curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_data.c_str() );
 		}

		res = curl_easy_perform(curl);

		/* Check for errors */ 
		if ( res != CURLE_OK ) {
			BinaCPP_logger::write_log( "<BinaCPP::curl_api> curl_easy_perform() failed: %s" , curl_easy_strerror(res) ) ;
		} 	
		/* always cleanup */ 
		curl_easy_cleanup(curl);
	}
	curl_global_cleanup();

	BinaCPP_logger::write_log( "<BinaCPP::curl_api> done" ) ;

}



