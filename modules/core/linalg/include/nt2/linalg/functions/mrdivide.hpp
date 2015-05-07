//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_MRDIVIDE_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_MRDIVIDE_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/core/container/dsl/value_type.hpp>
#include <nt2/sdk/meta/tieable_hierarchy.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/meta/value_as.hpp>

namespace nt2
{
  namespace tag
  {
    struct mrdivide_ : ext::tieable_<mrdivide_>
    {
      typedef ext::tieable_<mrdivide_>  parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_mrdivide_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site>
    BOOST_FORCEINLINE generic_dispatcher<tag::mrdivide_, Site>
    dispatching_mrdivide_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
    {
      return generic_dispatcher<tag::mrdivide_, Site>();
    }
    template<class... Args>
    struct impl_mrdivide_;
  }

  /**
   * @briefsolve a (left) linear system xa = b (x unknown)
   *
   * solve for x the system xa = b ( c = ctrans(linsolve(ctrans(a), ctrans(b));
   *
   * @code
   *      T x = mrdivide(b, a {, option});
   * @encode
   *
   *    is similar to
   *
   * @code
   *      T x = ctrans(linsolve(ctrans(a), ctrans(b) {, option});
   * @encode
   *
   * Note : @code tie(x, r) = mrdivide(b, a {, option}); @encode
   * also returns the inverse condition number r of a

   * @see @{linsolve} @{mldivide}

   * @param  b right hand side of the equation
   * @param  a matrix of the equation
   *
   * @return the solution of the system
   **/

  NT2_FUNCTION_IMPLEMENTATION(tag::mrdivide_, mrdivide, 2)
  NT2_FUNCTION_IMPLEMENTATION(tag::mrdivide_, mrdivide, 3)
}

namespace nt2 { namespace ext
{
  template<class Domain, int N, class Expr>
  struct  size_of<tag::mrdivide_,Domain,N,Expr>
        : meta::size_as<Expr,1>
  {};

  template<class Domain, int N, class Expr>
  struct  value_type<tag::mrdivide_,Domain,N,Expr>
        : meta::value_as<Expr,0>
  {};

} }

#endif
