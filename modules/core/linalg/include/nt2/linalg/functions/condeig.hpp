//==============================================================================
//          Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_CONDEIG_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_CONDEIG_HPP_INCLUDED

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
    struct condeig_ :  ext::tieable_<condeig_>
    {
      typedef ext::tieable_<condeig_>  parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_condeig_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site>
    BOOST_FORCEINLINE generic_dispatcher<tag::condeig_, Site> dispatching_condeig_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
    {
      return generic_dispatcher<tag::condeig_, Site>();
    }
    template<class... Args>
    struct impl_condeig_;
  }

  NT2_FUNCTION_IMPLEMENTATION(tag::condeig_, condeig, 1)

  /**
   * Condeig condition number with respect to eigenvalues.
   *    condeig(a) is a vector of condition numbers for the eigenvalues
   *    of a. these condition numbers are the reciprocals of the cosines
   *    of the angles between the left and right eigenvectors.
   *        tie(v,d,s) = condeig(a) is equivalent to:
   *        tie(v,d) = eig(a); s = condeig(a);
   *
   *        tie(v,d,y,s) = condeig(a) is equivalent to:
   *        tie(v,d,y) = eig(a); s = condeig(a);
   *
   *    large condition numbers imply that a is near a matrix with
   *    multiple eigenvalues.
   *
   *    note:
   *    condeig returns the reciprocals of the wilkinson s(lambda) numbers.
   *
   *    @see funcref{cond}.
   *
   *    Reference:
   *    [1] G.H. Golub and C.F. Van Loan, Matrix Computations, Third
   *        Edition, Johns Hopkins University Press, Baltimore, Maryland,
   *        1996, sec. 7.2.2. p 323
   **/
}

namespace nt2 { namespace ext
{
  template<class Domain, int N, class Expr>
  struct  size_of<tag::condeig_,Domain,N,Expr>
        : meta::size_as<Expr,0>
  {};

  template<class Domain, int N, class Expr>
  struct  value_type<tag::condeig_,Domain,N,Expr>
        : meta::value_as<Expr,0>
  {};
} }

#endif
