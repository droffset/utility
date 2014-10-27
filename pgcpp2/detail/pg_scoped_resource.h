#ifndef PGCPP_DETAIL_PG_SCOPED_RESOURCE_H_INCLUDED
#define PGCPP_DETAIL_PG_SCOPED_RESOURCE_H_INCLUDED

namespace pgcpp2
{
namespace detail
{

template <typename T, void (*Deleter)(T *)>
class scoped_resource
{
    typedef void (scoped_resource::*bool_type)() const;
    void this_type_does_not_support_comparisons() const {}

public:
    explicit scoped_resource(T * x = 0)
        : res_(x)
    { }

    explicit scoped_resource(scoped_resource const & x)
        : res_(x.res_)
    {
        x.res_ = 0;
    }

    ~scoped_resource()
    {
        Deleter(res_);
    }

    void reset(T * p = 0)
    {
        if(p != res_)
        {
            Deleter(res_);
            res_ = p;
        }
    }

    T * get() const
    {
        return res_;
    }

    T * release()
    {
        T * res = res_;
        res_ = 0;
        return res;
    }

    void swap(scoped_resource & x)
    {
        T * res = x.res_;
        x.res_ = res_;
        res_ = res;
    }

    operator bool_type() const
    {
        return res_
            ? &scoped_resource::this_type_does_not_support_comparisons
            : 0;
    }

private:
    scoped_resource & operator=(scoped_resource const &);

    mutable T * res_;
};

}//detail

}//pgcpp2

#endif // PGCPP_DETAIL_PG_SCOPED_RESOURCE_H_INCLUDED
