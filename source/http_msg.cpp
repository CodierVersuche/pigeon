#include "http_msg.h"
#include <http_util.h>
#include <iostream>

using namespace std;
using namespace pigeon;

http_msg::~http_msg() {

}

auto http_msg::has_headers() -> bool{
	if (headers.size() > 0){ return true; }
	else { return false; }
}

auto http_msg::set_header_field(string& _key) -> void{

    key_value_pair kvp;
    kvp.key = _key;
    headers.push_back(kvp);

}

auto http_msg::set_header_value(string& _value) -> void{

    if(headers.empty()) {
        return;
    }
    headers.back().value = _value;

}

auto http_msg::get_header(key_value_pair& kvp) -> void {

    for(auto& hdr : headers){
        if(hdr.key == kvp.key){
            kvp = hdr;
        }
    }

}

auto http_msg::get_non_default_headers(string &msg) -> void {

    for (auto& hdr : headers){
        msg += hdr.key;
        msg += hdr.value;
        msg += "\r\n";
    }

}

auto http_request::get_parameter(key_value_pair& kvp) -> void {

    for(auto& prm : parameters){
        if(prm.key == kvp.key){
            kvp = prm;
        }
    }

}

auto http_request::create_response(const char* msg, http_response& response, HttpStatus status) -> void {

    response.message += get_status_phrase(status);
    response.message += get_err_msg(status);;

}

auto http_request::create_response(string& message, http_response& response, HttpStatus status) -> void {
    
    response.content += message;
    response.status = (unsigned int)status;

    response.message += get_status_phrase(status);
    response.message += get_cached_response(is_api);
    
    if (is_api){

        response.message += get_header_field(HttpHeader::Content_Length);
        response.message += std::to_string(message.size());
        response.message += "\r\n";

    }
    
    response.get_non_default_headers(response.message);
    response.message += "\r\n";
    response.message += response.content;

}


auto http_request::create_response(string& cached_headers, string& message, http_response& response, HttpStatus status) -> void {
	
	response.content += message;
	response.status = (unsigned int)status;

	response.message += get_status_phrase(status);
	response.message += get_cached_response(is_api);
	
	if (is_api){

		response.message += get_header_field(HttpHeader::Content_Length);
		response.message += std::to_string(message.size());
		response.message += "\r\n";

    }

	response.message += cached_headers;
	response.get_non_default_headers(response.message);
	response.message += "\r\n";
	response.message += response.content;

}

auto http_request::set_parameter(key_value_pair& kvp) -> void {
    parameters.push_back(std::move(kvp));
}

http_response::~http_response() {

}

http_request::~http_request() {

}