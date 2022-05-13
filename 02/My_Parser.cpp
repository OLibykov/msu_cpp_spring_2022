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
		if (buf.size() > 20){//Размер 2^64
			num = false;
		}
		if (num && buf.size() ==  20){
			char last = buf[19];
			buf.pop_back();
			std::stringstream stream(buf);
			stream >> value;
			if (value > uint64_t(std::numeric_limits<uint64_t>::max() / 10) && last - '0' > 5){
				num = false;
			}
			if (value == uint64_t(std::numeric_limits<uint64_t>::max() / 10) && last - '0' > 5){
				num = false;
			}
			buf += last;
		}
		if (num){
			if (callback_num_){
				std::stringstream stream(buf);
				stream >> value;
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
