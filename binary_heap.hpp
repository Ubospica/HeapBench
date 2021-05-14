//
// Created by Ubospica on 2021/5/12.
//

#ifndef PROJECT_BINARY_HEAP_HPP
#define PROJECT_BINARY_HEAP_HPP

#include "exception.hpp"
#include <vector>
#include <algorithm>

namespace HeapTest {
	template<typename RandomAccessIterator,
			typename Comp = std::less<decltype(RandomAccessIterator::operator*())>>
	void my_push_heap(RandomAccessIterator first, RandomAccessIterator last,
				const Comp &cmp = std::less<decltype(RandomAccessIterator::operator*())>()) {
		auto dis = std::distance(first, last) - 1;
		auto parent = (dis - 1) / 2;
		decltype(dis) root = 0;
		auto val = std::move(*(last - 1));
		
		while(root < dis && cmp(*(first + parent), val)) {
			*(first + dis) = std::move(*(first + parent));
			dis = parent;
			parent = (dis - 1) / 2;
		}
		*(first + dis) = std::move(val);
	}
	
	template<typename RandomAccessIterator,
			typename Comp = std::less<decltype(RandomAccessIterator::operator*())>>
	void my_pop_heap(RandomAccessIterator first, RandomAccessIterator last,
	              const Comp &cmp = std::less<decltype(RandomAccessIterator::operator*())>()) {
		auto dis = std::distance(first, last) - 1;
		if(dis == 0) {
			return;
		}
		else if (dis == 1) {
			std::swap(*(first), *(last - 1));
			return;
		}
		
		auto val = std::move(*(last - 1));
		*(last - 1) = std::move(*first);
		decltype(dis) pl = 0;
		
		auto child = 2 * pl + 1;
		if (child + 1 < dis && cmp(*(first + child), *(first + child + 1))) {
			++child;
		}
		
		while(cmp(val, *(first + child))) {
			*(first + pl) = std::move(*(first + child));
			pl = child;
			child = child * 2 + 1;
			if (child >= dis) {
				break;
			}
			if (child + 1 < dis && cmp(*(first + child), *(first + child + 1))) {
				++child;
			}
		}
		*(first + pl) = std::move(val);
	}
	
	template <typename T, typename Sequence = std::vector<T>, typename Comp = std::less<T>>
	class BinaryHeap {
	private:
		Sequence val;
		Comp cmp;
	public:
		BinaryHeap() :val() {}
		void push(T v) {
			val.push_back(v);
			my_push_heap(val.begin(), val.end(), cmp);
//			for (auto i : val) std::cerr << i << ' ';
//			std::cerr << "push end\n";
		}
		void pop() {
			if (empty()) {
				return;
//				throw container_is_empty();
			}
			my_pop_heap(val.begin(), val.end(), cmp);
			val.pop_back();
//			for (auto i : val) std::cerr << i << ' ';
//			std::cerr << "pop end\n";
		}
		T top() const {
			if (empty()) {
				return T();
//				throw container_is_empty();
			}
			return val.front();
		}
		void merge(BinaryHeap &ano) {
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

#endif //PROJECT_BINARY_HEAP_HPP
