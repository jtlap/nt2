//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_COMMON_TIE_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_COMMON_TIE_HPP_INCLUDED

#include <nt2/core/functions/tie.hpp>
#include <boost/mpl/assert.hpp>
#include <nt2/include/functions/assign.hpp>

#include <boost/fusion/include/vector.hpp>

namespace boost { namespace dispatch { namespace meta
{
  template<class A0, class A1>
  struct value_of< boost::fusion::vector2<A0, A1> >
  {
    typedef boost::fusion::vector2< typename value_of<A0>::type, typename value_of<A1>::type > type;
  };
} } }

namespace nt2 { namespace ext
{
  template<class Domain, int N, class Expr>
  struct resize<tag::tie_, Domain, N, Expr>
  {
    template<class Sz>
    BOOST_FORCEINLINE void operator()(Expr& x, Sz const& sz)
    {
      boost::proto::child_c<0>(x).resize(sz);
      boost::proto::child_c<1>(x).resize(sz);
    }
  };

  // semantic of assigning a value to a fusion sequence is assumed to always
  // be valid if assigning the first element is
  // TODO: make nodes specify their semantic per output arity?
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::assign_, tag::cpu_
                            , (A0)(A1)
                            , (fusion_sequence_<A0>)
                              (generic_< unspecified_<A1> >)
                            )
  {
    typedef typename boost::fusion::result_of::at_c<A0, 0>::type first;
    typedef typename meta::scalar_of<first>::type first_scalar;
    typedef typename meta::call<tag::assign_(first_scalar, A1 const&)>::type result_type;
  };

#if 0
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_assign_, tag::cpu_
                            , (A0)(N0)(A1)
                            , ((node_<A0, nt2::tag::tie_, N0, nt2::container::domain>))
                              ((ast_<A1, nt2::container::domain>))
                            )
  {
    typedef A0& result_type;

    BOOST_FORCEINLINE result_type operator()(A0& a0, A1& ) const
    {
      //========================================================================
      //              ****NT2_INCORRECT_RHS_FOR_TIE_EXPRESSION****
      // If you trigger this static assertion, an invalid expression has been
      // assigned to a tie expression.
      //              ****NT2_INCORRECT_RHS_FOR_TIE_EXPRESSION****
      //========================================================================
      BOOST_MPL_ASSERT_MSG( (sizeof(A0) == 0)
                          , NT2_INCORRECT_RHS_FOR_TIE_EXPRESSION
                          , (A1)
                          );
      return a0;
    }
  };
#endif
} }

#endif
