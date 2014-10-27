#ifndef PGCPP_QUERY_ARG_STORAGE_H_INCLUDED
#define PGCPP_QUERY_ARG_STORAGE_H_INCLUDED

#include "detail/network_byte_storage.h"
#include "detail/simple_byte_storage.h"

namespace pgcpp2
{

template <typename T, bool IsBinary = true>
struct query_arg_storage
{
    typedef detail::network_byte_storage<T> type;
};
template <typename T>
struct query_arg_storage<T, false>
{
    typedef detail::simple_byte_storage<T>  type;
};

/*-*/
} //pgcpp2

#endif // PGCPP_QUERY_ARG_STORAGE_H_INCLUDED
