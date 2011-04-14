#include <boost/proto/debug.hpp>
#include <nt2/sdk/simd/pack.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/include/functions/fma.hpp>

namespace nt2
{

namespace tag
{
  struct recognition_ : formal_
  {
  };
}
  
namespace meta
{
  template <class Tag>
  struct recognition_
      : boost::proto::
        unpack< boost::proto::
                call< functor<Tag, tag::recognition_> >(compile< recognition_ < boost::mpl::_1 >
                                                            >
                                                    )
              >
  {};

  template <>
  struct recognition_<tag::terminal_>
        : boost::proto::_
  {};
} }

namespace boost { namespace proto
{
  template<class Tag>
  struct  is_callable<nt2::meta::recognition_<Tag> >
        : boost::mpl::true_  {};
} }

NT2_REGISTER_DISPATCH ( tag::plus_ , tag::recognition_, (A0)(A1)(Dom)(Sema)
                      , ((expr_<A0,Dom,tag::multiplies_,Sema>))(unspecified_<A1>)
                      )

namespace nt2 { namespace ext
{
  template<class Domain,class Semantic,class Dummy>
  struct call < tag::plus_(tag::expr_<Domain,tag::multiplies_,Semantic>, tag::unspecified_)
              , tag::recognition_, Dummy
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

NT2_REGISTER_DISPATCH ( tag::plus_ , tag::recognition_, (A0)(A1)(Dom)(Sema)
                      , (unspecified_<A0>)((expr_<A1,Dom,tag::multiplies_,Sema>))
                      )

namespace nt2 { namespace ext
{
  template<class Domain,class Semantic,class Dummy>
  struct call < tag::plus_(tag::unspecified_, tag::expr_<Domain,tag::multiplies_,Semantic>)
              , tag::recognition_, Dummy
              >
        : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0, A1)>
      : meta::call< tag::fma_(
          typename boost::proto::result_of::child_c<A1, 0>::type,
          typename boost::proto::result_of::child_c<A1, 1>::type,
          A0
        ) >
    {};


    NT2_FUNCTOR_CALL(2)
    {
      return fma(boost::proto::child_c<0>(a1), boost::proto::child_c<1>(a1), a0);
    }
  };
} }

int main()
{
    using nt2::simd::pack;
    namespace proto = boost::proto;
    
    pack<float> a, b, c, d;
    
    int target;
    proto::display_expr(
      nt2::meta::compile<
        nt2::meta::recognition_<boost::mpl::_1>
      >()
      (
        a + b * (a + b * (a + b * (a + b * c)))
      + b * (b * (b * (b * c + a) + a) + a) + a
      )
    );
}
