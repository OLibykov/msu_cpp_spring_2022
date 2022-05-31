#pragma once
#include <iostream>
#include <string>
#include <algorithm>

class BigInt
{
private:
	int32_t* data_;
	size_t len_;
	bool minus_;
	BigInt(int32_t*, size_t, bool);
public:
	BigInt();
	BigInt(const char* str);
	BigInt(std::string str);
	BigInt(int32_t);
	~BigInt();
	BigInt(const BigInt&);
	BigInt(BigInt&&);
	BigInt& operator = (const BigInt&);
	BigInt& operator = (BigInt&&);
	std::string get_num();
	friend std::ostream & operator<<(std::ostream& , const BigInt&);
	BigInt operator+(const BigInt&) const;
	BigInt operator-(const BigInt&) const;
	BigInt operator*(const BigInt&) const;
	BigInt operator+(int32_t) const;
	BigInt operator-(int32_t) const;
	BigInt operator*(int32_t) const;
	BigInt operator-() const;
	bool operator==(const BigInt&) const;
	bool operator>(const BigInt&) const;	
	bool operator!=(const BigInt&) const;
	bool operator>=(const BigInt&) const;	
	bool operator<(const BigInt&) const;	
	bool operator<=(const BigInt&) const;	
};

