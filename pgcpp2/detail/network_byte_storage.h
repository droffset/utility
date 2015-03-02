#ifndef PGCPP_DETAIL_NETWORK_BYTE_STORAGE_H_INCLUDED
#define PGCPP_DETAIL_NETWORK_BYTE_STORAGE_H_INCLUDED

namespace pgcpp2
{
namespace detail
{

template <typename T, size_t Byte>
struct reinterpret_
{
    static void reverse(char (&dest)[sizeof(T)], char const * value)
    {
        dest[Byte] = *value;
        reinterpret_<T, Byte - 1>::reverse(dest, ++value);
    }
};
template <typename T>
struct reinterpret_<T, 0>
{
    static void reverse(char (&dest)[sizeof(T)], char const * value)
    {
        dest[0] = *value;
    }
};

template <typename T>
struct reinterpret
    : reinterpret_<T, sizeof(T) - 1> //GCC 2.95 workaround
{ };

template <typename T>
union network_byte_storage
{
public:
    network_byte_storage(T const & val)
    {
        reinterpret<T>::reverse(bytes, reinterpret_cast<char const *>(&val));
    }
    network_byte_storage()
        : bytes()
    { }

    int size() const
    {
        return sizeof(T);
    }
    char const * data() const
    {
        return bytes;
    }

private:
    T    value;
    char bytes[sizeof(T)];
};
/*-*/

} // detail
} // pgcpp2

#endif // PGCPP_DETAIL_NETWORK_BYTE_STORAGE_H_INCLUDED
