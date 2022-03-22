#include<iostream>
int main() {
	char* str = (char*)"\u2588";

	printf("znak utf8 (printf): %s\n", str);
	std::cout << "znak utf8 (cout): " << str << std::endl;

	printf("4 bajty: ");
	size_t i{0}; while (1){printf("0x%.2x ",(uint8_t)str[i]); if(not str[i]) break;  ++i; };
	putchar('\n');

	printf("liczba uint32_t: 0x%.8x\n", *((uint32_t*)str));
	return 0;
}
