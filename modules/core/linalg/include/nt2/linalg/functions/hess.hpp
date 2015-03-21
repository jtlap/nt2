//==============================================================================
//         Copyright 2014 - Jean-Thierry Lapresté
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_HESS_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_HESS_HPP_INCLUDED

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
    struct hess_ : ext::tieable_<hess_>
    {
      typedef ext::tieable_<hess_>  parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_hess_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site>
    BOOST_FORCEINLINE generic_dispatcher<tag::hess_, Site> dispatching_hess_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
    {
      return generic_dispatcher<tag::hess_, Site>();
    }
    template<class... Args>
    struct impl_hess_;
  }

  /**
     @brief the hess functor finds  the Hessenberg form of matrix a.

     h = hess(a)

     tie(h, q) = hess(a)

     tie(aa, bb{, q{, z}}) = hess(a, b)

     tie(h, q) = hess(a) produces a hessenberg matrix h and a unitary matrix p
     so that a = mtimes(mtimes(q, h), ctrans(q)).

     tie(h, r, q, z) = hess(a, b) produces an upper hessenberg matrix h,
     an upper triangular matrix r, and unitary matrices q and z such that
     mtimes(mtimes(q, h), ctrans(z)) = a and mtimes(mtimes(q, r, ctrans(z)) = b.

     Note : Be aware that are not exactly the Matlab outputs.

     The hessenberg form of a matrix is zero below the first subdiagonal.
     If the matrix is symmetric or hermitian, the form is tridiagonal.

     hess can transform a general eigenvalue problem ax = lbx in hx = lrx,
     where h is hessenberg and r triangular.
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::hess_, hess, 1)
  NT2_FUNCTION_IMPLEMENTATION(tag::hess_, hess, 2)
}

namespace nt2 { namespace ext
{
  template<class Domain, int N, class Expr>
  struct  size_of<tag::hess_,Domain,N,Expr>
        : meta::size_as<Expr,0>
  {};
} }

#endif
