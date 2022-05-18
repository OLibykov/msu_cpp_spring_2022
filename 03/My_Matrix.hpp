#pragma once
#include <iostream>


class Matrix
{
private:
	class ProxyRow
	{
	public:
		int32_t* data_;
		size_t len_;
		ProxyRow();
		~ProxyRow();
		ProxyRow& operator = (ProxyRow&&);
		ProxyRow(size_t);
		ProxyRow* operator*=(int32_t);
		int32_t& operator[](size_t);
	};
	
	size_t n_row_;
	size_t n_col_;
	ProxyRow* rows_;

	
public:
	Matrix(size_t, size_t);
	Matrix();
	~Matrix();
	Matrix(const Matrix&);
	Matrix(Matrix&&);
	Matrix& operator = (const Matrix&);
	Matrix& operator = (Matrix&&);
	size_t get_n_row() const;
	size_t get_n_col() const;
	ProxyRow& operator[](size_t);
	Matrix& operator*=(int32_t);
	friend std::ostream & operator<<(std::ostream& , const ProxyRow&);
	friend std::ostream & operator<<(std::ostream& out, const Matrix&);
	Matrix operator+(const Matrix& mat) const;
	bool operator==(const Matrix& mat) const;
	bool operator!=(const Matrix& mat) const;	
};

