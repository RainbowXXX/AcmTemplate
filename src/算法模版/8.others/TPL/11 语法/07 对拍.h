// mine.cpp文件输入输出要关闭
#include <time.h>
void Solve(void)
{
	system("g++ -g mine.cpp -std=c++17 -o mine.exe");
	ll l, r;
	cin >> l >> r;
	FOR(i, l, r)
	{
		cout << endl
			 << "TestCase:" << i << endl;
		clock_t begin_time = clock();
		system(("mine.exe < std" + to_string(i) + ".in > mine" + to_string(i) + ".out").data());
		clock_t end_time = clock();
		cout << "time:" << static_cast<double>(end_time - begin_time) / CLOCKS_PER_SEC * 1000 << "ms" << endl;
		if (system(("fc std" + to_string(i) + ".out mine" + to_string(i) + ".out").data()))
		{
			cout << "WA:" << i << endl;
			system("pause");
		}
		else
			cout << "AC:" << i << endl;
	}
	system("pause");
	return;
}