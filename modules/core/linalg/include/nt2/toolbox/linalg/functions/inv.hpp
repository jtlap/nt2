//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_INV_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_INV_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>
#include <nt2/sdk/memory/container.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/value_type.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/include/functions/issquare.hpp>

/*!
 * @brief inv  inverse of square matrix.
 * inv(x) is the inverse of the square matrix expression x.
 *
 * Avoid to use this function if you do not have a very good reason
 * and whatsoever never use it to solve linear systems.
 * 99% of the time a solver is a better choice.
 **/

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag inv_ of functor inv
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct inv_ :  ext::unspecified_<inv_> { typedef ext::unspecified_<inv_> parent; };
  }

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::inv_, inv, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::inv_, inv, 2)
}

namespace nt2 { namespace ext
{
  template<class Domain, class Expr,  int N> //N == 1 only
  struct  size_of<tag::inv_, Domain, N, Expr>
  {
    typedef typename boost::proto::result_of::child_c<Expr&,0>::value_type  c0_t;
    typedef typename c0_t::extent_type                               result_type;
    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      result_type sizee = boost::proto::child_c<0>(e).extent();
      BOOST_ASSERT_MSG(issquare(boost::proto::child_c<0>(e)),
                       "inverse of non square matrix expression requested");
      return sizee;
    }
  };

 template <class Domain, class Expr,  int N>
 struct value_type < tag::inv_, Domain,N,Expr>
  : meta::value_as<Expr,0>
 {};
} }


#endif

