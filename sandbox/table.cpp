#include <iostream>

#include <nt2/include/functions/run.hpp>
#include <nt2/core/container/table/table.hpp>
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


int main()
{
  using nt2::container::table;
  table<double, nt2::of_size_<5, 10> > a, b, c;
/*
  std::cout << "a = " << (void*)&a << std::endl;
  std::cout << "b = " << (void*)&b << std::endl;
  std::cout << "c = " << (void*)&c << std::endl;
*/

/*  a = -(c+b);
  a = -b;*/

  //a = -(c+b);
  a = -(b + c*(a+(c * -c))) + b;
#if 0
  a = b + c;
  std::cout << std::endl;
  b += c;
  std::cout << std::endl;
  c += -a;
  std::cout << std::endl;
#endif
  /* c(a) += a; // function undefined
  c(a) = b(c) + c(a)*b(a);*/
}
