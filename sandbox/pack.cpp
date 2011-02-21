#include <iostream>
#include <nt2/sdk/details/type_id.hpp>
#include <nt2/sdk/simd/pack.hpp>
#include <boost/proto/debug.hpp>

#include <nt2/include/functions/cos.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/exponentbits.hpp>

using namespace std;

NT2_REGISTER_DISPATCH ( Func , tag::cpu_
                      , (Func)(D)
                        (A0)(T0)(S0)
                      , ((expr_<A0, domain_<D>, T0, S0>))
                      )

NT2_REGISTER_DISPATCH ( Func , tag::cpu_
                      , (Func)(D)
                        (A0)(T0)(S0)
                        (A1)
                      , ((expr_<A0, domain_<D>, T0, S0>))
                        (fundamental_<A1>)
                      )

NT2_REGISTER_DISPATCH ( Func , tag::cpu_
                      , (Func)(D)
                        (A0)
                        (A1)(T1)(S1)
                      , (fundamental_<A0>)
                        ((expr_<A1, domain_<D>, T1, S1>))
                      )

NT2_REGISTER_DISPATCH ( Func , tag::cpu_
                      , (Func)(D)
                        (A0)(T0)(S0)
                        (A1)(T1)(S1)
                      , ((expr_<A0, domain_<D>, T0, S0>))
                        ((expr_<A1, domain_<D>, T1, S1>))
                      )

namespace nt2 { namespace ext
{
  template< class Func, class D, class T0, class S0 , class Dummy >
  struct  call< Func(tag::expr_<D,T0,S0>)
              , tag::cpu_, Dummy
              >
        : callable
  {
    template<class Sig> struct result;

    template<class This,class A0>
    struct result<This(A0)>
    {
      typedef typename boost::proto::result_of::
      make_expr < Func
                , typename meta::strip<A0>::type const&
                >::type type;
    };

    NT2_FUNCTOR_CALL(1)
    {
      return boost::proto::make_expr<Func>(boost::cref(a0));
    }
  };


  template< class Func, class D
          , class T0, class S0
          , class T1, class S1
          , class Dummy >
  struct  call< Func(tag::expr_<D,T0,S0>,tag::expr_<D,T1,S1>)
              , tag::cpu_, Dummy
              >
        : callable
  {
    template<class Sig> struct result;

    template<class This,class A0,class A1>
    struct result<This(A0,A1)>
    {
      typedef typename boost::proto::result_of::
      make_expr < Func
                , typename meta::strip<A0>::type const&
                , typename meta::strip<A1>::type const&
                >::type type;
    };

    NT2_FUNCTOR_CALL(2)
    {
      return boost::proto::make_expr<Func>(boost::cref(a0),boost::cref(a1));
    }
  };

  template<class D, class T0, class S0 , class Dummy >
  struct  call< tag::exponentbits_(tag::expr_<D,T0,S0>)
              , tag::cpu_, Dummy
              >
        : callable
  {
    template<class Sig> struct result;

    template<class This,class A0>
    struct result<This(A0)>
    {
      typedef typename boost::proto::result_of::
      make_expr < tag::exponentbits_
                , simd::domain< typename meta::
                                as_integer<typename D::simd_type, signed>::type
                              , typename D::simd_cardinal
                              >
                , typename meta::strip<A0>::type const&
                >::type type;
    };

    NT2_FUNCTOR_CALL(1)
    {
      typedef simd::domain< typename meta::
                            as_integer<typename D::simd_type, signed>::type
                          , typename D::simd_cardinal
                          > domain_type;

      return  boost::proto::
              make_expr<tag::exponentbits_,domain_type>(boost::cref(a0));
    }
  };
} }

template<class Xpr> void
foo(Xpr const& x)
{
  std::cout << "Proto:\n"; boost::proto::display_expr(x);
  std::cout << nt2::type_id<typename boost::proto::domain_of<Xpr>::type>() << "\n";
}

int main()
{
  nt2::simd::pack<nt2::int32_t> x(5.321f);
  nt2::simd::pack<float> y(5.321);

  foo(x);
  foo(nt2::exponentbits(y));
  foo(nt2::cos(y) + nt2::cos(y)); // ok
  foo(nt2::exponentbits(y) + x); // not ok

}
