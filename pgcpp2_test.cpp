#include <cstdio>
#include <clocale>
#include <string>
#include <cstring>

#include <libpq-fe.h>

#include <pgcpp2/query.h>

struct A
{

};

std::string pgcpp_adopt(A const & x)
{
    return "A";
}

int main()
{
    pgcpp2::pg_conn conn = PQconnectdb("");
    if(conn)
    {
        PQtrace(conn.get(), stdout);

        pgcpp2::pg_result res = pgcpp2::query(conn, "SELECT * FROM test WHERE id=$1")
                .arg(880003);
//.arg() adds null value
//.arg(true) adds bool value
//.arg(3.4) adds double value
// Other values may be added by overloading pgcpp_adopt (ADL in action, common type is string)

        if(!res) return 1;

        std::printf("returned records: %d\n", res.ntuples());
        char sep[] = "|";

        PQprintOpt opt = {};
        opt.header = 1;
        opt.align  = 1;
        opt.fieldSep = sep;

        PQprint(stdout, res.get(), &opt);

        PQuntrace(conn.get());
    }
}
