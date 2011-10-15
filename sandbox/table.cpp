#include <iostream>
#include <nt2/sdk/details/type_id.hpp>

#include <nt2/include/functions/of_size.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/toolbox/operator/functions.hpp>

namespace nt2 { namespace ext
{
  // terminal, does load / store
  NT2_FUNCTOR_IMPLEMENTATION_TPL( nt2::tag::terminal_, tag::cpu_
                                , (class A0)(class S0)(class State)
                                , ((ast_<table_< unspecified_<A0>, S0 > >))
                                  (fusion_sequence_<State>)
                                )
  {
    typedef typename boost::dispatch::meta::
    scalar_of< typename boost::dispatch::meta::
               semantic_of<A0>::type
             >::type                                        result_type;

    template<class A0_>
    result_type operator()(A0_& a0, State const& state) const
    {
       return (boost::proto::value(a0))(state);    
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION_TPL( nt2::tag::terminal_, tag::cpu_
                            , (class A0)(class State)
                            , ((ast_<table_< unspecified_<A0>, nt2::of_size_<1> > >))
                              (fusion_sequence_<State>)
                            )
  {
    typedef typename boost::dispatch::meta::
    scalar_of< typename boost::dispatch::meta::
               semantic_of<A0>::type
             >::type                                       result_type;

    template<class A0_> BOOST_DISPATCH_FORCE_INLINE
    result_type operator()(A0_& a0, State const& state) const
    {
       static typename boost::remove_reference<result_type>::type r;
       return r;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION_TPL( nt2::tag::terminal_, tag::cpu_
                            , (class A0)(class State)
                            , ((ast_<scalar_< unspecified_<A0> > >))
                              (fusion_sequence_<State>)
                            )
  {
    typedef typename boost::dispatch::meta::
    scalar_of< typename boost::dispatch::meta::
               semantic_of<A0>::type
             >::type                                       result_type;

    template<class A0_> BOOST_DISPATCH_FORCE_INLINE
    result_type operator()(A0_& a0, State const& state) const
    {
       return boost::proto::value(a0);
    }
  };
} }

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION
  ( boost::simd::tag::store_, tag::cpu_, (A0)(A1)(A2)(S0)
  , ((ast_<table_< unspecified_<A0>, S0 > >))
    (fusion_sequence_<A1>)
    (scalar_< arithmetic_<A2> >)
  )
  {
    typedef A2 result_type;
    result_type operator()(A0& dst, A1 const& pos, A2 const& src) const
    {
      boost::proto::value(dst)(pos) = src;
      return src;
    }
  };
} }

using nt2::container::table;

int main()
{
  int d0,d1;
  std::cin >> d0 >> d1;

  table<double,nt2::_2D> a( nt2::of_size(d0,d1) );
  a = (a + 3.) * 10.;

  boost::array<int,2> p;
  for(p[1]=1;p[1]<=d1;++p[1])
  {
    for(p[0]=1;p[0]<=d0;++p[0])
      std::cout << boost::proto::value(a)(p) << " ";
    std::cout << "\n";
  }

  a *= a + 1.; // problem with a *= a

  for(p[1]=1;p[1]<=d1;++p[1])
  {
    for(p[0]=1;p[0]<=d0;++p[0])
      std::cout << boost::proto::value(a)(p) << " ";
    std::cout << "\n";
  }

#if 0
  a = -(b + c*(a+(c * -c))) + b;
  a = b + c;
  a = -b;
  b += c;
  c += -a;
#endif

  /* 
  
  c(a) += a; // function undefined
  c(a) = b(c) + c(a)*b(a);
  
  */
}
