#include <iostream>
//#define BOOST_PROTO_STRICT_RESULT_OF

#include <nt2/sdk/details/type_id.hpp>
#include <nt2/sdk/simd/pack.hpp>
#include <nt2/sdk/dsl/compute.hpp>

using namespace std;

NT2_REGISTER_DISPATCH(tag::terminal_,tag::cpu_
                     ,(A0)(A1)(A2)(X)
                     ,((simd_<arithmetic_<A0>,X>))(int32_<A1>)(int32_<A2>)
                     )

namespace nt2 { namespace ext
{
  template<class Dummy,class X>
  struct call<tag::terminal_(tag::simd_<tag::arithmetic_,X>,tag::int32_,tag::int32_),tag::cpu_,Dummy>
  : callable
  {
    template<class Sig> struct result;

    template<class This, class Value, class State, class Data>
    struct result<This(Value,State,Data)>
    {
      typedef typename meta::strip<Value>::type::parent type;
    };

    template<class Value, class State, class Data> inline
    typename result<call(Value,State,Data)>::type
    operator()( Value& v, State& , Data&  ) const
    {
      return v.value();
    }
  };
} }


int main()
{
  nt2::simd::pack<float> y(5.321);

  nt2::meta::compile< nt2::meta::compute, nt2::tag::cpu_ > compiler;

  std::cout << compiler(y) << "\n";

  std::cout << compiler(y+y) << "\n";
}
