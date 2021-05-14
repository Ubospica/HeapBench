//
// Created by Ubospica on 2021/5/13.
//

#ifndef PROJECT_PAIRING_HEAP_HPP
#define PROJECT_PAIRING_HEAP_HPP

#include "exception.hpp"

namespace HeapTest {
	
	template<typename T, class Compare = std::less<T>>
	class PairingHeap {
	private:
		int sz = 0;
		struct Node {
			T value;
			Node *son = nullptr, *sibling = nullptr;
			friend std::ostream& operator<<(std::ostream &os, Node one) {
				os << "value = " << one.value << " sibling = " << one.sibling << " son = " << one.son;
				return os;
			}
		};
		Node *root = nullptr;
		
		Node *_merge(Node *ptr1, Node *ptr2) {
			if (ptr1 == nullptr) return ptr2;
			if (ptr2 == nullptr) return ptr1;
			
			if (Compare()(ptr1 -> value, ptr2 -> value)) {
				std::swap(ptr1, ptr2);
			}
			ptr2 -> sibling = ptr1 -> son;
			ptr1 -> son = ptr2;
			return ptr1;
		}
		
		Node *_pop() {
			if (root == nullptr) {
				return nullptr;
			}
//		std::cerr << "pop root = " << root << " " << *root << '\n';
//		std::cerr.flush();
			Node *son1 = root -> son;
			if (son1 == nullptr) {
				root = nullptr;
				return root;
			}
			Node *son2 = son1 -> sibling;
			root -> son = (son2 == nullptr ? nullptr : son2 -> sibling);
			son1 -> sibling = nullptr;
			if (son2 != nullptr) son2 -> sibling = nullptr;
			root = _merge(_merge(son1, son2), _pop());
			return root;
		}
		
		void _destruct(Node *&ptr) {
			if (ptr == nullptr) {
				return;
			}
//		std::cerr << "destruct " << ptr << " " << *ptr << '\n' << std::flush;
			_destruct(ptr -> son);
			_destruct(ptr -> sibling);
			delete ptr;
			ptr = 0;
		}
		
		Node *_duplicate(Node *other) {
			if (other == nullptr) {
				return nullptr;
			}
//		std::cerr << "copy " << other << " " << *other << '\n' << std::flush;
			Node *cur = new Node(*other);
//		std::cerr << "copy result " << cur << '\n';//<< " " << *cur << '\n' << std::flush;
			
			cur -> son = _duplicate(other -> son);
			cur -> sibling = _duplicate(other -> sibling); //
			return cur;
		}
		
		void _print(Node *cur) {
			if (cur == nullptr) {
				return;
			}
			std::cerr << "cur = " << cur << " " << *cur << '\n';
			_print(cur->sibling);
			_print(cur->son);
		}
	
	public:
		/**
		 * TODO constructors
		 */
		PairingHeap() = default;
		PairingHeap(const PairingHeap &other) {
			root = _duplicate(other.root);
			sz = other.sz;
		}
		/**
		 * TODO deconstructor
		 */
		~PairingHeap() {
//		std::cerr << "destructor rt = " << root << '\n';
			_destruct(root);
			root = nullptr;
			sz = 0;
		}
		/**
		 * TODO Assignment operator
		 */
		PairingHeap &operator=(const PairingHeap &other) {
			if (&other == this) {
				return *this;
			}
			_destruct(root);
			root = _duplicate(other.root);
			sz = other.sz;
			return *this;
		}
		/**
		 * get the top of the queue.
		 * @return a reference of the top element.
		 * throw container_is_empty if empty() returns true;
		 */
		T top() const {
			if (empty()) {
				return T();
//				throw container_is_empty();
			}
			return root -> value;
		}
		/**
		 * TODO
		 * push new element to the priority queue.
		 */
		void push(const T &e) {
			++sz;
			Node *newNd = new Node ({e, nullptr, nullptr});
			root = _merge(root, newNd);
//			std::cerr << "push end\n";
//			print();
		}
		/**
		 * TODO
		 * delete the top element.
		 * throw container_is_empty if empty() returns true;
		 */
		void pop() {
			if (empty()) {
				return;
//				throw container_is_empty();
			}
			--sz;
			Node *ptr = root;
			root = _pop();
			delete ptr;
//			std::cerr << "pop end\n";
//			print();
		}
		/**
		 * return the number of the elements.
		 */
		size_t size() const {
			return sz;
		}
		/**
		 * check if the container has at least an element.
		 * @return true if it is empty, false if it has at least an element.
		 */
		bool empty() const {
			return sz == 0;
		}
		/**
		 * return a merged priority_queue with at least O(logn) complexity.
		 */
		void merge(PairingHeap &other) {
			if (&other == this) {
				return;
			}
			root = _merge(root, other.root);
			sz += other.sz;
			other.sz = 0;
			other.root = nullptr;
		}
		
		void print() {
			std::cerr << "print root = " << root << '\n';
			_print(root);
			std::cerr << '\n';
		}
	};
}

#endif //PROJECT_PAIRING_HEAP_HPP
