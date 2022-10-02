#include "clap/clap.h"

uint8_t isPrime(size_t n)
{
	if (n < 2)
		return 0;

	size_t i = 2;

	while (i * i <= n)
	{
		if (n % i++ == 0)
			return 0;
	}

	return 1;
}

int main(int argc, char** argv)
{
	clapRegisterFlag("from", CLAP_FLAG_NO_SHORT, CLAP_FLAG_REQ_ARG, NULL);
	clapRegisterFlag("to", CLAP_FLAG_NO_SHORT, CLAP_FLAG_REQ_ARG, NULL);

	size_t from = 0;
	size_t to = 0;
	const char* non_opt = NULL;

	while (clapParse(argc, argv))
	{
		if (clapParsedFlag("from", CLAP_FLAG_NO_SHORT))
		{
			const char* arg = clapGetArg();
			from = atoi(arg);
		}

		if (clapParsedFlag("to", CLAP_FLAG_NO_SHORT))
		{
			const char* arg = clapGetArg();
			to = atoi(arg);
		}

		if (clapParsedNonOpt(&non_opt))
		{
			size_t n = atoi(non_opt);

			if (!n)
				continue;

			if (isPrime(n))
				printf("%zu is prime!\n", n);
			else
				printf("%zu is not prime.\n", n);
		}
	}

	if (!from && !to)
		return 0;

	if (from > to)
	{
		printf("Error: From can not be larger than to!\n");
		return 0;
	}

	printf("Prime numbers from %zu to %zu (inclusive) are:\n", from, to);

	for (size_t i = from; i <= to; i++)
	{
		if (isPrime(i))
			printf("%zu\n", i);
	}

	return 0;
}