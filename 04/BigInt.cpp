#include "BigInt.hpp"


BigInt::BigInt(){
	data_ = nullptr;
	len_ = 0;
	minus_ = false;
}

BigInt::BigInt(const char* str){
	std::string s(str);
	minus_ = false;
	if (s[0] == '-'){
		minus_ = true;
		s.erase(0, 1);
	}
	len_ = s.size();
	data_ = new int32_t[len_];
	for(size_t i = 0; i < len_; i++){
		data_[i] = static_cast <int32_t> (s[len_ - i - 1] - '0');
	}
}

BigInt::BigInt(std::string str){
	minus_ = false;
	if (str[0] == '-'){
		minus_ = true;
		str.erase(0, 1);
	}
	len_ = str.size();
	data_ = new int32_t[len_];
	for(size_t i = 0; i < len_; i++){
		data_[i] = static_cast <int32_t> (str[len_ - i - 1] - '0');
	}
}

BigInt::BigInt(int32_t num){
	minus_ = false;
	std::string s = std::to_string(num);
	if (s[0] == '-'){
		minus_ = true;
		s.erase(0, 1);
	}
	len_ = s.size();
	data_ = new int32_t[len_];
	for(size_t i = 0; i < len_; i++){
		data_[i] = static_cast <int32_t> (s[len_ - i - 1] - '0');
	}
}

BigInt::BigInt(int32_t* num, size_t size, bool min){
	len_ = size;
	minus_ = min;
	data_ = num;

}
BigInt::~BigInt(){
	delete [] data_;
	data_ = nullptr;
}

BigInt::BigInt(const BigInt& num){
	len_ = num.len_;
	minus_ = num.minus_;
	data_ = new int32_t[len_];
	for(size_t i = 0; i < len_; i++){
		data_[i] = num.data_[i];
	}
}

BigInt::BigInt(BigInt&& num){
	len_ = num.len_;
	minus_ = num.minus_;
	data_ = num.data_;
	num.data_ = nullptr;
	num.len_ = 0;
	num.minus_ = false;
}

BigInt& BigInt::operator = (const BigInt& num){
	if (&num == this){
		return *this;
	}
	else{
		delete [] data_;
		len_ = num.len_;
		minus_ = num.minus_;
		data_ = new int32_t[len_];
		for(size_t i = 0; i < len_; i++){
			data_[i] = num.data_[i];
		}
	}
	return *this;
}

BigInt& BigInt::operator = (BigInt&& num){
	delete [] data_;
	len_ = num.len_;
	minus_ = num.minus_;
	data_ = num.data_;
	num.data_ = nullptr;
	num.len_ = 0;
	num.minus_ = false;
	return *this;
}

std::ostream & operator<<(std::ostream& out, const BigInt& num){
	if (num.minus_){
		std::cout << '-';
	}
	for (size_t i = 0; i  < num.len_; i++){
		std::cout << num.data_[num.len_ - i - 1];
	}
	return out;
}
std::string BigInt::get_num(){
	std::string s;
	for (size_t i = 0; i < len_; i++){
		s.append(std::to_string(data_[len_ - i - 1]));
	}
	if (minus_){
		s = '-' + s;
	}
	return s;
}

BigInt BigInt::operator-() const{
	int32_t* buf = new int32_t[len_];
	for (size_t i = 0; i < len_; i ++){
		buf[i] = data_[i];
	}
	if (*this != 0){
		BigInt a(buf, len_, !minus_);
		return a;
	}
	BigInt a(buf, len_, false);
	return a;
}

BigInt BigInt::operator+(const BigInt& num) const{
	if (minus_ && !num.minus_){return num - (-(*this));}
	if (!minus_ && num.minus_){return *this - (-(num));} 
	if (minus_ && num.minus_){return -(-(*this) + (-num));}
	if (*this < num){return num + *this;}
	int32_t* buf = new int32_t[len_ + 1];
	int32_t transfer = 0;
	for (size_t i = 0; i < num.len_; i++){
		buf[i] = (data_[i] + num.data_[i] + transfer) % 10;
		transfer = (data_[i] + num.data_[i] + transfer) / 10;
	}
	for (size_t i = num.len_; i < len_; i ++){
		buf[i] = (data_[i]  + transfer) % 10;
		transfer = (data_[i] + transfer) / 10;
	}
	size_t size = len_ + 1;
	if (transfer == 0){
		size--;
	}
	else{
		buf[size] = transfer;
	}
	BigInt a(buf, size, false);
	return a;
}

BigInt BigInt::operator-(const BigInt& num) const{
	if (minus_ && !num.minus_){return -(num + (-(*this)));} 
	if (!minus_ && num.minus_){return *this + (-(num));}
	if (!minus_){
		if (*this >= num){
			int32_t* buf = new int32_t[len_];
			int32_t transfer = 0;
			for (size_t i = 0; i < num.len_; i++){
				if (data_[i] < transfer+num.data_[i]){
					buf[i] = 10 + data_[i] - num.data_[i] - transfer;
					transfer = 1;
				}
				else{
					buf[i] = data_[i] - num.data_[i] - transfer;
					transfer = 0;
				}
			}
			for (size_t i = num.len_; i < len_; i++){
				if (data_[i] < transfer){
					buf[i] = (10 + data_[i]  - transfer);
				}
				else{
					buf[i] = (data_[i]  - transfer);
					transfer = 0;
				}
			}
			size_t zero = 0;
			for (size_t i = 0; i < len_ - 1; i++){
				if (buf[len_ - i - 1] != 0){
					break;
				}
				zero++;
			}
			BigInt a(buf, len_ - zero, false);
			return a;
		}
		else{
			return -(num - *this);
		}
	}
	else{
		return -num - (-(*this));
	}
}
BigInt BigInt::operator*(const BigInt& num) const{
	bool min = !(minus_ == num.minus_);
	int32_t* buf = new int32_t[len_ + num.len_];
	for (size_t i = 0; i < num.len_ + len_; i++){
		buf[i] = 0;
	}
	for (size_t i = 0; i < len_; i++){
		for (size_t j = 0; j < num.len_; j++){
			buf[i+j] += data_[i] * num.data_[j];
			for (size_t k = i + j; k < len_ + num.len_; k++){
				if (buf[k] >= 10){
					buf[k+1] += buf[k] / 10;
					buf[k] = buf[k] % 10;
				}
				else{
					break;
				}
			}
		}
	}
	

	size_t zero = 0;
	for (size_t i = 0; i < len_ + num.len_ - 1; i++){
		if (buf[len_ + num.len_ - i - 1] != 0){
			break;
		}
		zero++;
	}
	if (zero == len_ + num.len_ - 1 && buf[0] == 0){
		BigInt a(buf, 1, false);
		return a;
	}
	BigInt a(buf, len_ + num.len_ - zero, min);
	return a;
}
BigInt BigInt::operator+(int32_t num) const{
	BigInt a(num);
	return *this + a;
}
BigInt BigInt::operator-(int32_t num) const{
	BigInt a(num);
	return *this - a;
}
BigInt BigInt::operator*(int32_t num) const{
	BigInt a(num);
	return *this * a;
}

bool BigInt::operator==(const BigInt& num) const{
	if (minus_ != num.minus_){return false;}
	if (len_ != num.len_){return false;}
	for (size_t i = 0; i < len_; i++){
		if (data_[i] != num.data_[i]){
			return false;
		}
	}
	return true;
}

bool BigInt::operator>(const BigInt& num) const{
	if (!minus_ && num.minus_){return true;}
	if (minus_ && !num.minus_){return false;}
	if (len_ < num.len_){return minus_;}
	if (len_ > num.len_){return !minus_;}
	for (size_t i = 0; i < len_; i++){
		if (data_[len_ - i - 1] > num.data_[len_ - i - 1]){
			return !minus_;
		}
		if (data_[len_ - i - 1] < num.data_[len_ - i - 1]){
			return minus_;
		}
	}
	return false;
}

bool BigInt::operator!=(const BigInt& num) const{
	return !(*this == num);
}

bool BigInt::operator>=(const BigInt& num) const{
	return (*this == num) || (*this > num);
}

bool BigInt::operator<(const BigInt& num) const{
	return !(*this >= num);
}

bool BigInt::operator<=(const BigInt& num) const{
	return !(*this > num);
}


