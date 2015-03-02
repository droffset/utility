#ifndef PGCPP_QUERY_ARG_TRAITS_H_INCLUDED
#define PGCPP_QUERY_ARG_TRAITS_H_INCLUDED

#include <pgcpp2/query_arg_storage.h>

#include <stdint.h>

/* POSTGRESQL OIDS */
#define BOOLOID		16
#define CHAROID		18
#define INT2OID		21
#define INT4OID		23
#define INT8OID		20
#define TEXTOID		25
#define FLOAT4OID   700
#define FLOAT8OID   701
#define VARCHAROID  1043

namespace pgcpp2
{

template <typename T>
struct query_arg_traits
{
    enum { oid_type  = VARCHAROID };
    enum { is_binary = false };

    typedef T arg_type;
    typedef typename query_arg_storage<arg_type, is_binary>::type storage_type;
};

template <>
struct query_arg_traits<void>
{
    enum { oid_type  = 0 };
    enum { is_binary = false };

    typedef struct arg_type
    {
        size_t size() const
        {
            return 0;
        }
        char const * data() const
        {
            return 0;
        }
    } storage_type;
};

#define PGCPP_ARG_TRAITS_DECLARE(Type, Oid, Binary) \
    template <> \
    struct query_arg_traits<Type> \
    { \
        enum { oid_type  = (Oid) }; \
        enum { is_binary = (Binary) }; \
        \
        typedef Type arg_type; \
        typedef query_arg_storage<arg_type, is_binary>::type storage_type; \
    }

PGCPP_ARG_TRAITS_DECLARE(uint8_t, CHAROID, true);
PGCPP_ARG_TRAITS_DECLARE(int8_t, CHAROID, true);
PGCPP_ARG_TRAITS_DECLARE(uint16_t, INT2OID, true);
PGCPP_ARG_TRAITS_DECLARE(int16_t, INT2OID, true);
PGCPP_ARG_TRAITS_DECLARE(uint32_t, INT4OID, true);
PGCPP_ARG_TRAITS_DECLARE(int32_t, INT4OID, true);
PGCPP_ARG_TRAITS_DECLARE(uint64_t, INT8OID, true);
PGCPP_ARG_TRAITS_DECLARE(int64_t, INT8OID, true);

PGCPP_ARG_TRAITS_DECLARE(float, FLOAT4OID, true);
PGCPP_ARG_TRAITS_DECLARE(double, FLOAT8OID, true);
PGCPP_ARG_TRAITS_DECLARE(long double, FLOAT8OID, true);

PGCPP_ARG_TRAITS_DECLARE(bool, BOOLOID, true);
PGCPP_ARG_TRAITS_DECLARE(char, CHAROID, true);

#undef PGCPP_ARG_TRAITS_DECLARE
/*-*/

#undef BOOLOID
#undef CHAROID
#undef INT2OID
#undef INT4OID
#undef INT8OID
#undef TEXTOID
#undef FLOAT4OID
#undef FLOAT8OID
/*-*/

} //pgcpp2

#endif // PGCPP_QUERY_ARG_TRAITS_H_INCLUDED
