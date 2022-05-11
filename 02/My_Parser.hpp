#pragma once
#include <iostream>
#include <functional>
#include <vector>
#include <string>
#include <sstream>

using func = std::function<void()>;
using func_uint = std::function<void(uint64_t)>;
using func_str = std::function<void(const std::string)>;

class TokenParser
{
private:
	func callback_start_;
	func callback_end_;
	func_uint callback_num_;
	func_str callback_str_;


public:
	TokenParser() = default;

	void SetStartCallback(void (*)());

	void SetEndCallback(void (*)());

	void SetDigitTokenCallback(void (*)(uint64_t));

	void SetStringTokenCallback(void (*)(const std::string));

	void Parse(const std::string &);

};
