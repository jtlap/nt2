//==============================================================================
//         Copyright 2003 - 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_LSQNONNEG_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_LSQNONNEG_HPP_INCLUDED

#include <nt2/linalg/options.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/sdk/meta/tieable_hierarchy.hpp>
#include <nt2/core/container/dsl/value_type.hpp>


namespace nt2
{
  namespace tag
  {
    struct lsqnonneg_ :  ext::tieable_<lsqnonneg_>
    {
      typedef ext::tieable_<lsqnonneg_>  parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_lsqnonneg_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site>
    BOOST_FORCEINLINE generic_dispatcher<tag::lsqnonneg_, Site> dispatching_lsqnonneg_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
    {
      return generic_dispatcher<tag::lsqnonneg_, Site>();
    }
    template<class... Args>
    struct impl_lsqnonneg_;
  }

  NT2_FUNCTION_IMPLEMENTATION(tag::lsqnonneg_, lsqnonneg, 2)
  NT2_FUNCTION_IMPLEMENTATION(tag::lsqnonneg_, lsqnonneg, 3)
  /*
   *  @brief returns the vector x that minimizes norm(d-mtimes(c, x))
   *  subject to x >= 0. c and d must be real resp matrix
   *  and vector expressions.
   *
   *  @code
   *   tie(x{, resnorm, residual, exitflag, nbiter, lambda}) =  lsqnonneg(c, d);
   *  @endcode
   *
   * @param c real matrix
   * @param d real column vector
   * @param x argmin(norm(d-mtimes(c, x)), x >= 0)
   * if present
   * @param resnorm is norm(d-mtimes(c, x)) for the found soulution
   * @param residual is d-mtimes(c, x)
   * @param exitflag is 1 process converged 0 if the maximum
            number of internal iterations (3*length(c)) has been exceeded
   * @param nbiter number of external iterations
   * @param lambda is the dual vector ( lambda(i) <= 0 when x(i) is (approximately) 0
   *        and lambda(i) is (approximately) 0 when x(i) > 0.
  */
}

namespace nt2 { namespace ext
{
  template<class Domain, int N, class Expr>
  struct  size_of<tag::lsqnonneg_,Domain,N,Expr>
        : meta::size_as<Expr,0>
  {};

  template<class Domain, int N, class Expr>
  struct  value_type<tag::lsqnonneg_,Domain,N,Expr>
        : meta::value_as<Expr,0>
  {};
} }

#endif
