#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <list>
#include <tuple>


/// <summary>
/// Global template func (used for string)
/// </summary>
template<typename T>
std::string print_ip(T v) {
	return v;
};

/// <summary>
/// Specification for char
/// </summary>
template<>
std::string print_ip<char>(char v) {
	unsigned char ch = v;
	return std::to_string(ch);
};

template<>
std::string print_ip<short>(short v) {
		return print_ip<char>((v & 0xFF00) >> 8) + "." + print_ip<char>(v & 0x00FF);
};

template<>
std::string print_ip<int>(int v) {
	return print_ip<short>((v & 0xFFFF0000) >> 16) + "." + print_ip<short>(v & 0x0000FFFF);
};

template<>
std::string print_ip<long long>(long long v) {
	return print_ip<int>((v & 0xFFFFFFFF00000000) >> 32) + "." + print_ip<int>((v & 0x00000000FFFFFFFF));
};

/// <summary>
/// Overloading for containers
/// </summary>
std::string print_ip(std::vector<int> &v) {
	std::string s = "";
	for (auto it = v.begin(); it != v.end(); ++it) {
		s += std::to_string(*it);
		if (it != v.end()-1)
			s += ".";
	}
	return s;
};

std::string print_ip(std::list<int> &v) {
	std::string s = "";
	if (v.size() > 0) {
		for (auto vv : v)
			s += std::to_string(vv) + ".";
		s = s.substr(0, s.size() - 1);
	}
	return s;
};

/// <summary>
/// Overloading tuples
/// </summary>
template<std::size_t I = 0, typename... Tp>
inline typename std::enable_if<I == sizeof...(Tp), void>::type
print_ip(std::tuple<Tp...>& t)
{ }

template<std::size_t I = 0, typename... Tp>
inline typename std::enable_if<I < sizeof...(Tp), void>::type
	print_ip(std::tuple<Tp...>& t) {
		std::cout << std::get<I>(t);
		if(I + 1 != sizeof...(Tp)) std::cout << ".";
		print_ip<I + 1, Tp...>(t);
	}


int main()
{	
	/// Base checks
	std::cout << print_ip<char>(-1) << std::endl;
	std::cout << print_ip<short>(0) << std::endl;
	std::cout << print_ip(2130706433) << std::endl; 
	std::cout << print_ip(8875824491850138409) << std::endl;

	/// String check
	std::cout << print_ip("127.127.127.001") << std::endl; 

	/// Containers checks
	std::vector<int> q_vector = {127, 10, 10, 42};
	std::cout << print_ip(q_vector) << std::endl;
	std::list<int> q_list = { 127, 42, 42, 10 };
	std::cout << print_ip(q_list) << std::endl;

	/// Tuple checks	
	auto zz = std::make_tuple(127, 127, 10, 10);
	print_ip(zz);

}

