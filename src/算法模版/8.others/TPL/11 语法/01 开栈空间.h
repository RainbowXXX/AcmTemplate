int main(void)
{
	int size(512 << 20); // 512M
	__asm__("movq %0, %%rsp\n" ::"r"((char *)malloc(size) + size));
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	Main();
	exit(0); // !!!
}