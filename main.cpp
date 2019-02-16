#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <tuple>


/// <summary>
/// integral types printing
/// </summary>
namespace print_int {

	std::string print_(char v) {
		unsigned char ch = v;
		return std::to_string(ch);
	}

	std::string print_(short v) {
		char qq = (v & 0xFF00) >> 8;
		return print_((char)qq) +
			"." +
			print_((char)(v & 0x00FF));
	}

	std::string print_(int v) {
		short qq = (v & 0xFFFF0000) >> 16;
		return print_(qq) + "." + print_((short)(v & 0x0000FFFF));
	}

	std::string print_(long long v) {
		int qq = (v & 0xFFFFFFFF00000000) >> 32;
		return print_(qq) + "." + print_((int)(v & 0x00000000FFFFFFFF));
	}
}

/// <summary>
/// integral types specialization
/// </summary>
template<class T, typename std::enable_if<std::is_integral<T>::value>::type* = nullptr>
	void print_ip(const T& t)
{
	std::cout << print_int::print_(t) << std::endl;
}

/// <summary>
/// Containers specialization
/// </summary>
template <typename T, typename = typename T::iterator>
void print_ip(T container)
{
	for (auto value : container)
		std::cout << value << " ";
	std::cout << std::endl;
}

/// <summary>
/// String specialization
/// </summary>
template<class T, typename std::enable_if<std::is_same<T, std::string>::value>::type* = nullptr>
void print_ip(std::string t)
{
	std::cout << t << std::endl;
}

/// <summary>
/// Tuple specialization
/// </summary>
template<std::size_t I = 0, typename... Tp>
inline typename std::enable_if<I == sizeof...(Tp), void>::type
print_ip(std::tuple<Tp...>& t)
{ 
	std::cout << std::endl;
}

template<std::size_t I = 0, typename... Tp>
inline typename std::enable_if<I < sizeof...(Tp), void>::type
	print_ip(std::tuple<Tp...>& t) {
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
