//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_EXPONENTIAL_FUNCTIONS_SCALAR_LOG2_HPP_INCLUDED
#define NT2_TOOLBOX_EXPONENTIAL_FUNCTIONS_SCALAR_LOG2_HPP_INCLUDED

#include <nt2/toolbox/exponential/functions/log2.hpp>
#include <nt2/toolbox/exponential/functions/scalar/impl/logs.hpp>
#include <nt2/include/functions/frexp.hpp>


namespace nt2 { namespace ext
{
//   NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::log2_, tag::cpu_
//                             , (A0)
//                               ,  (scalar_< arithmetic_<A0> >)
//                             )
//   {
//     typedef typename  boost::proto::
//                       result_of::make_expr< nt2::tag::log2_
//                                           , container::domain
//                                           , A0 const&
//                                           >::type             result_type;

//     BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
//     {
//       return boost::proto::make_expr< nt2::tag::log2_
//                                     , container::domain
//                                     > ( boost::cref(a0));
//     }
//   };
//   //============================================================================
//   // This version of log2 is called whenever a tie(...) = log2(...) is captured
//   // before assign is resolved. As a tieable function, log2 retrieves rhs/lhs
//   // pair as inputs
//   //============================================================================
//   NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::log2_, tag::cpu_
//                               , (A0)(N0)(A1)(N1)
//                               , ((node_<A0, nt2::tag::log2_, N0>))
//                               ((node_<A1, nt2::tag::tie_ , N1>))
//                             )
//   {
//     typedef void                                                    result_type;
//     typedef typename boost::proto::result_of::child_c<A1&,0>::type       child0;
//     typedef typename A0::value_type                                  value_type;
//     typedef typename meta::as_integer<value_type>::type                  i_type;
//     BOOST_FORCEINLINE result_type operator()( A0& a0, A1& a1 ) const
//     {
//       compute(a0, a1, N1());
//     }

//     private:

//     //==========================================================================
//     // INTERNAL ONLY
//     // fill the args out
//     //==========================================================================
//     BOOST_FORCEINLINE
//     void compute(A0 & a0, A1 & a1, boost::mpl::long_<1> const&) const
//     {
//       value_type a = boost::proto::value(boost::proto::child_c<0>(a0));
//       boost::proto::child_c<0>(a1) = nt2::log2b(a);
//     }

//     BOOST_FORCEINLINE
//     void compute(A0& a0, A1 & a1, boost::mpl::long_<2> const&) const
//     {
//       value_type a = boost::proto::child_c<0>(a0);
//       i_type e;
//       value_type f = frexp(a, e);
//       boost::proto::child_c<0>(a1) = f;
//       boost::proto::child_c<1>(a1) = e;
//     }

//   };

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::log2_, tag::cpu_
                            , (A0)
                            , (scalar_< arithmetic_<A0> >)
                            )
  {

    typedef typename boost::dispatch::meta::as_floating<A0>::type result_type;

    NT2_FUNCTOR_CALL(1)
    {
      return nt2::log2(result_type(a0));
    }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is floating_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::log2_, tag::cpu_
                            , (A0)
                            , (scalar_< floating_<A0> >)
                            )
  {

    typedef typename boost::dispatch::meta::as_floating<A0>::type result_type;

    NT2_FUNCTOR_CALL(1)
    {
      return impl::logarithm<A0, tag::not_simd_type>::log2(a0);
    }
  };
} }


#endif
