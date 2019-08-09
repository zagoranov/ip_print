#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <tuple>

/// <summary>
/// Integral types 
/// </summary>
template<class T, typename std::enable_if_t<std::is_integral<T>::value>* = nullptr>
void print_ip(const T t) {
	for (int i = sizeof(T) - 1; i >= 0; --i) {
		std::cout << ((t >> (8 * i)) & 0xff);
		if (i != 0)
			std::cout << ".";
	}
	std::cout << std::endl;
}


/// <summary>
/// String simple overloading
/// </summary>
void print_ip(std::string const& t)
{
	std::cout << t << std::endl;
}

/// <summary>
/// Containers specialization
/// </summary>
template <typename T, typename = typename T::iterator>
void print_ip(T container)
{
	for (auto& value : container) {
		std::cout << value << ".";
	}
	std::cout << std::endl;
}

/// <summary>
/// Tuple overloading
/// </summary>
template<std::size_t I = 0, typename... Tp>
inline typename std::enable_if_t<I == sizeof...(Tp), void> print_ip(std::tuple<Tp...>& t)
{
	std::cout << std::endl;
}
template<std::size_t I = 0, typename... Tp>
inline typename std::enable_if_t<I < sizeof...(Tp), void> print_ip(std::tuple<Tp...>& t) {
	std::cout << std::get<I>(t);
	if (I + 1 != sizeof...(Tp)) std::cout << ".";
	print_ip<I + 1, Tp...>(t);
}


int main()
{
	/// Base checks
	char ch = -1;
	print_ip(ch);
	short sh = 0;
	print_ip(sh);
	int inin = 2130706433;
	print_ip(inin);
	long long lolo = 8875824491850138409;
	print_ip(lolo);

	/// String checks
	std::string qq = "127.127.127.001";
	print_ip(qq);

	/// Containers checks
	std::vector<int> q_vector = { 127, 10, 12, 42 };
	print_ip(q_vector);
	std::list<int> q_list = { 127, 42, 42, 10 };
	print_ip(q_list);

	/// Tuple checks	
	auto zz = std::make_tuple(127, 127, 10, 11);
	print_ip(zz);

}
