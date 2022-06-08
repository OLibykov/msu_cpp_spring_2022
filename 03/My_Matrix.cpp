#include "My_Matrix.hpp"

Matrix::ProxyRow::ProxyRow(size_t size){
	data_ = new int32_t[size];
	len_ = size;
	for (size_t i = 0; i < size; i++){
		data_[i] = 0;
	}
}
Matrix::ProxyRow::ProxyRow(){
	data_ = nullptr;
	len_ = 0;
}
int32_t& Matrix::ProxyRow::operator[](size_t i){
	if (i >= len_ ){
		throw std::out_of_range("Out of bounds");
	}
	return data_[i];
}
/*Matrix::ProxyRow* Matrix::ProxyRow::operator*=(int32_t mul){
	for (size_t i = 0; i < len_; i++){
		data_[i] *= mul;
	} 
	return this;
}*/
Matrix::ProxyRow& Matrix::ProxyRow::operator=(ProxyRow&& copy){
	len_ = copy.len_;
	data_ = copy.data_;
	copy.data_ = nullptr;
	return *this;
}
Matrix::ProxyRow::~ProxyRow(){
	if (data_ != nullptr){
		delete[] data_;
	}
}
std::ostream& operator<<(std::ostream& out, const Matrix::ProxyRow &row){
	for(size_t i = 0; i < row.len_; i++){
		out << row.data_[i] << ' ';
	}
	return out;
}
Matrix::Matrix(){
	rows_ = nullptr;
	n_row_ = 0;
	n_col_ = 0;
}
Matrix::Matrix(size_t row = 5, size_t col = 5): n_row_(row), n_col_(col) {
	rows_ = new ProxyRow[n_row_];
	for (size_t i = 0; i < n_row_; i++){
		rows_[i] = ProxyRow(n_col_);
	}
}
Matrix::~Matrix(){
	if (rows_ != nullptr){
		delete[] rows_;
	}
}
Matrix::Matrix(const Matrix& mat) {
	n_row_ = mat.n_row_;
	n_col_ = mat.n_col_;
	rows_ = new ProxyRow[n_row_];
	for(size_t i = 0; i < n_row_; i++){rows_[i] = ProxyRow(n_col_);}
	for(size_t i = 0; i < n_row_; i++){
		for(size_t j = 0; j < n_col_; j++){
			rows_[i][j] = mat.rows_[i][j];
		}
	}
}
Matrix::Matrix(Matrix&& mat){
	n_row_ = mat.n_row_;
	n_col_ = mat.n_col_;
	rows_ = mat.rows_;
	mat.rows_ = nullptr;
}
Matrix& Matrix::operator=(const Matrix& mat){
	n_row_ = mat.n_row_;
	n_col_ = mat.n_col_;
	if (rows_ != nullptr){
		delete[] rows_;
	}
	rows_ = new ProxyRow[n_row_];
	for(size_t i = 0; i < n_row_; i++){rows_[i] = ProxyRow(n_col_);}
	for(size_t i = 0; i < n_row_; i++){
		for(size_t j = 0; j < n_col_; j++){
			rows_[i][j] = mat.rows_[i][j];
		}
	}
	return *this;
}
Matrix& Matrix::operator=(Matrix&& mat){
	if (rows_ != nullptr){
		delete[] rows_;
	}
	rows_ = mat.rows_;
	n_row_ = mat.n_row_;
	n_col_ = mat.n_col_;
	mat.rows_ = nullptr;
	return *this;
}

size_t Matrix::get_n_row() const{
	return n_row_;
}
size_t Matrix::get_n_col() const{
	return n_col_;
}
Matrix::ProxyRow& Matrix::operator[](size_t i){
	if (i >= n_row_){
		throw std::out_of_range("Out of bounds");
	}
	return rows_[i];
}
Matrix& Matrix::operator*=(int32_t mul){
	for(size_t i = 0; i < n_row_; i++){
		for(size_t j = 0; j < n_col_; j++){
			rows_[i][j] *= mul;
		}
	}
	return *this;
}
std::ostream& operator<<(std::ostream& out, const Matrix &mat){
	for(size_t i = 0; i < mat.n_row_; i++){
		out << mat.rows_[i] << std::endl;
	}
	return out;
}
Matrix Matrix::operator+(const Matrix& mat) const{
	if (mat.get_n_row() != n_row_ || mat.get_n_col() != n_col_){
		throw std::out_of_range("The matrices have different sizes");
	}
	Matrix tmp(n_row_, n_col_);
	for(size_t i = 0; i < n_row_; i++){
		for(size_t j = 0; j < n_col_; j++){
			tmp.rows_[i][j] = mat.rows_[i][j]  + rows_[i][j];
		}
	}
	return tmp;
}
bool Matrix::operator==(const Matrix& mat) const{
	if (mat.get_n_row() != n_row_ || mat.get_n_col() != n_col_){
		throw std::out_of_range("The matrices have different sizes");
	}
	bool ok = true;
	for(size_t i = 0; i < mat.n_row_; i++){
		for(size_t j = 0; j < mat.n_col_; j++){
			if (rows_[i][j] != mat.rows_[i][j]){
				ok = false;
				break;
			}
		}
		if (!ok){
			break;
		}
	}
	return ok;
}
bool Matrix::operator!=(const Matrix& mat) const{
	return !(mat == *this);
}