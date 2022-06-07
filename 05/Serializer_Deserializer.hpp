#pragma once
#include <iostream>
#include <sstream>

enum class Error
{
    NoError,
    CorruptedArchive
};

class Serializer
{
private:
	std::ostream& out_;
    static constexpr char Separator = ' ';
public:
    explicit Serializer(std::ostream& out): out_(out){}
    template <class T>
    Error save(T&);
    template <class... Args>
    Error operator()(Args&&...);
private:
	template <class T>
	Error process(T&&);
	template <class T, class... Args>
	Error process(T&&, Args&&... );
    Error saving(bool);
    Error saving(uint64_t);	
};


class Deserializer
{
private:
	std::istream& in_;
    static constexpr char Separator = ' ';
public:
    explicit Deserializer(std::istream& in): in_(in){}
    template <class T>
    Error load(T&);
    template <class... Args>
    Error operator()(Args&&...);
private:
	template <class T>
	Error process(T&&);
	template <class T, class... Args>
	Error process(T&&, Args&&...);
    Error loading(bool &);
    Error loading(uint64_t &);
};
#include "templ.tpp"