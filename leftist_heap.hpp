//
// Created by Ubospica on 2021/5/13.
//

#ifndef PROJECT_LEFTIST_HEAP_HPP
#define PROJECT_LEFTIST_HEAP_HPP


#include "exception.hpp"

namespace HeapTest {
	template <typename T, typename Compare = std::less<T>>
	class LeftistHeap {
	private:
		int sz = 0;
		struct Node {
			T value;
			int dis = 0;
			Node *left = nullptr, *right = nullptr;
			friend std::ostream& operator<<(std::ostream &os, Node one) {
				os << "value = " << one.value << " left = " << one.left << " right = " << one.right;
				return os;
			}
		};
		Node *root = nullptr;
		
		static Node* _merge(Node *lhs, Node *rhs) {
			if (lhs == nullptr) {
				return rhs;
			} else if (rhs == nullptr) {
				return lhs;
			}
			if (lhs -> value < rhs -> value) {
				std::swap(lhs, rhs);
			}
			lhs -> right = _merge(lhs -> right, rhs);
			if (lhs -> left == nullptr) {
				std::swap(lhs -> left, lhs -> right);
				lhs -> dis = 0;
			} else if ((lhs -> left -> dis) < (lhs -> right -> dis)) {
				std::swap(lhs -> left, lhs -> right);
				lhs -> dis = lhs -> right -> dis + 1;
			}
			return lhs;
		}
		
		static void _destruct(Node *p) {
			if (p == nullptr) {
				return;
			}
			_destruct(p -> left);
			_destruct(p -> right);
			delete p;
		}
		
		void _print(Node *cur) {
			if (cur == nullptr) {
				return;
			}
			std::cerr << "cur = " << cur << " " << *cur << '\n';
			_print(cur->left);
			_print(cur->right);
		}
		
	public:
		LeftistHeap() = default;
		~LeftistHeap() {
			_destruct(root);
			root = nullptr;
		}
		void push(T val) {
			Node *node = new Node {val};
			root = _merge(root, node);
			++sz;
		}
		void pop() {
			if (empty()) {
				return;
//				throw container_is_empty();
			}
			root = _merge(root -> left, root -> right);
			--sz;
		}
		T top() const {
			if (empty()) {
				return T();
//				throw container_is_empty();
			}
			return root -> value;
		}
		void merge(LeftistHeap &ano) {
			if (&ano == this) {
				return;
			}
			root = _merge(root, ano.root);
			sz += ano.sz;
			ano.root = nullptr;
			ano.sz = 0;
		}
		bool empty() const {
			return root == nullptr;
		}
		int size() const {
			return sz;
		}
		
		void print() {
			std::cerr << "print root = " << root << '\n';
			_print(root);
			std::cerr << '\n';
		}
	};
}

#endif //PROJECT_LEFTIST_HEAP_HPP
