#ifndef PGCPP_QUERY_ARG_TUPLE_FWD_H_INCLUDED
#define PGCPP_QUERY_ARG_TUPLE_FWD_H_INCLUDED

#include <pgcpp2/query_arg_traits.h>

namespace pgcpp2
{

class query_arg_empty;

template <typename ArgT
        , typename TailT = query_arg_empty
        , typename ArgTraitsT = query_arg_traits<ArgT> >
class query_arg_tuple;

}

#endif // PGCPP_QUERY_ARG_TUPLE_FWD_H_INCLUDED
