#pragma once
#include <vector>
/**	Field is a template class and can create fields
	init: creates a field of the size x and y
	at: access the information at the position x and y
*/

struct Position {
	int x;
	int y;
};

template<typename T>
class Field
{
private:
	std::vector <T> data;
	size_t fieldSizeX;
	size_t fieldSizeY;
	
	
public:
	void init(int fieldsizeX, int fieldsizeY);
	void init(int fieldsizeX, int fieldsizeY, T value);
	
	T& at(int x, int y);
	T const& at(int x, int y) const;
	T& at(size_t index);

	size_t getSizeX() const;
	size_t getSizeY() const;
	size_t getIndex(int x, int y) const;
	Position getPosition(size_t index) const;
	T const& getValue(size_t index)const;
	std::vector <T> const& getData()const;
	std::vector <T> & getData();


	size_t getSize() const { return data.size(); }
};

template<typename T>
void Field<T>::init(int fieldsizeX, int fieldsizeY)
{
	fieldSizeX = fieldsizeX;
	fieldSizeY = fieldsizeY;
	data.resize(fieldSizeX * fieldSizeY);
	memset(data.data(), 0,  fieldsizeY * fieldsizeX * sizeof(T));
}

template<typename T>
void Field<T>::init(int fieldsizeX, int fieldsizeY, T value)
{
	fieldSizeX = fieldsizeX;
	fieldSizeY = fieldsizeY;
	data.resize(fieldSizeX * fieldSizeY, value);
}


template<typename T>
T& Field<T>::at(int x, int y)
{
	return data.at(getIndex(x, y));
}

template<typename T>
T const& Field<T>::at(int x, int y) const
{
	return data.at(getIndex(x, y));
}

template<typename T>
T& Field<T>::at(size_t index)
{
	return data.at(index);
}

template<typename T>
size_t Field<T>::getIndex(int x, int y) const
{
	return y * fieldSizeX + x;
}

template<typename T>
Position Field<T>::getPosition(size_t index) const
{
	Position pos;
	pos.y = index / fieldSizeX;
	pos.x = index - pos.y * fieldSizeX;
	return pos;
}
template<typename T>
size_t Field<T>::getSizeX() const
{
	return fieldSizeX;
}

template<typename T>
size_t Field<T>::getSizeY() const 
{ 
	return fieldSizeY; 
}

template<typename T>
T const& Field<T>::getValue(size_t index) const
{
	return data.at(index);
}

template<typename T>
std::vector<T> const& Field<T>::getData() const
{
	return data;
}

template<typename T>
std::vector<T>& Field<T>::getData()
{
	return data;
}