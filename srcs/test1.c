#include <unistd.h>
#include <stdio.h>

int main()
{
	write(1, "1234567890", 10);
	write(1, "\033[6n", 4);
}
