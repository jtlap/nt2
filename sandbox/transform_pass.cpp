#include <boost/proto/debug.hpp>
#include <nt2/sdk/simd/pack.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/include/functions/fma.hpp>

#include <iostream>

namespace nt2
{

namespace tag
{
  struct optimize_ : cpu_
  {
  };
}
  
namespace meta
{
  template <class Tag>
  struct optimize
      : boost::proto::
        unpack< boost::proto::
                call< functor<Tag, tag::optimize_> >(compile< optimize < boost::mpl::_1 >
                                                                       , tag::cpu_
                                                                       >
                                                    )
              >
  {};

  template <>
  struct optimize<tag::terminal_>
        : boost::proto::_
  {};
} }

namespace boost { namespace proto
{
  template<class Tag>
  struct  is_callable<nt2::meta::optimize<Tag> >
        : boost::mpl::true_  {};
} }

NT2_REGISTER_DISPATCH ( tag::plus_ , tag::optimize_, (A0)(A1)(Dom)(Sema)
                      , ((expr_<A0,Dom,tag::multiplies_,Sema>))(unspecified_<A1>)
                      )

namespace nt2 { namespace ext
{
  template<class Domain,class Semantic,class Dummy>
  struct call < tag::plus_(tag::expr_<Domain,tag::multiplies_,Semantic>, tag::unspecified_)
              , tag::optimize_, Dummy
              >
        : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0, A1)>
      : meta::call< tag::fma_(
          typename boost::proto::result_of::child_c<A0, 0>::type,
          typename boost::proto::result_of::child_c<A0, 1>::type,
          A1
        ) >
    {};


    NT2_FUNCTOR_CALL(2)
    {
      return fma(boost::proto::child_c<0>(a0), boost::proto::child_c<1>(a0), a1);
    }
  };
} }

int main()
{
    using nt2::simd::pack;
    namespace proto = boost::proto;
    
    pack<float> a, b, c;
    
    int target;
    proto::display_expr(
      nt2::meta::compile<
        nt2::meta::optimize<boost::mpl::_1>
      , nt2::tag::cpu_
      >()
      (
        a * b + c
      )
    );
}
