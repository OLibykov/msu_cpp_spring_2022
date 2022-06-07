#pragma once


template <class T>
Error Serializer::save(T& object)
{
	return object.serialize(*this);
}
template <class... Args>
Error Serializer::operator()(Args&&... args)
{
	return process(std::forward<Args>(args)...);
}

template <class T>
Error Serializer::process(T&& val)
{
	return saving(val);
}
template <class T, class... Args>
Error Serializer::process(T&& val, Args&&... args)
{
	if (saving(val) == Error::CorruptedArchive)
	{
		return Error::CorruptedArchive;
	}
	out_ << Separator;
	return process(std::forward<Args>(args)...);
}	

template <class T>
Error Deserializer::load(T& object)
{
	return object.deserialize(*this);
}
template <class... Args>
Error Deserializer::operator()(Args&&... args)
{
	return process(std::forward<Args>(args)...);
}
template <class T>
Error Deserializer::process(T&& val)
{
	return loading(val);
}
template <class T, class... Args>
Error Deserializer::process(T&& val, Args&&... args)
{
	if (loading(val) == Error::CorruptedArchive){
		return Error::CorruptedArchive;
	}

	return process(std::forward<Args>(args)...);
}
