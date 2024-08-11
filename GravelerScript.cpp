#include <thread>
#include <iostream>
#include <vector>
#include <random>
#include <future>
using namespace std;

int doSomething(int numberOfOperations) {
	int highest = 0;
	int n = 0;
	int t = 0;
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist4(1, 4); // distribution in range [1, 4]
	for (t = 0; t <= numberOfOperations;++t) {
		int safeTurns = 54;
		int paralysisProcs = 177;
		for (n = 0; n <= paralysisProcs;++n) {
			int temp = dist4(rng);
			if (temp == 1) {
				continue;
			}
			else {
				--safeTurns;
			}
			if (safeTurns <= 0) {
				break;
			}
		}
		if (n > highest) {
			highest = n;
		}
	}

	return highest;
}



void spawnThreads(int n, int operationsPerThread)
{
	int maxOnes = 0;
	using Future = std::future<int>;
	std::vector<Future> futures;
	for (int i = 0; i < n; i++) {
		auto fut = std::async(std::launch::async, doSomething, operationsPerThread);
		futures.push_back(std::move(fut));
	}

	for (auto& th : futures) {

		int temp = th.get();
		if (temp > maxOnes) {
			maxOnes = temp;
		}
	}
	std::cout << "Max Ones: ";
	std::cout << maxOnes;
	std::cout << "\n";
}

int main()
{
	const clock_t begin_time = clock();
	std::cout << "Generation Started\n";
	//spawnThreads(32, 31250); //32*31250 =  1 000 000
	spawnThreads(32, 31250000); //32 * 31 250 000 =  1 000 000 000
	std::cout << "Generation Finished\n";
	std::cout << (float(clock() - begin_time) / CLOCKS_PER_SEC);
	std::cout << " seconds";
}