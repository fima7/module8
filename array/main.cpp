#include "Array.h"

#include <cassert>
#include <iostream>
#include <iomanip>

#define TEST(x) { x(); std::cerr << std::left << std::setw(30) << #x << " pass" << std::endl; } 


//
// Тесты для Array
//
/*
static Array test_pass_parameters(Array a) 
{
	return a;
}
*/

static void TestConstructors()
{

	{ // Инициялизация пустого массива
		Array<int> a;
		assert(a.GetSize() == 0);
	}

	{ // Инициялизация пустого массива
		Array<int> a{};
		assert(a.GetSize() == 0);
	}

	{ // Инициализация с параметром
		Array<int> a(10);

		assert(a.GetSize() == 10);

		for (int i = 0; i < 10; ++i) {
			a[i] = i;
		}


		for (int i = 0; i < a.GetSize(); ++i) {
			assert(a[i] == i);
		}
	}
		
	{ // Унифицированная инициализация
		Array<int> a{ 0, 1, 2, 3, 4, 5 };

		for (int i = 0; i < a.GetSize(); ++i) {
			assert(a[i] == i);
		}
	}

	{ // Инициализация копированием
		Array<int> a{ 0, 1, 2, 3, 4, 5 };
		Array<int> b = a;
		assert(a.GetSize() == b.GetSize());

		for (int i = 0; i < b.GetSize(); ++i) {
			assert(a[i] == b[i]);
		}
	}

	{ // Инициализация копированием
		Array<int> a{ 0, 1, 2, 3, 4, 5 };
		Array<int> b(a);
		assert(a.GetSize() == b.GetSize());

		for (int i = 0; i <b.GetSize(); ++i) {
			assert(a[i] == b[i]);
		}
	}

	{ // Инициализация копированием
		Array<int> a{ 0, 1, 2, 3, 4, 5 };
		Array<int> b{ a };
		assert(a.GetSize() == b.GetSize());

		for (int i = 0; i <b.GetSize(); ++i) {
			assert(a[i] == b[i]);
		}
	}

	/*
	{
		Array<int> a{ 0, 1, 2, 3, 4, 5 };
		Array<int> b = test_pass_parameters(a);
		assert(a.GetSize() == b.GetSize());

		for (int i = 0; i < b.GetSize(); ++i) {
			assert(a[i] == b[i]);
		}
	}
	*/

	{
		const Array<int> a{ 0, 1, 2, 3, 4, 5 };
		const int b = a[5];
		assert(b == 5);
	}

}

static void TestAssignment()
{
	{
		Array<int> a{ 1, 2, 3, 4, 5 };
		Array<int> b;

		b = a;

		assert(b.GetSize() == a.GetSize());

		for (size_t i = 0; i < b.GetSize(); ++i) {
			assert(b[i] == a[i]);
		}
	}

}

static void TestAccess()
{
	{
		Array<int> a{0, 1, 2, 3, 4, 5 };
		int v = a[5];
		assert(v == 5);
	}
	{
		try {
			Array<int> a{ 1, 2, 3, 4, 5 };
			std::cout << a[16] << std::endl;
			assert(false);
		} catch (OutOfRange&) {
			// std::cerr << "Exception: " << e.what() << std::endl;
		}
	}
	{
		try {
			Array<int> a(10000000000);
			assert(false);
		} catch (std::bad_alloc&) {
			// std::cerr << "Exception: " << e.what() << std::endl;
		}
	}
	{
		Array<int> a{ 1, 2, 3, 4, 5 };
		assert(a.GetFront() == 1);
	}
	{
		Array<int> a{ 1, 2, 3, 4, 5 };
		assert(a.GetBack() == 5);
	}

}

static void TestResize()
{
	{
		Array<int> a{ 0, 1, 2, 3, 4, 5 };
		Array<int> e{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		a.Resize(10);
		for (int i = 6; i < a.GetSize(); ++i) {
			a[i] = i;
		}

		assert(a == e);
	}

	{
		Array<int> a{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		Array<int> e{ 0, 1, 2, 3, 4, 5 };
	
		a.Resize(6);

		assert(a == e);
	}

}

static void TestInsert()
{

	{
		Array<int> a{ 0, 1, 2, 3, 4, 5 };
		Array<int> e{ 0, 8, 1, 2, 3, 4, 5 };

		a.Insert(8, 0);

		assert(a == e);
	}
	{
		Array<int> a{ 0, 1, 2, 3, 4, 5 };
		Array<int> e{ 0, 1, 8, 2, 3, 4, 5 };

		a.Insert(8, 1);

		assert(a == e);
	}
	{
		Array<int> a{ 0, 1, 2, 3, 4, 5 };
		Array<int> e{ 0, 1, 2, 8, 3, 4, 5 };

		a.Insert(8, 2);

		assert(a == e);
	}
	{
		Array<int> a{ 0, 1, 2, 3, 4, 5 };
		Array<int> e{ 0, 1, 2, 3, 8, 4, 5 };

		a.Insert(8, 3);

		assert(a == e);
	}
	{
		Array<int> a{ 0, 1, 2, 3, 4, 5 };
		Array<int> e{ 0, 1, 2, 3, 4, 8, 5 };

		a.Insert(8, 4);

		assert(a == e);
	}
	{
		Array<int> a{ 0, 1, 2, 3, 4, 5 };
		Array<int> e{ 0, 1, 2, 3, 4, 5, 8 };

		a.Insert(8, 5);

		assert(a == e);
	}
	{
		// Два блока try не нужны, использую только чтобы попрактиковаться

		std::string emsg("index 6 is out of 6");
		try {
			try {
				Array<int> a{ 0, 1, 2, 3, 4, 5 };
				a.Insert(8, 6);
				assert(false);
			} catch (std::out_of_range& e) {
				std::string msg(e.what());
				assert(msg == emsg);
				throw;
			}
			assert(false);
		} catch (std::exception& e) {
			std::string msg(e.what());
			assert(msg == emsg);
		}
	}

}

static void TestPushFront()
{
	{
		Array<int> a;
		Array<int> e{ 5 };
		a.PushFront(5);
		assert(a.GetFront() == 5);
		assert(a == e);
	}
	{

		Array<int> a{ 0, 1, 2, 3, 4, 5 };
		Array<int> e{ -2, -1, 0, 1, 2, 3, 4, 5 };

		a.PushFront(-1);
		assert(a.GetFront() == -1);

		a.PushFront(-2);
		assert(a.GetFront() == -2);
		
		assert(a == e);
	}

}

static void TestPushBack()
{

	{
		Array<int> a;
		Array<int> e{ 5 };

		a.PushBack(5);
		assert(a.GetBack() == 5);
		assert(a == e);
	}
	{

		Array<int> a{ 0, 1, 2, 3, 4, 5 };
		Array<int> e{ 0, 1, 2, 3, 4, 5, 6, 7 };

		a.PushBack(6);
		assert(a.GetBack() == 6);

		a.PushBack(7);
		assert(a.GetBack() == 7);
		
		assert(a == e);
	}

}

static void TestErase()
{

	{
		Array<int> a{ 0, 1, 2, 3, 4, 5 };
		Array<int> e{ 1, 2, 3, 4, 5 };
		a.Erase(0);
		assert(a == e);
	}
	{
		Array<int> a{ 0, 1, 2, 3, 4, 5 };
		Array<int> e{ 0, 2, 3, 4, 5 };
		a.Erase(1);
		assert(a == e);
	}
	{
		Array<int> a{ 0, 1, 2, 3, 4, 5 };
		Array<int> e{ 0, 1, 3, 4, 5 };
		a.Erase(2);
		assert(a == e);
	}
	{
		Array<int> a{ 0, 1, 2, 3, 4, 5 };
		Array<int> e{ 0, 1, 2, 4, 5 };
		a.Erase(3);
		assert(a == e);
	}
	{
		Array<int> a{ 0, 1, 2, 3, 4, 5 };
		Array<int> e{ 0, 1, 2, 3, 5 };
		a.Erase(4);
		assert(a == e);
	}
	{
		Array<int> a{ 0, 1, 2, 3, 4, 5 };
		Array<int> e{ 0, 1, 2, 3, 4 };
		a.Erase(5);
		assert(a == e);
	}

}

static void TestSort()
{
	{
		Array<int> a{ 5, 4, 3, 2, 1, 0 };
		Array<int> e{ 0, 1, 2, 3, 4, 5 };
		a.Sort();
		assert(a == e);
	}

	{
		Array<int> a{ 0, 1, 2, 3, 4, 5 };
		Array<int> e{ 0, 1, 2, 3, 4, 5 };
		a.Sort();
		assert(a == e);
	}

	{
		Array<int> a{ 5 };
		Array<int> e{ 5 };
		a.Sort();
		assert(a == e);
	}
	{
		Array<int> a{ 0, 1, 2, 3, 4, 5 };
		Array<int> e{ 5, 4, 3, 2, 1, 0 };
		a.RSort();
		assert(a == e);
	}

	{
		Array<int> a{ 5, 4, 3, 2, 1, 0 };
		Array<int> e{ 5, 4, 3, 2, 1, 0 };
		a.RSort();
		assert(a == e);
	}

	{
		Array<int> a{ 5 };
		Array<int> e{ 5 };
		a.RSort();
		assert(a == e);
	}

}

static void TestAllocation() 
{

#if 0 // зависит от машины	
	{
		try {
			Array<int> a(100'000'000'000);
			assert(false);
		} catch (std::bad_alloc&) {
		}
	}
	{
		Array<int> a;
		try {
			a.Resize(100'000'000'000);
			assert(false);
		} catch (std::bad_alloc&) {
		}
	}
	{
		Array<int> a;
		try {
			Array<int> a(4'000'000'000);
			for (size_t i = 0; i < 1'000'000; ++i) {
				a.PushFront(i);
			}
			assert(false);
		} catch (std::bad_alloc&) {
		}
	}
	{
		Array<int> a;
		try {
			Array<int> a(4'000'000'000);
			for (size_t i = 0; i < 1'000'000; ++i) {
				a.PushBack(i);
			}
			assert(false);
		} catch (std::bad_alloc&) {
		}
	}
#endif

}

struct MyType
{
	std::string name;
	int value = 0;
};

bool operator==(const MyType& lhs, const MyType& rhs)
{
	return (lhs.name == lhs.name) && (rhs.value == rhs.value);
}

bool operator!=(const MyType& lhs, const MyType& rhs)
{
	return !(lhs == rhs);
}

void TestObject()
{
	{
		Array<MyType> a{ {"first", 1}, { "second", 2 }, { "third", 3 }, { "forth", 4 }, { "five", 5 } };
		Array<MyType> e{ {"first", 1}, { "second", 2 }, { "third", 3 }, { "forth", 4 }, { "five", 5 } };
		assert(a == e);
	}
	{
		Array<MyType> a{ {"first", 1}, { "second", 2 }, { "third", 3 }, { "forth", 4 }, { "five", 5 } };
		Array<MyType> e{ { "second", 2 }, { "third", 3 }, { "forth", 4 }, { "five", 5 } };

		a.Erase(0);

		assert(a == e);
	}
}

int main()
{

	TEST(TestConstructors);
	TEST(TestAssignment);
	TEST(TestAccess);
	TEST(TestResize);
	TEST(TestInsert);
	TEST(TestPushFront);
	TEST(TestPushBack);
	TEST(TestErase);
	TEST(TestSort);
	TEST(TestAllocation);
	TEST(TestObject);

	return 0;

} 