
#ifndef ip_print_h
#define ip_print_h

#include <iostream>
#include <string>
#include <type_traits>
#include <vector>
#include <list>
#include <tuple>
#include <utility>


template< typename T >
using IsString = std::enable_if_t< std::is_same_v<T,std::string>, bool >;

template< typename T >
using IsInt8T = std::enable_if_t< std::is_same_v<T,int8_t>, bool >;

template< typename T >
using IsInt16T = std::enable_if_t< std::is_same_v<T,int16_t>, bool >;
 
template< typename T >
using IsInt32T = std::enable_if_t< std::is_same_v<T,int32_t>, bool >;

template< typename T >
using IsInt64T = std::enable_if_t< std::is_same_v<T,int64_t>, bool >;
 
template< template <typename, typename> typename Container , typename  U >
using IsContainer = std::enable_if_t< std::is_same_v<Container<U, std::allocator<U>>,std::vector<U, std::allocator<U>>> ||
                                    std::is_same_v<Container<U, std::allocator<U>>,std::list<U, std::allocator<U>>>, bool >;

template< template <typename...> typename Container , typename...  U >
using IsTuple = std::enable_if_t< std::is_same_v<Container<U...>,std::tuple<U...>>, bool >;


/*!
\brief
print_ip for string value
*/
template< typename T, IsString< T > = true>
void print_ip( T &&val )
{
    std::cout << std::forward<T>(val) << std::endl;
}

/*!
\brief
print_ip for vector or list
*/
template< template <typename, typename> typename Container , typename U, IsContainer< Container,  U > = true>
void print_ip( Container<U, std::allocator<U>> &&val )
{
    auto vec = std::forward<Container<U, std::allocator<U>>>(val);
    
    std::string res{""};
    for (auto it = vec.begin(); it != vec.end(); ++it)
    {
        res += std::to_string(*it);
        res += ".";
    }
    res.pop_back();
    std::cout << res <<std::endl;
}

/*!
\brief
 print_ip for tuple
*/
template< template <typename...> typename Container , typename... U, IsTuple< Container,  U... > = true>
void print_ip( Container<U...> &&val )
{
    auto tup = std::forward<Container<U...>>(val);
    
    std::string res{""};

    std::apply([&](auto&&... args)
    {
        ((res.append(std::to_string(args)).append(".")), ...);
    }, tup);

    res.pop_back();
    std::cout << res <<std::endl;
}

/*!\brief
* print_ip for uint8_t value
*/
template< typename T, IsInt8T< T > = true >
void print_ip( T &&val )
{

    auto b = (std::forward<T>(val) & 0x000000FF);
    std::cout << b << std::endl;
}

/*!\brief
* print_ip for uint16_t value
*/
template< typename T, IsInt16T< T > = true >
void print_ip( T &&val )
{
    auto b1 = (std::forward<T>(val) & 0x0000FF00)>>8;
    std::cout << b1 << "."
    << (std::forward<T>(val) & 0x000000FF) << std::endl;
}

/*!\brief
* print_ip for uint64_t value
*/
template< typename T, IsInt64T< T > = true >
void print_ip( T &&val )
{
    int b[8];
    b[0] = (std::forward<T>(val) & 0x00000000000000FF);
    b[1] = (std::forward<T>(val) & 0x000000000000FF00)>>8;
    b[2] = (std::forward<T>(val) & 0x0000000000FF0000)>>16;
    b[3] = (std::forward<T>(val) & 0x00000000FF000000)>>24;
    b[4] = (std::forward<T>(val) & 0x000000FF00000000)>>32;
    b[5] = (std::forward<T>(val) & 0x0000FF0000000000)>>40;
    b[6] = (std::forward<T>(val) & 0x00FF000000000000)>>48;
    b[7] = (std::forward<T>(val) & 0xFF00000000000000)>>56;
    
    for (int idx = 7; idx >= 0; --idx)
    {
        std::cout << b[idx];
        if (idx > 0)
            std::cout << ".";
    }
    std::cout << std::endl;
}

/*!\brief
* print_ip for uint32_t value
*/
template< typename T, IsInt32T< T > = true >
void print_ip( T &&val )
{
    auto b1 = (std::forward<T>(val) & 0x0000FF00)>>8;
    auto b2 = (std::forward<T>(val) & 0x00FF0000)>>16;
    auto b3 = (std::forward<T>(val) & 0xFF000000)>>24;
    std::cout << b3 << "."
            << b2 << "."
            << b1 << "."
            << (std::forward<T>(val) & 0x000000FF)
            <<  std::endl;
}

 
#endif /* ip_print_h */
