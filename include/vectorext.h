#ifndef VECTOREXT_H
#define VECTOREXT_H

#include <algorithm>
#include <vector>

template <typename T> void append(std::vector<T> &vec, const T element) {
		vec.push_back(element);
		}

template <typename T> void appendIfUnique(std::vector<T> &vec, const T element) {
	/*
	typedef typename std::vector<T>::iterator It;
	It it = std::find(vec.begin(), vec.end(), element);
	if (it != vec.cend()) {
		vec.push_back(element);
		}
	*/
	ptrdiff_t pos = find(vec.begin(), vec.end(), element) - vec.begin();
	if (pos >= int(vec.size())) {
		vec.push_back(element);
		}
	}

template <typename T>
	void removeDuplicates(std::vector<T> &vec){
		// https://stackoverflow.com/a/32172811
		typedef typename std::vector<T>::iterator It; // It is the name of a type
		It it = std::unique(vec.begin(), vec.end());
		vec.erase(it, vec.end());                     // uses aschepler's suggestion
		}

template <typename T>
	signed int findItem(const std::vector<T> &vec, const T &element) {
		/*
		//auto it = std::find(vec.begin(), vec.end(), element);
		std::vector<ptrdiff_t>::iterator it = std::find(vec.begin(), vec.end(), element);
		if (it != vec.cend()) {
			return std::distance(vec.begin(), it);
			} else {return -1;}
		*/
		// https://stackoverflow.com/a/15099748
		ptrdiff_t pos = find(vec.begin(), vec.end(), element) - vec.begin();
		if (pos < int(vec.size())) {
			return pos;
			} else {return -1;}
		}

template <typename T>
	class to_vector {
		public:
		typedef to_vector<T> my_type;
		my_type& operator<< (const T& val) {
			data_.push_back(val);
			return *this;
			}
		operator std::vector<T>() const {
			return data_;
			}
		private:
		std::vector<T> data_;
		};


#endif // VECTOREXT_H
