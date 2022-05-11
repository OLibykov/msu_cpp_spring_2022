#include "My_Parser.hpp"

void TokenParser::SetStartCallback(void (*start)() = nullptr){
	 callback_start_ = start;
}
void TokenParser::SetEndCallback(void (*end)() = nullptr){
	 callback_end_ = end;
}
void TokenParser::SetDigitTokenCallback(void (*digit)(uint64_t) = nullptr){
	 callback_num_ = digit;
}
void TokenParser::SetStringTokenCallback(void (*str)(const std::string) = nullptr){
	 callback_str_ = str;
}

void TokenParser::Parse(const std::string &str){
	uint64_t value;
	if (callback_start_){callback_start_();}
	auto it = str.begin();
	std::string buf;
	bool num;
	while(it != str.end()){
		while(it != str.end() && (*it == ' ' || *it =='\t')){
			it++;
		}
		if (it  == str.end()){break;}
		buf = "";
		num = true;
		while(it != str.end() && *it != ' ' && *it !='\t'){
			if (!std::isdigit(*it)){num = false;}
			buf += *it;
			it++;
		}
		if (num){
			std::stringstream stream(buf);
			stream >> value;
			if (callback_num_){
				callback_num_(value);
			}
		}
		else{
			if (callback_str_){
				callback_str_(buf);
			}
		}
	}
	
	if (callback_end_){callback_end_();}
}
