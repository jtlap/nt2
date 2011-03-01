#include <iostream>
//#define BOOST_PROTO_STRICT_RESULT_OF

#include <nt2/sdk/details/type_id.hpp>
#include <nt2/sdk/meta/any.hpp>
#include <nt2/sdk/simd/pack.hpp>
#include <boost/proto/debug.hpp>

#include <nt2/include/functions/cos.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/exponentbits.hpp>

using namespace std;

namespace nt2 { namespace ext
{
  template<class Dummy >
  struct  call< tag::exponentbits_(tag::ast_), tag::cpu_, Dummy>
        : callable
  {
    template<class Sig> struct result;

    template<class This,class A0>
    struct result<This(A0)>
    {
      typedef typename boost::proto::domain_of<A0>::type domain_type;
      typedef typename boost::proto::result_of::
      make_expr < tag::exponentbits_
                , simd::domain< typename meta::
                                as_integer<typename domain_type::simd_type, signed>::type
                              , typename domain_type::cardinal_type
                              >
                , typename meta::strip<A0>::type const&
                >::type type;
    };

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename boost::proto::domain_of<A0>::type base_type;
      typedef simd::domain< typename meta::
                            as_integer<typename base_type::simd_type, signed>::type
                          , typename base_type::cardinal_type
                          > domain_type;

      return  boost::proto::
              make_expr<tag::exponentbits_,domain_type>(boost::cref(a0));
    }
  };
} }

template<class Xpr> void
foo(Xpr const& x)
{
  std::cout << nt2::type_id(x) << "\n";
}

int main()
{
  nt2::simd::pack<nt2::int32_t> x(5.321f);
  nt2::simd::pack<float> y(5.321);

  foo(x);
  foo(nt2::exponentbits(1.f));
  foo(nt2::exponentbits(y));
  foo(nt2::cos(y) + nt2::cos(y)); // ok
  foo(nt2::plus(x , x) ); //  ok
  foo(nt2::plus(nt2::exponentbits(y) , 3) ); //  ok
  foo(nt2::plus(nt2::exponentbits(y) , nt2::exponentbits(y)) ); //  ok
  foo(nt2::plus(nt2::exponentbits(1.f) , x) ); //  ok
  foo(nt2::plus(nt2::exponentbits(1.f) , 3) ); //  ok
  foo(nt2::where(y,y,y) ); //  ok
  foo(nt2::where(1,2,y) ); //  ok
}
