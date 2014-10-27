#ifndef PGCPP_DETAIL_SIMPLE_BYTE_STORAGE_H_INCLUDED
#define PGCPP_DETAIL_SIMPLE_BYTE_STORAGE_H_INCLUDED

#include <string>
#include <cstring>

namespace pgcpp2
{
namespace detail
{

// by default we store data in string
template <typename T>
struct simple_byte_storage
{
    simple_byte_storage(std::string const & value)
        : bytes(value)
    { }

    simple_byte_storage(char const * value)
        : bytes(value)
    { }

    char const * data() const
    {
        return bytes.data();
    }
    int size() const
    {
        return static_cast<int>(bytes.size());
    }

private:
    std::string const bytes;
};

// if data already in std::string, we do not copy it
template <>
struct simple_byte_storage<std::string>
{
    simple_byte_storage(std::string const & value)
        : bytes(value)
    { }

    char const * data() const
    {
        return bytes.data();
    }
    int size() const
    {
        return static_cast<int>(bytes.size());
    }

private:
    std::string const & bytes;
};

template <>
struct simple_byte_storage<char const *>
{
    simple_byte_storage(char const * value)
        : bytes(value)
    { }
    char const * data() const
    {
        return bytes;
    }
    int size() const
    {
        return std::strlen(bytes);
    }

private:
    char const * bytes;
};

template <>
struct simple_byte_storage<char *>
    : public simple_byte_storage<char const *>
{
    simple_byte_storage(char * value)
        : simple_byte_storage<char const *>(value)
    { }
};

template <size_t N>
struct simple_byte_storage<char [N]>
    : public simple_byte_storage<char const *>
{
    simple_byte_storage(char const (&value)[N])
        : simple_byte_storage<char const *>(value)
    { }
    simple_byte_storage(char (&value)[N])
        : simple_byte_storage<char const *>(value)
    { }
};

template <size_t N>
struct simple_byte_storage<char const [N]>
    : public simple_byte_storage<char const *>
{
    simple_byte_storage(char const (&value)[N])
        : simple_byte_storage<char const *>(value)
    { }
    simple_byte_storage(char (&value)[N])
        : simple_byte_storage<char const *>(value)
    { }
};
/*-*/

} // detail
} // pgcpp2

#endif // PGCPP_DETAIL_SIMPLE_BYTE_STORAGE_H_INCLUDED
