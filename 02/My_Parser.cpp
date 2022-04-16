#include "My_Parser.hpp"

void TokenParser::SetStartCallback(void (*start)() = nullptr){
	 callback_start_ = start;
}
void TokenParser::SetEndCallback(void (*end)(std::vector<uint64_t>, std::vector<uint64_t>) = nullptr){
	 callback_end_ = end;
}
void TokenParser::SetDigitTokenCallback(uint64_t (*digit)(uint64_t) = nullptr){
	 callback_num_ = digit;
}
void TokenParser::SetStringTokenCallback(uint64_t (*str)(const std::string) = nullptr){
	 callback_str_ = str;
}
std::vector<uint64_t>  TokenParser::get_stat_num(){
	return stat_num_; 
}
std::vector<uint64_t> TokenParser::get_stat_str(){
	return stat_str_; 
}
uint64_t TokenParser::get_last_num(){
	return last_num_; 
}
std::string TokenParser::get_last_str(){
	return last_str_; 
}

void TokenParser::Parse(const std::string &str){
	uint64_t value;
	if (callback_start_){callback_start_();}
	auto it = str.begin();
	std::string buf;
	bool num;
	while(it != str.end()){
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
			last_num_ = value;
			if (callback_num_){
				stat_num_.push_back( callback_num_(value));
			}
		}
		else{
			last_str_ = buf;
			if (callback_str_){
				stat_str_.push_back(callback_str_(buf));
			}
		}
		if (*it == ' ' || *it == '\t'){
			it++;
		}
	}
	
	if (callback_end_){callback_end_(stat_num_, stat_str_);}
}
