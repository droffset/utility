#ifndef PGCPP_PG_CONN_H_INCLUDED
#define PGCPP_PG_CONN_H_INCLUDED

#include "detail/pg_scoped_resource.h"

namespace pgcpp2
{

typedef detail::scoped_resource< ::PGconn, ::PQfinish > pg_conn_base;

struct pg_conn
    : public pg_conn_base
{
    pg_conn(::PGconn * x)
        : pg_conn_base(x)
    { }
};

}

#endif // PGCPP_PG_CONN_H_INCLUDED
