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
#include <boost/dispatch/dsl/semantic_of.hpp>
#include <boost/dispatch/details/parameters.hpp>
#include <boost/fusion/include/as_vector.hpp>
#include <boost/mpl/transform.hpp>

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
/* `tie' constructs the node directly to avoid issues with ambiguous specializations;
 * should maybe be fixed in a different manner. */
#define M0(z,n,t) boost::ref(boost::proto::as_child(a##n))
#define M1(z,n,t) typename boost::proto::result_of::as_child<A##n>::type&

#define M2(z,n,t)                                                                 \
template<BOOST_PP_ENUM_PARAMS(n,class A)> BOOST_FORCEINLINE                       \
typename boost::proto::result_of::make_expr                                       \
         < nt2::tag::tie_, container::domain                                      \
         , BOOST_PP_ENUM(n,M1,~)                                                  \
         >::type                                                                  \
tie(BOOST_PP_ENUM_BINARY_PARAMS(n,A,& a))                                         \
{                                                                                 \
  return boost::proto::                                                           \
         make_expr<nt2::tag::tie_, container::domain>(BOOST_PP_ENUM(n,M0,~));     \
}                                                                                 \
/**/

BOOST_PP_REPEAT_FROM_TO(1,BOOST_DISPATCH_MAX_META_ARITY,M2,~)

#undef M0
#undef M1
#undef M2
}

namespace nt2 { namespace container { namespace ext
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

    typedef expression<base_t, semantic_t>                          result_type;

    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      return result_type(e);
    }
  };

  //============================================================================
  // INTERNAL ONLY
  // tie size is just <1>
  //============================================================================
  template<class Domain, class Expr>
  struct  size_of<nt2::tag::tie_,Domain,1,Expr>
  {
    typedef of_size_<1> result_type;
    BOOST_FORCEINLINE result_type operator()(Expr&) const
    {
      return result_type();
    }
  };

  template<class Domain, int N, class Expr>
  struct  size_of<nt2::tag::tie_,Domain,N,Expr>
  {
    typedef of_size_<1> result_type;
    BOOST_FORCEINLINE result_type operator()(Expr&) const
    {
      return result_type();
    }
  };
} } }

#endif
