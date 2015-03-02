#ifndef PGCPP_QUERY_ARG_TUPLE_H_INCLUDED
#define PGCPP_QUERY_ARG_TUPLE_H_INCLUDED

#include <pgcpp2/query_info.h>
#include <pgcpp2/query_result_converter.h>

#define GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)

namespace pgcpp2
{

class pg_conn;

template <typename T>
inline T const & pgcpp_adopt(T const & c) //for ADL
{
    return c;
}

namespace detail
{

template <typename HolderT, size_t Size = 0>
struct tuple_size
{
    enum { value = tuple_size<typename HolderT::tail_type, Size + 1>::value };
};
template <size_t Size>
struct tuple_size<query_arg_empty, Size>
{
    enum { value = Size };
};

template <size_t ArgsCount>
struct query_prepeared_data
{
    char const * args[ArgsCount];
    int lens[ArgsCount];
    int bins[ArgsCount];
    ::Oid oids[ArgsCount];
};

} // detail

template <typename ArgT, typename TailT, typename ArgTraitsT>
class query_arg_tuple
    : public query_result_converter< query_arg_tuple<ArgT, TailT, ArgTraitsT> >
{
public:
// for external algorithms
    typedef TailT                               tail_type;
    typedef typename ArgTraitsT::arg_type       arg_type;
    typedef typename ArgTraitsT::storage_type   storage_type;

    ::PGresult * result() const
    {
        enum { count = detail::tuple_size<query_arg_tuple>::value };

        detail::query_prepeared_data<count> queryData;

        query_info const & inf = fill(queryData);

        return ::PQexecParams(inf.conn, inf.query
    	                       , count  /* num params */
                               , queryData.oids /* param types */
                               , queryData.args /* params */
                               , queryData.lens /* param sizes */
                               , queryData.bins /* binary or not*/
                               , 0);   /* ask for binary results */
    }

public:
// constructors
    query_arg_tuple(arg_type const & arg, tail_type const & tail)
        : data_(pgcpp_adopt(arg)), tail_(tail)
    { }

    template <size_t ArgsCount>
    query_info const & fill(detail::query_prepeared_data<ArgsCount> & queryData) const
    {
        enum { index = detail::tuple_size<query_arg_tuple>::value - 1 };

        queryData.args[index] = data_.data();
        queryData.lens[index] = data_.size();
        queryData.bins[index] = ArgTraitsT::is_binary;
        queryData.oids[index] = ArgTraitsT::oid_type;

        return tail_.fill(queryData);
    }

private:
    storage_type const data_;
    tail_type const &  tail_;
};

class query_arg_empty
    : public query_result_converter<query_arg_empty>
{
public:
    ::PGresult * result() const
    {
        return ::PQexec(inf_.conn, inf_.query);
    }

public:
    template <size_t ArgsCount>
    query_info const & fill(detail::query_prepeared_data<ArgsCount> &) const
    {
        return inf_;
    }

    friend query_arg_empty query(::PGconn * conn, char const *);
    friend query_arg_empty query(pg_conn & conn, char const *);

    query_arg_empty(query_arg_empty const & x) 
        : inf_(x.inf_)
    { }

private:
    query_arg_empty(::PGconn * conn, char const * query)
        : inf_(conn, query)
    { }

    query_arg_empty(); //disallow
    query_arg_empty & operator=(query_arg_empty const &); //disallow

    query_info const inf_;
};

/*-*/
} //pgcpp2

#undef GCC_VERSION

#endif // PGCPP_QUERY_ARG_TUPLE_H_INCLUDED
