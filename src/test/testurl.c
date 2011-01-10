#include <url.h>
#include <log.h>
#include <stdio.h>

int main(int argc, char ** argv)
{
	log_init();
	Connection *con = connect_to_host("202.117.21.117", 3128);
	if(con == NULL){
		return 0;
	}
	Request *r = request_new();
	request_set_method(r, "GET");
	request_set_uri(r, "http://web2.qq.com");
	request_set_version(r, "HTTP/1.1");
	request_set_default_headers(r);
	request_add_header(r, "Proxy-Authorization", "Basic "
						"YWNtOjEyMzQ1Njc4OTBhIQ==");
	request_add_header(r, "Cache-Control", "maxage=0");
	
	if(send_request(con, r) < 0){
		close_con(con);
		return 0;
	}
	Response *rps = NULL;
	if(rcv_response(con, &rps) < 0){
		close_con(con);
		return 0;
	}
	printf("%s\n", response_tostring(rps) -> str);
	close_con(con);
	return 0;
}
