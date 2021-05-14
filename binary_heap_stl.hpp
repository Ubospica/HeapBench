//
// Created by Ubospica on 2021/5/13.
//

#ifndef PROJECT_BINARY_HEAP_STL_HPP
#define PROJECT_BINARY_HEAP_STL_HPP

#include "exception.hpp"
#include <vector>
#include <algorithm>

namespace HeapTest {
	template <typename T, typename Sequence = std::vector<T>, typename Comp = std::less<T>>
	class BinaryHeapSTL {
	private:
		Sequence val;
		Comp cmp;
	public:
		BinaryHeapSTL() = default;
		void push(T v) {
			val.push_back(v);
			std::push_heap(val.begin(), val.end(), cmp);
		}
		void pop() {
			if (empty()) {
				return;
//				throw container_is_empty();
			}
			std::pop_heap(val.begin(), val.end(), cmp);
			val.pop_back();
		}
		T top() const {
			if(empty()) {
				return T();
//				throw container_is_empty();
			}
			return val.front();
		}
		void merge(BinaryHeapSTL &ano) {
			return;
		}
		bool empty() const {
			return val.empty();
		}
		void clear() {
			val.clear();
		}
		int size() const {
			return val.size();
		}
	};
	
}

#endif //PROJECT_BINARY_HEAP_STL_HPP
