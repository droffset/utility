#ifndef PGCPP_QUERY_H_INCLUDED
#define PGCPP_QUERY_H_INCLUDED

#include <pgcpp2/query_arg_tuple.h>
#include <pgcpp2/pg_conn.h>
#include <pgcpp2/pg_result.h>

namespace pgcpp2
{

inline query_arg_empty query(PGconn * conn, char const * sql)
{
    return query_arg_empty(conn, sql);
}

inline query_arg_empty query(pg_conn & conn, char const * sql)
{
    return query_arg_empty(conn.get(), sql);
}

}

#endif // PGCPP_QUERY_H_INCLUDED
