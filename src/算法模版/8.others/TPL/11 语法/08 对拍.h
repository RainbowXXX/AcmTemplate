// mine.cpp文件输入输出要关闭
#include <time.h>
void Solve(void)
{
	system("g++ -g gen.cpp -std=c++17 -o gen.exe");
	system("g++ -g std.cpp -std=c++17 -o std.exe");
	system("g++ -g mine.cpp -std=c++17 -o mine.exe");
	ll cnt;
	cin >> cnt;
	FOR(i, 1, cnt)
	{
		system("gen.exe > gen.in");
		system("std.exe < gen.in > std.out");
		clock_t begin_time = clock();
		system("mine.exe < gen.in > mine.out");
		clock_t end_time = clock();
		cout << "time:" << static_cast<double>(end_time - begin_time) / CLOCKS_PER_SEC * 1000 << "ms" << endl;
		if (system("fc std.out mine.out"))
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