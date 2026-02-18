#pragma once
#include <iostream>
#include <utility>  // для std::pair
#include <vector>   

template <typename TKey, typename TValue>
class ITable
{
public:

	virtual void insert(const TKey& Key, const TValue& Val) = 0;
	virtual TValue find(const TKey& Key) const = 0;
	virtual void erase(const TKey& Key) = 0;
	virtual std::ostream& print(std::ostream& out)const noexcept = 0;
	virtual bool is_empty() const noexcept = 0;
	virtual bool consist(const TKey& Key)const noexcept = 0;
	virtual size_t size() const noexcept = 0;
	virtual~ITable() {}

};