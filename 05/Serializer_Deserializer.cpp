#include "Serializer_Deserializer.hpp"

Error Serializer::saving(bool val)
{
	if (val)
	{
		out_ << "true" ;
	}
	else
	{
		out_ << "false" ;
	}
	return Error::NoError;
}
Error Serializer::saving(uint64_t val)
{
	out_ << (std::to_string(val));
	return Error::NoError;
}


Error Deserializer::loading(bool &value)
{
	std::string text;
    in_ >> text;
    if (text == "true")
        value = true;
    else if (text == "false")
        value = false;
    else
        return Error::CorruptedArchive;
    return Error::NoError;
}
Error Deserializer::loading(uint64_t &val)
{
	std::string text;
    in_ >> text;
	if (text.size() > 20 || text.size() == 0)
	{//uint64_t может сожержать 20 разрядов
		return Error::CorruptedArchive;
	}
	for (size_t i = 0; i < text.size(); i++)
	{
		if (!isdigit(text[i]))
		{
			return Error::CorruptedArchive;
		}
	}
	if (text.size() == 20)
	{
		uint64_t tmp;
		char last = text[19];
		text.pop_back();
		std::stringstream stream(text);
		stream >> tmp;
		if (tmp > uint64_t(std::numeric_limits<uint64_t>::max() / 10))
		{
			return Error::CorruptedArchive;
		}
		if (tmp == uint64_t(std::numeric_limits<uint64_t>::max() / 10) && last - '0' > 5)
		{
			return Error::CorruptedArchive;
		}
		text += last;
	}
	uint64_t hlp;
	std::stringstream stream(text);
	stream >> hlp;
	val = hlp;
	return Error::NoError;
}
	