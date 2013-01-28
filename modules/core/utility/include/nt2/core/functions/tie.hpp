//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_TIE_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_TIE_HPP_INCLUDED

/*!
 * \file
 * \brief Defines and implements the nt2::tie function
 */

#include <nt2/include/functor.hpp>
#include <nt2/core/utility/of_size.hpp>
#include <nt2/core/container/dsl/generator.hpp>
#include <nt2/core/container/dsl/expression.hpp>

#include <boost/mpl/transform.hpp>
#include <boost/dispatch/dsl/semantic_of.hpp>
#include <boost/fusion/include/as_vector.hpp>

#include <boost/dispatch/details/parameters.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>

namespace nt2
{
  namespace tag
  {
    struct tie_ : ext::elementwise_<tie_>
    {
      typedef ext::elementwise_<tie_> parent;
    };
  }

  //============================================================================
  /*!
   * Tie terminals for multi-return function handling
   */
  //============================================================================
#define M0(z,n,t)                                                                 \
template<BOOST_PP_ENUM_PARAMS(n,class A)> BOOST_FORCEINLINE                       \
typename boost::dispatch::meta::                                                  \
         call<tag::tie_(BOOST_PP_ENUM_BINARY_PARAMS(n, A, t & BOOST_PP_INTERCEPT))>::type \
tie(BOOST_PP_ENUM_BINARY_PARAMS(n,A,t & a))                                       \
{                                                                                 \
  return typename boost::dispatch::make_functor<tag::tie_, A0>::type()            \
         (BOOST_PP_ENUM_PARAMS(n, a));                                            \
}                                                                                 \
/**/

// FIXME: needs perfect forwarding
BOOST_PP_REPEAT_FROM_TO(1,BOOST_DISPATCH_MAX_META_ARITY,M0,BOOST_PP_EMPTY())
BOOST_PP_REPEAT_FROM_TO(1,BOOST_DISPATCH_MAX_META_ARITY,M0,const)
#undef M0
}

//==============================================================================
// Specify tie node generation processs
//==============================================================================
namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  template<class Domain, int N, class Expr>
  struct  size_of<nt2::tag::tie_,Domain,N,Expr>
  {
    typedef typename boost::proto::result_of::child_c<Expr&, 0>::value_type child0;
    typedef typename child0::extent_type const& result_type;

    BOOST_FORCEINLINE result_type operator()(Expr& expr) const
    {
      return boost::proto::child_c<0>(expr).extent();
    }
  };
} }

namespace nt2 { namespace details
{
  //============================================================================
  // INTERNAL ONLY
  // tie semantic is a fusion sequence and don't carry any special meaning.
  //============================================================================
  template<class Domain, int N, class Expr>
  struct  generator<nt2::tag::tie_,Domain,N,Expr>
  {
    typedef typename boost::remove_const<Expr>::type                    base_t;
    typedef typename boost::fusion::result_of::as_vector<base_t>::type  sem_t;
    typedef typename boost::mpl::transform< sem_t
                                          , boost::dispatch::meta
                                                 ::semantic_of<boost::mpl::_>
                                          >::type                   semantic_t;

    typedef container::expression<base_t, semantic_t>               result_type;

    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      return result_type(e);
    }
  };
} }

#endif
