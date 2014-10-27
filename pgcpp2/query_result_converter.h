#ifndef PGCPP_QUERY_RESULT_CONVERTER_H_INCLUDED
#define PGCPP_QUERY_RESULT_CONVERTER_H_INCLUDED

#include <pgcpp2/query_arg_tuple_fwd.h>

namespace pgcpp2
{

template <typename T>
struct query_result_converter
{
    operator ::PGresult *() const
    {
        return self().result();
    }

    template <typename A, typename Tr>
    query_arg_tuple<A, T, Tr> arg(A const & x) const
    {
        return query_arg_tuple<A, T, Tr>(x, self());
    }
    template <typename A>
    query_arg_tuple<A, T> arg(A const & x) const
    {
        return query_arg_tuple<A, T>(x, self());
    }
    query_arg_tuple<void, T> arg() const
    {
        return query_arg_tuple<void, T>(
                        typename query_arg_tuple<void, T>::arg_type()
                                        , self());
    }

private:

    T const & self() const
    {
        return static_cast<T const &>(*this);
    }
    T & self()
    {
        return static_cast<T &>(*this);
    }
};

} //pgcpp2

#endif // PGCPP_QUERY_RESULT_CONVERTER_H_INCLUDED
