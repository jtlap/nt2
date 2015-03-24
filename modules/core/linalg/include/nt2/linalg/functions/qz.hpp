//==============================================================================
//         Copyright 2014 - 2015  Jean-Thierry Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_QZ_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_QZ_HPP_INCLUDED

#include <nt2/linalg/options.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/tieable_hierarchy.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/sdk/meta/size_as.hpp>

namespace nt2 {
  namespace tag {
    struct qz_ : ext::tieable_<qz_>
    {
      typedef ext::tieable_<qz_>  parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_qz_( ext::adl_helper(),
                                static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext {
    template<class Site>
    BOOST_FORCEINLINE generic_dispatcher<tag::qz_, Site> dispatching_qz_(adl_helper,
        boost::dispatch::meta::unknown_<Site>, ...)
    {
      return generic_dispatcher<tag::qz_, Site>();
    }
    template<class... Args>
    struct impl_qz_;
  }

  /**
   * @brief Perform qz generalized factorization
   *
   * For any given matrix expression, performs a Qz factorization of
   * said matrix using the specified output layout for the Qz method.
   *
   *
   * possible calls are
   * t =  qz(a);
   *     if a is complex, the complex qz form is returned in matrix t.
   *     the complex qz form is upper triangular with the eigenvalues
   *     of a on the diagonal.
   *
   *     if a is real, or has only real elements two different decompositions are available.
   *     t = qz(a,real_) has the real eigenvalues on the diagonal and the
   *     complex eigenvalues in 2-by-2 blocks on the diagonal.
   *     t = qz(a,cmplx_) is triangular and is complex.
   *     t = qz(a,real_) is the default for real types entry and in this case is equivalent to
   *     t = qz(a). For complex types entry the complex form is the default and in this case
   *     t = qz(a,cmplx_) is equivalent to qz(a).
   *
   * t =  qz(a, real_);   // all a coefficients must contain real values
   * t =  qz(a, cmplx_);  // t must be able to receive complex elts
   *
   * tie(u, t) = qz(a, ...) also returns the unitary (orthogonal in the real_ case) matrix u
   *                        such that u*t*ctrans(u) ==  a
   * tie(u, t, w) = qz(a, ...) returns also the vector w containing the eigenvalues of a (w
   *                           is mandatorily complex)
   *
   *
   **/
  NT2_FUNCTION_IMPLEMENTATION(tag::qz_, qz, 2)
  NT2_FUNCTION_IMPLEMENTATION(tag::qz_, qz, 3)
  NT2_FUNCTION_IMPLEMENTATION(tag::qz_, qz, 4)
}

namespace nt2 {
  namespace ext {
    template<class Domain, int N, class Expr>
    struct  size_of<tag::qz_,Domain,N,Expr>
      : meta::size_as<Expr,0>
    {};
  }
}

#endif
