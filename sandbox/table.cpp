#include <iostream>
//#include <boost/proto/debug.hpp>
#include <nt2/sdk/details/type_id.hpp>

#include <nt2/sdk/timing/ctic.hpp>
#include <nt2/include/functions/cos.hpp>
#include <nt2/include/functions/sin.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/core/container/colon/colon.hpp>
#include <nt2/toolbox/operator/functions.hpp>

#include <boost/simd/sdk/simd/meta/vector_of.hpp>
#include <boost/simd/sdk/simd/meta/native_cardinal.hpp>
#include <boost/simd/sdk/simd/meta/is_vectorizable.hpp>

namespace nt2 { namespace ext
{
  // terminal, does load
  NT2_FUNCTOR_IMPLEMENTATION_TPL( nt2::tag::terminal_, tag::cpu_
                                , (class A0)(class S0)(class State)
                                , ((ast_<table_< unspecified_<A0>, S0 > >))
                                  (fusion_sequence_<State>)
                                )
  {
    typedef typename boost::dispatch::meta::
    scalar_of< typename boost::dispatch::meta::
               semantic_of<A0>::type
             >::type                                       result_type;
    
    result_type operator()(A0 const& a0, State const& state) const
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

using nt2::container::table;
using nt2::_;

#include <vector>

template< class T
        , bool Enable = boost::simd::
                        meta::is_vectorizable<T,BOOST_SIMD_DEFAULT_EXTENSION>::value
        > 
struct evaluation_type
{
  typedef nt2::meta::as_<T> type;
};

template<class T> 
struct  evaluation_type<T, true> 
{
  typedef typename boost::simd::meta::
          vector_of<T, boost::simd::meta::native_cardinal<T>::value>::type base;
  typedef nt2::meta::as_<base>                                             type;
};

struct foo { int i; int j; };

int main()
{
  int iter, d0,d1;
  std::cin >> iter >> d0 >> d1;
  std::vector<double> cc;

  static table<float,nt2::_2D> a( nt2::of_size(d0,d1) );

  for(int i=0;i<iter;++i)
  {
    nt2::ctic();
    a = nt2::cos(a);
    cc.push_back(nt2::ctoc(false)/(1.*d0*d1));
  }

  std::sort(cc.begin(),cc.end());

  std::cout << cc[cc.size()/2 - 1] << " c/elements\n";

#if 0
  a = -(b + c*(a+(c * -c))) + b;
  a = b + c;
  a = -b;
  b += c;
  c += -a;
  //c(a) += a;                // function undefined
  //c(a) = b(c) + c(a)*b(a);
#endif
}
