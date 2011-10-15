#include <iostream>
#include <nt2/sdk/details/type_id.hpp>

#include <nt2/include/functions/run.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/core/container/memory/dense_block.hpp>
#include <nt2/toolbox/operator/functions.hpp>

namespace nt2
{
  // To replace with appropriate stuff
  template<class T>
  boost::array<std::size_t, NT2_MAX_DIMENSIONS> base_indices(T const&)
  {
    boost::array<std::size_t, NT2_MAX_DIMENSIONS> sz = { BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS, 1 BOOST_PP_INTERCEPT) };
    return sz;
  }
}

#include <boost/dispatch/meta/identity.hpp>

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
       static typename boost::remove_reference<result_type>::type r;
       return r;
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

  NT2_REGISTER_DISPATCH_TO_TPL( nt2::tag::terminal_, tag::cpu_
                            , (class A0)(class State)(std::size_t N)
                            , ((ast_<scalar_< unspecified_<A0> > >))
                              ((array_< scalar_< integer_<State> >, N>))
                            , identity
                            )
} }

#define M0(z,n,t)                                                       \
boost::array<std::ptrdiff_t,n> BOOST_DISPATCH_FORCE_INLINE              \
at(BOOST_PP_ENUM_PARAMS(n,std::ptrdiff_t i) )                           \
{                                                                       \
  boost::array<std::ptrdiff_t,n> that = {{BOOST_PP_ENUM_PARAMS(n,i)}};  \
  return that;                                                          \
}                                                                       \
/**/

BOOST_PP_REPEAT_FROM_TO(1,5,M0,~)

int main()
{
  using nt2::container::table;
  
  //while(1)
  {
    int d0,d1,d2,d3;
    //std::cin >> d0 >> d1 >> d2 >> d3;
    table<double, nt2::_2D> a( nt2::of_size(2,2) );

    a = 3. - a;
  }

#if 0
  a = -(b + c*(a+(c * -c))) + b;
  std::cout << std::endl;
  a = b + c;
  std::cout << std::endl;
  a = -b;
  std::cout << std::endl;
  b += c;
  std::cout << std::endl;
  c += -a;
  std::cout << std::endl;
#endif
  /* c(a) += a; // function undefined
  c(a) = b(c) + c(a)*b(a);*/
}
