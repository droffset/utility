#ifndef PGCPP_PG_RESULT_H_INCLUDED
#define PGCPP_PG_RESULT_H_INCLUDED

#include "detail/pg_scoped_resource.h"

#include <pgcpp2/query_result_converter.h>

namespace pgcpp2
{

typedef detail::scoped_resource< ::PGresult, ::PQclear > pg_result_base;

struct pg_result
    : public pg_result_base
{
    template <typename T>
    pg_result(query_result_converter<T> const & x)
        : pg_result_base(x)
    { }
    pg_result(::PGresult * x)
        : pg_result_base(x)
    { }

    int ntuples() const
    {
        return ::PQntuples(get());
    }

    int nfields() const
    {
        return ::PQnfields(get());
    }

    char const * fname(int field) const
    {
        return ::PQfname(get(), field);
    }

    int fnumber(char const * field) const
    {
        return ::PQfnumber(get(), field);
    }

    ::Oid ftype(int field) const
    {
        return ::PQftype(get(), field);
    }

    short fsize(int field) const
    {
        return ::PQfsize(get(), field);
    }

    char const * getvalue(int row, int field) const
    {
        return ::PQgetvalue(get(), row, field);
    }

    char const * getvalue(int row, char const * field) const
    {
        return ::PQgetvalue(get(), row, fnumber(field));
    }

    bool getisnull(int row, int field) const
    {
        return ::PQgetisnull(get(), row, field);
    }
};

}

#endif // PGCPP_PG_RESULT_H_INCLUDED
