#include <stdio.h>
#include <string.h>

#include "cheat.h"
/************************************************************************/
/*                                                                      */
/************************************************************************/
CHEAT_TEST(mathematics_still_work,
	cheat_assert(2 + 2 == 4);
	cheat_assert_not(2 + 2 == 5);
)

CHEAT_DECLARE(
	static double f(double const x,
			double const y) {
		return 2 / (x * x) - y * y / 2;
	}

	static bool p(double const x,
			double const y,
			double const e) {
		double d;

		if (x < y)
			d = y - x;
		else /* Turbo C could not parse this without this comment. */
			d = x - y;
		return d <= e;
	}
)

CHEAT_TEST(physics_still_work,
	double xn = 3;
	double x0 = 1;
	size_t n = 128;
	double s;
	double y0 = 2;
	double y;
	size_t i;
	double x;

	s = (xn - x0) / (double )n;
	y = y0;
	for (i = 0;
			i <= n;
			++i) {
		x = x0 + s * (double )i;
		y += s * f(x, y);
	}

	cheat_assert(p(y, 1, 0.1));
)

CHEAT_DECLARE(
	extern size_t size;
)

CHEAT_DECLARE(
	size_t size;
	static char* heap;
)

CHEAT_SET_UP(
	char const* stack;

	(void )fputs("Setting up", stderr);

	stack = "string";
	size = strlen(stack) + 1;
	heap = CHEAT_CAST(char*, malloc(size));
	memcpy(heap, stack, size);
)

CHEAT_TEAR_DOWN(
	(void )fputs(" and tearing down.\n", stderr);

	free(heap);
)

CHEAT_TEST(philosophy_never_worked,
	char const* stack;

	stack = "string";
	cheat_assert(heap == stack);
	cheat_assert(strcmp(heap, stack) == 0);
)

CHEAT_TEST(test,
	(void )fputs(", running a test", stderr);
)

#ifndef OXYGEN_MOLECULE
#define OXYGEN_MOLECULE (0 == 0)
#endif

CHEAT_TEST(chemistry_is_strange,
	cheat_assert(OXYGEN_MOLECULE);
)

CHEAT_DECLARE(
	enum things {
		THIS_TEST CHEAT_COMMA
		IMPORTANT_TEST
	};
)

CHEAT_IGNORE(important,
	cheat_assert(THIS_TEST == IMPORTANT_TEST);
)

CHEAT_IGNORE(unimportant,
	cheat_assert(THIS_TEST != IMPORTANT_TEST);
)

CHEAT_SKIP(pointless,
	cheat_assert((0 | ~0) == 0);
)

CHEAT_TEST(story,
	(void )puts("Here's a touching story.");
	(void )puts("Once upon a time I ran a test.");
)

CHEAT_TEST(streams_get_captured,
	if (fopen(".PHONY", "r") == NULL) {
		(void )fwrite(" [\n", 1, 3, stderr);
		perror("fopen");
		(void )fputc(']', stderr);
	}
)

CHEAT_TEST(crash,
	(void )fputs(" and crashing.\n", stderr);

	((void (*)(void))NULL)();
)

CHEAT_TEST(the_end,
	(void )puts("The end.");
)

CHEAT_TEST(bye, ;)

/************************************************************************/
/*                                                                      */
/************************************************************************/

// int main(int argc, char* argv[])
// {
    
    // return 0;
// }