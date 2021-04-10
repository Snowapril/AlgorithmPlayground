#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include <limits>
using namespace std;

int main()
{
	mt19937 rng;
	uniform_int_distribution<int> dist(1, (numeric_limits<int>::max() >> 1));
	
	//! 2^8 부터 2^15 까지 돌려보는 loop
	for (int i = 8; i <= 15; ++i)
	{
		size_t num = pow(2, i);
		
		vector<int> arr(num);
		//! arr[0] ~ arr[num - 1] 까지 random integer로 채우는 코드
		generate(arr.begin(), arr.end(), [&rng, &dist]() {
			return dist(rng);
		});

		//! sorting하고 unique element제거
		sort(arr.begin(), arr.end());
		auto last = unique(arr.begin(), arr.end());
		arr.erase(last, arr.end());
		num = arr.size();

		//! 이제 두 method 성능 비교
		cout << "compare two method with #elements : " << num << endl;
		
		//! method1. 
		auto start = chrono::high_resolution_clock::now();
		for (int i = 0; i < num - 2; ++i) //! O(N)
		{
			for (int j = i + 1; j < num - 1; ++j) //! O(N)
			{
				//! Binary search O(logN)
				const int targetNum = arr[i] + arr[j];
				auto iter = lower_bound(arr.begin() + j + 1, arr.end(), targetNum);
				if (iter != arr.end() && targetNum == *iter)
				{
					//! Do stuff with i, j and searched iter
					cout << arr[i] << " + " << arr[j] << " = " << *iter << endl;
				}
			} //! O(NlogN)
		} //! O(N^2logN)
		cout << "method1 takes : " << chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start).count()
								   << "(ms)" << endl;

		//! method 2
		start = chrono::high_resolution_clock::now();
		for (int k = num - 1; k >= 2; --k)
		{
			bool bFound = false;
			int i = 0, j = k - 1;
			while (i != j)
			{
				if (arr[i] + arr[j] > arr[k])
					--j;
				else if (arr[i] + arr[j] < arr[k])
					++i;
				else //! this mean arr[i] + arr[j] == arr[k]
				{
					bFound = true;
					break;
				}
			}
			if (bFound)
			{
				//! Do stuff with i, j, k
				cout << arr[i] << " + " << arr[j] << " = " << arr[k] << endl;
			}
		}
		cout << "method2 takes : " << chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start).count()
			<< "(ms)\n" << endl;
	}
}