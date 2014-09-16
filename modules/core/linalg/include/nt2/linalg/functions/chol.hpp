//==============================================================================
//         Copyright 2014                 Jean-Thierry Lapresté
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_CHOL_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_CHOL_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/sdk/meta/tieable_hierarchy.hpp>

namespace nt2
{
  namespace tag
  {
    struct chol_ : ext::tieable_<chol_>
    {
      typedef ext::tieable_<chol_>  parent;
    };
  }

  /**
     @brief Cholevski factorization of an hermitian
     (symetric in the real case) positive definite matrix.

     r = chol(a)
     l = chol(a,lower_)
     r = chol(a,upper_)
     [r,p] = chol(a)
     [l,p] = chol(a,lower_)
     [r,p] = chol(a,upper_)

     The three first calls assert if a is not positive definite.
     The three last call return a (p-1)X(p-1) matrix where p is
     the dimension of the smallest minor of a which is not positive
     definite. Then r (resp. l) gives the factor of the preeceding minor.

     upper_ (resp. lower_) indicates that only the upper (resp. lower)
     part of the a storage are referenced. Default is upper_.
     This also means that the  hermitianity (symetry in the real case)
     of the matrix is never tested.

     The options tags are in nt2 namespace.

     If the factorization is completed  a = ctrans(r)*r or
     a = l*ctrans(l) according to the option chosen.
   **/

  NT2_FUNCTION_IMPLEMENTATION(tag::chol_, chol, 1)
  NT2_FUNCTION_IMPLEMENTATION(tag::chol_, chol, 2)
}

namespace nt2 { namespace ext
{
  template<class Domain, int N, class Expr>
  struct  size_of<tag::chol_,Domain,N,Expr>
        : meta::size_as<Expr,0>
  {};
} }

#endif
