#include <iostream>
#include <typeinfo>

using namespace std;

void display(int* arr, size_t size)
{
	cout << arr[0];
	for (auto i = 1u; i < size; ++i)
		cout << ", " << arr[i];
	cout << endl;
}

enum class Order { ASC, DESC };
class Comparator	// Functor: Function class!
{
public:
	Order m_order = Order::ASC;
	bool operator()(int a, int b)
	{
		cout << "operator()\n";
		if (m_order == Order::ASC)
			return a > b; // Return a boolean value!
		else
			return a < b;
	}
};

bool asc(int a, int b)
{
	// Should the values be switched?
	return a > b;
}

bool desc(int a, int b)
{
	return a < b;
}

template<typename T>
void bubbleSort(int* arr, size_t n, T cmp) // 3rd argument is template
{
	for (auto i = 0u; i < n - 1; ++i)
		for (auto j = i + 1; j < n; ++j)
			if (cmp(arr[i], arr[j])) // Should I switch them?
			{
				// switch
				auto tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
}

int main()
{
	Comparator cmpFO;	// This instance can be used like a function!
	bool (*cmpF)(int, int) = nullptr; // pointer to a function that returns bool.

	// Lambda expression
	string str = "Hello";
	auto cmpL = [=, &str](int a, int b) -> bool	// [=] Catches all vars.
	{
		// cout << "A: " << a << " B: " << b << "   " << str << endl;
		str += " 1";
		return a > b;
	};
	
	cout << typeid(cmpL).name() << endl;
	// cout << str << endl; // str not changed yet

	bool res = cmpL(3, 9);	// Catch the result in a bool variable.

	// cout << "Should I switch? " << cmpFO(12, 9) << endl;

	cout << str << endl; // str has been changed
	
#pragma region Users_Choice
	char choice = '\0';
	cout << "Asc/Desc?: ";
	cin >> choice;

	if (choice == 'a')
	{
		cmpFO.m_order = Order::ASC;
		cmpF = asc;
	}
	else
	{
		cmpFO.m_order = Order::DESC;
		cmpF = desc;
	}
#pragma endregion

	int arr[]{ 4, 6, 98, 1, -5, 5, 78 };
	display(arr, sizeof(arr) / sizeof(arr[0]));

	/*bubbleSort(arr, 7, cmpF);
	bubbleSort(arr, 7, cmpFO);*/
	
	bubbleSort(arr, 7, cmpL);
	display(arr, 7);
}