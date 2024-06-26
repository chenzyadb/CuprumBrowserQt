// CuPairList by chenzyadb@github.com
// Based on C++17 STL (MSVC)

#ifndef _CU_PAIR_LIST_
#define _CU_PAIR_LIST_

#include <exception>
#include <vector>
#include <string>
#include <algorithm>
#include <memory>
#include <utility>

namespace CU
{
	class PairListExcept : public std::exception
	{
		public:
			PairListExcept(const std::string &message) : message_(message) { }

			const char* what() const noexcept override
			{
				return message_.c_str();
			}

		private:
			const std::string message_;
	};

	template <class _Ty1, class _Ty2>
	class PairList
	{
		public:
			class Iterator
			{
				public:
					typedef typename std::vector<_Ty1>::const_iterator KeyIterator;
					typedef typename std::vector<_Ty2>::const_iterator ValueIterator;

					Iterator(KeyIterator keyIter, ValueIterator valueIter) : keyIter_(keyIter), valueIter_(valueIter) { }

					Iterator(const Iterator &other) : keyIter_(), valueIter_()
					{ 
						if (std::addressof(other) != this) {
							keyIter_ = other.getKeyIterator();
							valueIter_ = other.getValueIterator();
						}
					}

					Iterator(Iterator &&other) noexcept : keyIter_(), valueIter_()
					{
						if (std::addressof(other) != this) {
							keyIter_ = other.getKeyIterator();
							valueIter_ = other.getValueIterator();
						}
					}

					Iterator &operator=(const Iterator &other)
					{
						if (std::addressof(other) != this) {
							keyIter_ = other.getKeyIterator();
							valueIter_ = other.getValueIterator();
						}
						return *this;
					}

					Iterator operator+(size_t pos) const
					{
						auto keyIter = keyIter_ + pos;
						auto valueIter = valueIter_ + pos;
						return Iterator(keyIter, valueIter);
					}

					size_t operator-(const Iterator &other) const
					{
						auto keyPos = keyIter_ - other.getKeyIterator();
						auto valuePos = valueIter_ - other.getValueIterator();
						if (keyPos != valuePos) {
							throw PairListExcept("Invaild PairList Iterator");
						}
						return keyPos;
					}

					Iterator &operator+=(size_t pos)
					{
						keyIter_ += pos;
						valueIter_ += pos;
						return *this;
					}

					Iterator &operator-=(size_t pos)
					{
						keyIter_ -= pos;
						valueIter_ -= pos;
						return *this;
					}

					Iterator &operator++()
					{
						keyIter_++;
						valueIter_++;
						return *this;
					}

					Iterator operator++(int _val)
					{
						Iterator origIter(*this);
						keyIter_++;
						valueIter_++;
						return origIter;
					}

					Iterator &operator--()
					{
						keyIter_--;
						valueIter_--;
						return *this;
					}

					Iterator operator--(int _val)
					{
						Iterator origIter(*this);
						keyIter_--;
						valueIter_--;
						return origIter;
					}

					bool operator==(const Iterator &other) const
					{
						return (keyIter_ == other.getKeyIterator() && valueIter_ == other.getValueIterator());
					}

					bool operator!=(const Iterator &other) const
					{
						return (keyIter_ != other.getKeyIterator() || valueIter_ != other.getValueIterator());
					}

					bool operator>(const Iterator &other) const
					{
						return (keyIter_ > other.getKeyIterator() && valueIter_ > other.getValueIterator());
					}

					bool operator<(const Iterator &other) const
					{
						return (keyIter_ < other.getKeyIterator() && valueIter_ < other.getValueIterator());
					}

					std::pair<_Ty1, _Ty2> operator*() const
					{
						return std::make_pair(*keyIter_, *valueIter_);
					}

					KeyIterator getKeyIterator() const
					{
						return keyIter_;
					}

					ValueIterator getValueIterator() const
					{
						return valueIter_;
					}

				private:
					KeyIterator keyIter_;
					ValueIterator valueIter_;
			};

			PairList() : keys_(), values_() { }

			PairList(const std::vector<_Ty1> &keys, const std::vector<_Ty2> &values) :
				keys_(keys),
				values_(values) 
			{ }

			PairList(const PairList &other) : keys_(), values_()
			{
				if (std::addressof(other) != this) {
					keys_ = other.getKeys();
					values_ = other.getValues();
				}
			}

			PairList(PairList &&other) noexcept : keys_(), values_()
			{
				if (std::addressof(other) != this) {
					keys_ = other.getKeys();
					values_ = other.getValues();
				}
			}

			PairList &operator=(const PairList &other)
			{
				if (std::addressof(other) != this) {
					keys_ = other.getKeys();
					values_ = other.getValues();
				}
				return *this;
			}

			bool operator==(const PairList &other) const
			{
				return (keys_ == other.getKeys() && values_ == other.getValues());
			}

			bool operator!=(const PairList &other) const
			{
				return (keys_ != other.getKeys() || values_ != other.getValues());
			}

			_Ty2 &operator[](const _Ty1 &key)
			{
				auto keyIter = std::find(keys_.begin(), keys_.end(), key);
				if (keyIter == keys_.end()) {
					keys_.emplace_back(key);
					values_.emplace_back();
					return values_.back();
				}
				return *(values_.begin() + (keyIter - keys_.begin()));
			}

			_Ty1 &operator()(const _Ty2 &value)
			{
				auto valueIter = std::find(values_.begin(), values_.end(), value);
				if (valueIter == values_.end()) {
					throw PairListExcept("Value not found");
				}
				return *(keys_.begin() + (valueIter - values_.begin()));
			}

			_Ty2 atKey(const _Ty1 &key) const
			{
				auto keyIter = std::find(keys_.begin(), keys_.end(), key);
				if (keyIter == keys_.end()) {
					throw PairListExcept("Key not found");
				}
				return *(values_.begin() + (keyIter - keys_.begin()));
			}

			_Ty1 atValue(const _Ty2 &value) const
			{
				auto valueIter = std::find(values_.begin(), values_.end(), value);
				if (valueIter == values_.end()) {
					throw PairListExcept("Value not found");
				}
				return *(keys_.begin() + (valueIter - values_.begin()));
			}

			bool containsKey(const _Ty1 &key) const
			{
				return (std::find(keys_.begin(), keys_.end(), key) != keys_.end());
			}

			bool containsValue(const _Ty2 &value) const
			{
				return (std::find(values_.begin(), values_.end(), value) != values_.end());
			}

			Iterator begin() const
			{
				return Iterator(keys_.begin(), values_.begin());
			}

			Iterator end() const
			{
				return Iterator(keys_.end(), values_.end());
			}

			std::pair<_Ty1, _Ty2> front() const
			{
				return std::make_pair(keys_.front(), values_.front());
			}

			std::pair<_Ty1, _Ty2> back() const
			{
				return std::make_pair(keys_.back(), values_.back());
			}

			void add(const _Ty1 &key, const _Ty2 &value)
			{
				keys_.emplace_back(key);
				values_.emplace_back(value);
			}

			void removeKey(const _Ty1 &key)
			{
				auto keyIter = std::find(keys_.begin(), keys_.end(), key);
				if (keyIter == keys_.end()) {
					throw PairListExcept("Key not found");
				}
				values_.erase(values_.begin() + (keyIter - keys_.begin()));
				keys_.erase(keyIter);
			}

			void removeValue(const _Ty2 &value)
			{
				auto valueIter = std::find(values_.begin(), values_.end(), value);
				if (valueIter == values_.end()) {
					throw PairListExcept("Value not found");
				}
				keys_.erase(keys_.begin() + (valueIter - values_.begin()));
				values_.erase(valueIter);
			}

			std::vector<_Ty1> getKeys() const
			{
				return keys_;
			}

			std::vector<_Ty2> getValues() const
			{
				return values_;
			}

			void clear()
			{
				keys_.clear();
				values_.clear();
			}

			size_t size() const
			{
				return keys_.size();
			}

		private:
			std::vector<_Ty1> keys_;
			std::vector<_Ty2> values_;
	};
}

#endif // _CU_PAIR_LIST_
