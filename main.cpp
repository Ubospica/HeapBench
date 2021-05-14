#include <iostream>
#include <fstream>
#include <random>
#include <sys/time.h>

#include "binary_heap.hpp"
#include "binary_heap_stl.hpp"
#include "pairing_heap.hpp"
#include "leftist_heap.hpp"

using namespace HeapTest;

int randBetween(int l, int r) {
//	static std::random_device rd;
//	static std::mt19937_64 rnd(rd());
//	std::uniform_int_distribution<long long> distribution(l,r);
//	return distribution(rnd);
	return l + rand() % (r - l + 1);
}

void generate1() {
	char filename[100];
	int bound = 3, heapCnt = 0;
	for(int size = 1; size <= 10; ++size) {
		bound <<= 2;
		for (int cnt = 1; cnt <= 10; ++cnt) {
			sprintf(filename, "a%d_%d.in", size, cnt);
			freopen(filename, "w", stdout);
			std::cout << bound << " 1\n";
			for (int i = 1; i <= bound; ++i) {
				int fl = randBetween(1, 3);
				std::cout << fl << " 1 ";
				//1 push 2 pop 3 top
				if (fl == 1) {
					std::cout << randBetween(1, 1e9);
				}
				std::cout << '\n';
			}
		}
		std::cerr << "generate file 1 " << size << '\n';
	}
}

void generate2() {
	char filename[100];
	int bound = 3, heapCnt = 0;
	for(int size = 1; size <= 10; ++size) {
		bound <<= 2;
		heapCnt = std::max(bound / 1000, 5);
		for (int cnt = 1; cnt <= 10; ++cnt) {
			sprintf(filename, "b%d_%d.in", size, cnt);
			freopen(filename, "w", stdout);
			std::cout << bound << " " << heapCnt << "\n";
			for (int i = 1; i <= bound; ++i) {
				int fl = randBetween(1, 4);
				std::cout << fl << ' ' << randBetween(1, heapCnt) << ' ';
				//1 push 2 pop 3 top 4 merge
				if (fl == 1) {
					std::cout << randBetween(1, 1e9);
				}
				else if (fl == 4) {
					std::cout << randBetween(1, heapCnt);
				}
				std::cout << '\n';
			}
		}
		std::cerr << "generate file 2 " << size << '\n';
	}
}

void generate3() {
	char filename[100];
	int bound = 3, heapCnt = 0;
	for(int size = 1; size <= 10; ++size) {
		bound <<= 2;
		heapCnt = std::max(bound / 1000, 5);
		for (int cnt = 1; cnt <= 10; ++cnt) {
			sprintf(filename, "c%d_%d.in", size, cnt);
			freopen(filename, "w", stdout);
			std::cout << bound << " " << heapCnt << "\n";
			for (int i = 1; i <= bound; ++i) {
				int fl;
				if (randBetween(1, 1000) >= 975) {
					fl = 2;
				}
				else {
					fl = randBetween(1, 3);
					if (fl == 2) {
						fl=4;
					}
				}
				
				std::cout << fl << ' ' << randBetween(1, heapCnt) << ' ';
				//1 push 2 pop 3 top 4 merge
				if (fl == 1) {
					std::cout << randBetween(1, 1e9);
				}
				else if (fl == 4) {
					std::cout << randBetween(1, heapCnt);
				}
				std::cout << '\n';
			}
		}
		std::cerr << "generate file 3 " << size << '\n';
	}
}

int input[6000000][4];

template <typename Heap, int flag>
void test(char *name, char *preName = nullptr) {
	char recordName[100];
	sprintf(recordName, "%s.csv", name);
	FILE *record = fopen(recordName, "w");
	struct timeval t1, t2;
	
	for (char c = 'a'; c <= 'c'; ++c) {
		for (int i = 1; i <= 10; ++i) {
			for (int j = 1; j <= 10; ++j) {
				char filename[100], outFilename[100], command[100];
				sprintf(filename, "%c%d_%d.in", c, i, j);
				sprintf(outFilename, "%c%d_%d_%s.out", c, i, j, name);
				
//				freopen(filename, "r", stdin);
//				freopen(outFilename, "w", stdout);
				
				std::ios::sync_with_stdio(0), std::cin.tie(0), std::cout.tie(0);
				std::ifstream ifs(filename);
				std::ofstream ofs(outFilename);
				std::cin.rdbuf(ifs.rdbuf());
				std::cout.rdbuf(ofs.rdbuf());
				
				
				int bound, heapCnt, fl, heap1, heap2, val;
				std::cin >> bound >> heapCnt;
				for (int a = 1; a <= bound; ++a) {
					std::cin >> input[a][0] >> input[a][1];
					if (input[a][0] == 1 || input[a][0] == 4) {
						std::cin >> input[a][2];
					}
				}
				
				gettimeofday(&t1, nullptr);
				
				Heap *hp = new Heap[heapCnt + 1]();
				
				for (int a = 1; a <= bound; ++a) {
//					std::cin >> fl >> heap1;
					fl = input[a][0], heap1 = input[a][1];
					if (fl == 1) {
//						std::cin >> val;
						val = input[a][2];
						hp[heap1].push(val);
					}
					else if (fl == 2) {
						hp[heap1].pop();
					}
					else if (fl == 3) {
//						std::cout << hp[heap1].top() << '\n';
						input[a][3] = hp[heap1].top();
					}
					else if (fl == 4){
//						std::cin >> heap2;
						heap2 = input[a][2];
						if (flag == 0) {
							continue;
						}
						hp[heap1].merge(hp[heap2]);
					}
				}
				delete[] hp;
				
				gettimeofday(&t2, nullptr);
				
//				for (int a = 1; a <= bound; ++a) {
//					if (input[a][0] == 3) {
//						std::cout << input[a][3] << '\n';
//					}
//				}
				
				double difftime = (double)(t2.tv_sec - t1.tv_sec) * 1000.0
						+ (double)(t2.tv_usec - t1.tv_usec) / 1000.0;
				fprintf(record, "%.3lf, ", difftime);
//				fclose(stdout);
//				std::cout.flush();
//				if (preName != nullptr){
//					sprintf(command, "diff -s %s %c%d_%d_%s.out\n", outFilename, c, i, j, preName);
//					system(command);
//				}
			}
			fprintf(record, "\n");
			fprintf(stderr, "%s %c %d end\n", name, c, i);
		}
		fprintf(record, "\n");
	}
	fclose(record);
}


int main() {
	srand(time(0));
	generate1();
	generate2();
	generate3();
	test<BinaryHeap<int>, 0>("BH");
	test<BinaryHeapSTL<int>, 0>("BHS", "BH");
	test<LeftistHeap<int>, 1>("LH");
	test<PairingHeap<int>, 1>("PH", "LH");
	return 0;
}
