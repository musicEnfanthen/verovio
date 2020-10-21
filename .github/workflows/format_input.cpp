// adapted from https://gist.github.com/gelldur/d7bc3ea226aebcf8cc879df1e8524236

#include "a.h"

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <functional>
#include <iostream>
#include <iterator>

#include "b.h"
#include <lib/main.h>

//This should be 1 liner
class EmptyClass
{};

struct EmptyStruct
{}; // dummy comment

class NotEmptyClass
{
	int a;
};

template <class T>
class EmptyTemplate
{};

template <typename K, typename V = list<K>>
class hash
{};

void emptyFunction() {}

int emptyFunction2(int a) {}

void notEmptyFunction()
{
	auto oneLineLambda = []() {};
	oneLineLambda();

	auto oneLineLambda = [](int a) { print(a); };
	oneLineLambda();

	auto longLineLambda = [](int a, int b, int casfdasfasdfhasdkjfhaskdjfhkasdhfkashdfjkhaskfjhas) {
		print(a);
	};
	longLineLambda();
}

namespace EmptyNamespace
{
}

#if FOO
#	if BAR
#		include <foo>
#	endif
#endif

#define EXAMPLE                                                                                    \
	do                                                                                             \
	{                                                                                              \
		int x = aaaaa;                                                                             \
		int b;                                                                                     \
		int dddddddddd;                                                                            \
	} while(0)

template <typename T, int size>
bool is_sorted(T (&array)[size])
{
	return std::adjacent_find(array, array + size, std::greater<T>()) == array + size;
}

int sampleCallback(int a, int beforeCallMe)
{
	{
		{
			{
				{
					{
						{
							{
								{
									{
										{
											{
												{
													{
														{
															{
																{
																	{
																		{
																			{
																				{
																					int aaa =
																						bbbbbbbbbbbbbbb +
																						ccccccccccccccc;
																					return a *
																						   beforeCallMe;
																				}
																			}
																		}
																	}
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
}

namespace A
{
namespace B
{
namespace C
{
namespace D
{

int veryLongFunction(int anotherArgument,
					 int beforeCallMe,
					 bool isThisOkForYouMan,
					 std::vector<int> unknownValueForThisParameter)
{
	int a; // My comment a
	int b = 2; // comment  b
	return a * beforeCallMe;
}

//clang should restore comment if missing and remove everything afterwords
} // namespace D
} // namespace C
} // namespace B
} // namespace A

namespace A
{
namespace C
{
int veryLongFunctionAbcAASKJHGAKLSFNCJKASDNCUIABSALSKJDNKAJSHDKJASHDJHKJASDHKJAHBSD(
	int anotherArgument,
	int beforeCallMe,
	bool isThisOkForYouMan,
	std::vector<int> unknownValueForThisParameter)
{
	int a; // My comment a
	int b = 2; // comment  b
	return a * beforeCallMe;
}
} // namespace C
} // namespace A

int main()
{
	std::srand(std::time(0));

	int list[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

	do
	{
		std::random_shuffle(list, list + 9);
	} while(is_sorted(list));

	int score = 0;

	do
	{
		std::cout << "Current list: ";
		std::copy(list, list + 9, std::ostream_iterator<int>(std::cout, " "));

		int rev;
		while(true)
		{
			std::cout << "\nDigits to reverse? ";
			std::cin >> rev;
			if(rev > 1 && rev < 10)
			{
				break;
			}
			std::cout << "Please enter a value between 2 and 9.";
		}

		++score;
		std::reverse(list, list + rev);
	} while(!is_sorted(list));

	std::cout << "Congratulations, you sorted the list.\n"
			  << "You needed " << score << " reversals." << std::endl;

	auto dialog = PandemicDialog::create(i18n::tr("$QuitGameId"));
	dialog->addButton(
		i18n::tr("$OkId"), "common/green_frame.9.png", [this](PandemicDialog* dialog) {
			std::cout << "Congratulations, you sorted the list.\n"
					  << "You needed " << score << " reversals." << std::endl;
			inherited::onBack();
		});
	dialog->addButton(i18n::tr("$CancelId"),
					  "common/red_frame.9.png",
					  [this](PandemicDialog* dialog) { dialog->close(); });
	dialog->setTag(dialogTag);
	dialog->show(this);

	try
	{
		foo();
	}
	catch()
	{
		//empty catch
	}

	try
	{
		foo();
	}
	catch()
	{}

	return 0;
}

#define min(a, b) ((a) < (b) ? (a) : (b))

int doSomething(...);

int doSomethingElse(...)
{
	return 2;
}

struct Foo : private FooBase
{
public:
	int i;

	virtual int action(int, char, float) = 0;

	virtual Foo* getSelf()
	{
		return this;
	}

private:
	static int method(){};
	list<Bar> bar;
};

namespace fooNS
{
class FooClass : Foo, virtual FooBase
{
// comment start ar first column
#define FooClass_B FooBase

	typedef int (FooClass::*ACTION)(int);

public:
	FooClass()
	{
		act = &FooClass::nv_action;
	}

	virtual ~FooClass() {}

	int nv_action(int arg)
	{
		return arg;
	}

	virtual int action(int color, char alpha, float);

	virtual Foo* getSelf()
	{
		return Foo::getSelf();
	}

	int method()
	{
		return 0;
	}

	ACTION act;

private:
	int var;
};
} // namespace fooNS

int fooNS::FooClass::action(int color, char alpha, float)
{
	return doSomething(color);
}

namespace A
{
namespace B
{
typedef void(fn)(int i, int j, int k);

typedef void (*block)(int i, int j, int k);
} // namespace B
} // namespace A
typedef int X;

int& refTest(X&& x)
{
	int**& p = (int**&)x;
	int static& r = *&x;
	return r && (r & x) ? r : x;
}

// todo something
void doSomething(int y, int b, void* (*)())
{
	int a = 1 || 0 && 1;
	int bb = a == !1 && a != 0;
	int ccc = bb = a = 1 < 2 >= 3;
	int dddd = ccc = bb = a = ~1 | 2 & 3 ^ 4;

	void* p1 = reinterpret_cast<void*>(&a);
	void** p2 = &p1;

	a = bb = ccc = dddd = 2;
	dddd = ccc = bb = a = (1 + 2 + 3 + 4 + 5 + 0xFFFFFFFFF);

	int i5 = ((1) + 2) - (4 * 5 / 6 % 7);
	int i6 = -123456 << 2 >> 3 >> 12345;
	int i7 = 2 > 3 ? 7 + 8 + 9 : 11 + 12 + 13;
	int i8 = 2 < 3 + 7 + 8 + 9 ?: 11 + 12 + 13;
	int ii[6], jj[] = {1, 2, 3, 0x000A, 0x000B, 0x000C};

	fooNS::FooClass object, *ptr = (fooNS::FooClass*)object.getSelf()->getSelf()->getSelf();
	(object.*object.act)(1);
	ptr->action(0xFF0000, 0.01, 320);
	ptr->getSelf()->getSelf()->getSelf()->getSelf();

	doSomething(ii[1], jj[ii[2]], doSomething(123));

	if(1)
	{
		doSomething(1);
	}
	else if(2)
	{
		doSomething(1, 2);
	}
	if(1)
	{
		doSomething();
	}
	else if(2)
	{
		doSomething();
	}
	else
	{
		doSomething();
	}
	for(int i = 1, j = 2; i <= j; i++, j--)
	{
		doSomethingElse();
	}
	while(1)
	{
		doSomethingElse();
	}
	do
	{
		doSomethingElse();
	} while(1);
	switch(1)
	{
	case 0:
		return;
	case 1:
	{
		return;
	}
	}

	try
	{
		doSomethingElse();
	}
	catch(char* message)
	{
		return;
	}
}

struct fooS
{
	int i;
	char j;
} foo_t;

struct
{
	int i;
	char j;
} c_style_t;

enum class NotSingleLineEnum
{
	a
};

enum fooE
{
	SUNDAY = 111,
	MONDAY = 222,
	TUESDAY = 333,
	WEDNESDAY = TUESDAY + 1
} foo_e;

template <typename T, typename M>
inline T const& Min(T const& a, M const& b)
{
	return a < b ? a : b;
}

template <class T>
struct FooT
{
	hash<int, list<char>> elems;

	template <int N>
	int foo()
	{
		return N;
	}

	template <>
	int foo<2>()
	{
		return Min<>(1, 5);
	}

	list<int> mem = {1, 2, 3};
	float vector[3];

	FooT()
		: elems{{-1, {'c', 'p', 'p'}}, {1, {'j', 'b'}}}
		, vector{1f, 2f, 3f}
	{
		auto la = [=, this, &mem, elems](int i1, int i2) -> bool mutable { return i1 < i2; }(1, 2);
	}

	int a1, b1;

	FooT(int a)
		: a(1)
		, b(2)
	{
		auto la = [=, this, &mem, elems](int i1, int i2) -> bool mutable { return i1 < i2; }(1, 2);
	}

	auto f(T t) -> decltype(t + doSomething())
	{
		return t + doSomething();
	}
};

// No extra space before brace initialization
EmptyStruct emptyStruct = EmptyStruct {}; // otherwise: = EmptyStruct {};

//comment
EmptyStruct emptyStruct = EmptyStruct{};//1 space after ';'' otherwise: ;//1 space after...
