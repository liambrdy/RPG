#include <spdlog/spdlog.h>

int main()
{
	spdlog::info("Hello {0}", "World");

	return 0;
}