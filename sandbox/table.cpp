#include <nt2/core/container/dsl.hpp>
#include <nt2/core/container/category.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/details/type_id.hpp>
#include <iostream>

template<class T>
struct block
{
  boost::array<T, 4096> data;
};

namespace boost { namespace dispatch { namespace meta
{
  template<class T>
  struct value_of< ::block<T> >
  {
    typedef T type;
  };
    
  template<class T, class Origin>
  struct hierarchy_of< ::block<T>, Origin >
  {
    typedef container_< typename property_of<T, Origin>::type, int /* to replace */> type;
  };
    
} } }

namespace nt2 { namespace container
{
  template<class T>
  struct is_block< ::block<T> >
    : boost::mpl::true_
  {
  };
} }

template<class T>
struct table : nt2::container::expression< typename boost::proto::terminal< ::block<T> >::type, ::block<T>& >
{
  typedef nt2::container::expression< typename boost::proto::terminal< block<T> >::type, ::block<T>& > parent;
  
  table()
  {
  }

  // Construction from arbitrary expression is same as assignment
  template<class Xpr> 
  BOOST_DISPATCH_FORCE_INLINE table(Xpr const& xpr) { *this = xpr; }

  // Assignment operators force evaluation
  template<class Xpr>
  BOOST_DISPATCH_FORCE_INLINE table& operator=(Xpr const& xpr)
  {
    nt2::evaluate( nt2::assign(*this, xpr) );
    return *this;
  }
};

namespace boost { namespace dispatch { namespace meta
{
  template<class T>
  struct semantic_of< ::table<T> >
    : semantic_of< typename ::table<T>::parent >
  {
  };
} } }

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION(boost::simd::tag::map_, tag::cpu_
                            , (F)(A0)(S0)
                            , (unspecified_<F>)((container_< unspecified_<A0>, S0 >))
                            )
  {
    typedef A0 result_type;
    result_type operator()(F const& f, A0 const& a0) const
    {
      return a0;
    }
  };
  
  NT2_FUNCTOR_IMPLEMENTATION(boost::simd::tag::map_, tag::cpu_
                            , (F)(A0)(S0)(A1)(S1)
                            , (unspecified_<F>)((container_< unspecified_<A0>, S0 >))((container_< unspecified_<A1>, S1 >))
                            )
  {
    typedef A0 result_type;
    result_type operator()(F const& f, A0 const& a0, A1 const& a1) const
    {
      return a0;
    }
  };
  
} }

int main()
{
  table<double> a, b, c;
  a = b + c*c/a;
}
