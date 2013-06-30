//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_FUNM_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_FUNM_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/sdk/meta/tieable_hierarchy.hpp>
#include <nt2/core/container/dsl/value_type.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/include/functions/issquare.hpp>
#include <boost/assert.hpp>

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag funm_ of functor funm
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct funm_ :   ext::tieable_<funm_>
    {
      typedef ext::tieable_<funm_>  parent;
    };
  }
  /**
   * @brief funm(f, a) evaluates the functor fun at the square
   * matrix expression a. fun(x,k) must return the k'th derivative of the function
   * represented by f evaluated at the vector x.
   *
   * @return a matrix containing funm(f, a)
   **/


  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::funm_, funm, 2)

}

namespace nt2 { namespace ext
{
  template<class Domain, int N, class Expr>
  struct  size_of<tag::funm_,Domain,N,Expr>
  {
    typedef typename boost::proto::result_of::child_c<Expr&,1>::value_type  c0_t;
    typedef typename c0_t::extent_type                               result_type;
    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      BOOST_ASSERT_MSG(issquare(boost::proto::child_c<1>(e)),
                       "funm needs a square matrix expression");

      return boost::proto::child_c<1>(e).extent();
    }
  };

  template<class Domain, int N, class Expr>
  struct  value_type<tag::funm_,Domain,N,Expr>
        : meta::value_as<Expr,1>
  {};
} }
#endif

