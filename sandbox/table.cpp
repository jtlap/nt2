#include <nt2/core/container/dsl.hpp>
#include <nt2/core/container/category.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/details/type_id.hpp>
#include <nt2/include/functions/run.hpp>
#include <iostream>
#include <boost/proto/debug.hpp>
#include <boost/dispatch/dsl/category.hpp>

template<class T>
struct block
{
  boost::array<T, 4096> data;
};

namespace nt2 { namespace container
{
    
template<class Block>
struct table_container
{
    Block block;
};

template<class T>
struct is_container< table_container<T> >
  : boost::mpl::true_
{
};

} }

namespace boost { namespace dispatch { namespace meta
{
  template<class T>
  struct value_of< nt2::container::table_container<T> >
  {
    typedef T type;
  };
    
  template<class T>
  struct value_of< ::block<T> >
  {
    typedef T type;
  };
    
  template<class T, class Origin>
  struct hierarchy_of< nt2::container::table_container<T>, Origin >
  {
    typedef container_< typename property_of<typename value_of<T>::type, Origin>::type > type;
  };
    
} } }

namespace nt2 { namespace container
{

template<class T, class S>
struct make_block
{
  typedef ::block<T> type;
};

template<class T, class S>
struct table 
: expression< typename boost::proto::terminal< table_container< typename make_block<T, S>::type > >::type
            , table_container< typename make_block<T, S>::type >&
            >
{
  typedef
  expression< typename boost::proto::terminal< table_container< typename make_block<T, S>::type > >::type
            , table_container< typename make_block<T, S>::type >&
            > parent;
  
  table() {}

  template<class Xpr,class Result> 
  BOOST_DISPATCH_FORCE_INLINE 
  table(expression<Xpr,Result> const& xpr) { static_cast<parent&>(*this) = xpr; }
};

} }

namespace boost { namespace dispatch { namespace meta
{
  template<class T>
  struct semantic_of<nt2::container::table<T> >
    : semantic_of<typename nt2::container::table<T>::parent>
  {
  };
} } }

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION(boost::simd::tag::map_, tag::cpu_
                            , (F)(A0)
                            , (unspecified_<F>)
                              ((container_< unspecified_<A0> >))
                            )
  {
    typedef A0& result_type;
    result_type inline operator()(F const&, A0 const& a0)
    {
      return const_cast<A0&>(a0);
    }
  };
  
  NT2_FUNCTOR_IMPLEMENTATION(boost::simd::tag::map_, tag::cpu_
                            , (F)(A0)(A1)
                            , (unspecified_<F>)
                              ((container_< unspecified_<A0> >))
                              ((container_< unspecified_<A1> >))
                            )
  {
    typedef A0& result_type;
    result_type inline operator()(F const&, A0 const& a0, A1 const& a1)
    {
      return const_cast<A0&>(a0);
    }
  };  
} }

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_, tag::cpu_
                            , (A0)
                            , (boost::dispatch::meta::ast_<container_< unspecified_<A0> > >)
                            )
  {
    typedef typename boost::dispatch::meta::semantic_of<A0>::type result_type;
    
    BOOST_DISPATCH_FORCE_INLINE result_type
    operator()(A0 const& a0) const
    {
      std::cout << "Evaluated:\n";
      boost::proto::display_expr(a0);
      static typename boost::remove_reference<result_type>::type r;
      return r;;
    }
  };
} }


int main()
{
  using nt2::container::table;
    
  table<double> a, b, c;
  a = b + c*c/a;
  b = c;
  c += !a;
  c(a) += !a;
  c(a) = b(c) + c(a)*b(a);
}
