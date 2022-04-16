#pragma once
#include <iostream>
#include <functional>
#include <vector>
#include <string>
#include <sstream>

class TokenParser
{
private:
    std::function<void()> callback_start_;
	std::function<void(std::vector<uint64_t>, std::vector<uint64_t>)> callback_end_;
	std::function<uint64_t(uint64_t)> callback_num_;
	std::function<uint64_t(const std::string)> callback_str_;
	std::vector<uint64_t> stat_num_; 
	std::vector<uint64_t> stat_str_;
	uint64_t last_num_;
	std::string last_str_;
	
public:
    TokenParser() = default;

    void SetStartCallback(void (*)());

    void SetEndCallback(void (*)(std::vector<uint64_t>, std::vector<uint64_t>));

    void SetDigitTokenCallback(uint64_t (*)(uint64_t));
	
	void SetStringTokenCallback(uint64_t (*)(const std::string));

    void Parse(const std::string &);
	
	std::vector<uint64_t> get_stat_num();
	
	std::vector<uint64_t> get_stat_str();
	
	uint64_t get_last_num();
	
	std::string get_last_str();
};
