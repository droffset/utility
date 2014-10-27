#ifndef PGCPP_QUERY_INFO_H_INCLUDED
#define PGCPP_QUERY_INFO_H_INCLUDED

#include <libpq-fe.h>

namespace pgcpp2
{

struct query_info
{
    PGconn *     conn;
    char const * query;

    query_info(PGconn * conn, char const * query)
        : conn(conn), query(query)
    { }
};

} // pgcpp2

#endif // PGCPP_QUERY_INFO_H_INCLUDED
