#include <nt2/core/container/dsl.hpp>
#include <nt2/core/container/category.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/details/type_id.hpp>
#include <iostream>
#include <boost/proto/debug.hpp>
#include <boost/dispatch/dsl/category.hpp>

template<class T, class Terminal>
struct block
{
  boost::array<T, 4096> data;
};

template<class T>
struct table_ : table_< typename T::parent >
{
  typedef table_< typename T::parent > parent;
};

template<class T>
struct table_< boost::dispatch::meta::unspecified_<T> > : boost::dispatch::meta::unspecified_<T>
{
  typedef boost::dispatch::meta::unspecified_<T> parent;
};

namespace tag
{
  struct table_ 
  { 
    template<class T> struct apply { typedef ::table_<T> type;  };  
  };
}

namespace boost { namespace dispatch { namespace meta
{
  template<class T, class Tag>
  struct value_of< ::block<T,Tag> >
  {
    typedef T type;
  };
    
  template<class T, class Tag, class Origin>
  struct hierarchy_of< ::block<T,Tag>, Origin >
  {
    typedef typename 
            boost::mpl::apply < Tag
                              , typename property_of<T, Origin>::type
                              >::type base;
    typedef container_< base > type;
  };
    
} } }

namespace nt2 { namespace container
{
  template<class T,class Tag>
  struct is_block< ::block<T,Tag> >
    : boost::mpl::true_
  {
  };
} }

template<class T>
struct table 
: nt2::container::
  expression< typename boost::proto::terminal<::block<T,tag::table_> >::type
            , ::block<T,tag::table_>& 
            >
{
  typedef nt2::container::
  expression< typename boost::proto::terminal<::block<T,tag::table_> >::type
            , ::block<T,tag::table_>& 
            > parent;
  
  table() {}

  // Construction from arbitrary expression is same as assignment
  template<class Xpr,class Result> 
  BOOST_DISPATCH_FORCE_INLINE 
  table(expression<Xpr,Result> const& xpr) { *this = xpr; }

  // Assignment operators force evaluation
  BOOST_DISPATCH_FORCE_INLINE table& operator=(table const& xpr)
  {
    nt2::evaluate( nt2::assign(*this, xpr) );
    return *this;
  }
  
  template<class Xpr,class Result> 
  BOOST_DISPATCH_FORCE_INLINE 
  table& operator=(expression<Xpr,Result> const& xpr)
  {
    nt2::evaluate( nt2::assign(*this, xpr) );
    return *this;
  }
};

namespace boost { namespace dispatch { namespace meta
{
  template<class T>
  struct semantic_of<::table<T> > : semantic_of<typename ::table<T>::parent> {};
} } }

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION(boost::simd::tag::map_, tag::cpu_
                            , (F)(A0)
                            , (unspecified_<F>)
                              ((container_< unspecified_<A0> >))
                            )
  {
    typedef A0 const& result_type;
    result_type inline operator()(F const&, A0 const& a0)
    {
      return a0;
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
  NT2_FUNCTOR_IMPLEMENTATION( boost::simd::tag::run_, tag::formal_
                            , (A0)
                            , ( boost::dispatch::meta::
                                ast_<container_< table_<unspecified_<A0> > > >
                              )
                            )
  {
    typedef typename boost::dispatch::meta::semantic_of<A0>::type result_type;
    
    BOOST_DISPATCH_FORCE_INLINE result_type
    operator()(A0 const& a0) const
    {
      static block<double,::tag::table_> b;
      std::cout << "Evaluated:\n";
      boost::proto::display_expr(a0);
      std::cout << "as a " << nt2::type_id<::tag::table_>() << "\n";
      return b;
    }
  };
} }


int main()
{
  table<double> a, b, c;
  a = b + c*c/a;
  b = c;
  c += !a;
  c(a) = b(c) + c(a)*b(a);
}
