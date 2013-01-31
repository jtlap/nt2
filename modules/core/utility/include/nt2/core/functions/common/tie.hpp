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
#include <nt2/include/functions/assign.hpp>
#include <boost/simd/sdk/meta/iterate.hpp>

#include <boost/dispatch/meta/value_of.hpp>
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
  // resizing a tie resizes all arguments
  template<class Domain, int N, class Expr>
  struct resize<tag::tie_, Domain, N, Expr>
  {
    template<class Sz>
    struct impl
    {
      BOOST_FORCEINLINE impl(Expr& x_, Sz const& sz_) : x(x_), sz(sz_) {}

      template<int I>
      BOOST_FORCEINLINE void operator()() const
      {
        boost::proto::child_c<I>(x).resize(sz);
      }

      Expr& x;
      Sz const& sz;
    };

    template<class Sz>
    BOOST_FORCEINLINE void operator()(Expr& x, Sz const& sz)
    {
      boost::simd::meta::iterate<N>(impl<Sz>(x, sz));
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
    typedef typename meta::call<tag::assign_(first, A1 const&)>::type result_type;
  };

  // semantic of assigning a fusion sequence to a fusion sequence is assumed
  // to always be valid if assigning the first element is
  // TODO: check other elements?
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::assign_, tag::cpu_
                            , (A0)(A1)
                            , (fusion_sequence_<A0>)
                              (fusion_sequence_<A1>)
                            )
  {
    typedef typename boost::fusion::result_of::at_c<A0, 0>::type first;
    typedef typename boost::fusion::result_of::at_c<A1, 0>::type first2;
    typedef typename meta::call<tag::assign_(first, first2)>::type result_type;
  };
} }

#endif
