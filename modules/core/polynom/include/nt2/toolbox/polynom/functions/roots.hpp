//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_POLYNOM_FUNCTIONS_ROOTS_HPP_INCLUDED
#define NT2_TOOLBOX_POLYNOM_FUNCTIONS_ROOTS_HPP_INCLUDED
#include <nt2/include/simd.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/sdk/meta/tieable_hierarchy.hpp>
#include <nt2/core/container/dsl/value_type.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>

// roots(p, x)
// This compute the roots of a polynomial p of degree N 
// The polynomial is supposed to be given by an array of N+1 elements
// in decreasing degrees order. The type of returned roots is always
// the complexification of the input data type. Use realroots if you only want the real
// roots in "real" form.

namespace nt2 { namespace tag
  {         
    struct roots_ : ext::unspecified_<roots_> { typedef ext::unspecified_<roots_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::roots_, roots, 1)
 
}
 
 namespace nt2 { namespace ext
{
  template<class Domain, int N, class Expr>
  struct  size_of<tag::roots_,Domain,N,Expr>
  {
    typedef typename  boost::proto::result_of::child_c<Expr&,0>::value_type::extent_type result_type;
    
    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      result_type sizee = boost::proto::child_c<0>(e).extent();
      sizee[1] = sizee[1]? sizee[1]-1 : 0; 
      return sizee; 
    }
  };

  template<class Domain, int N, class Expr>
  struct  value_type<tag::roots_,Domain,N,Expr>
  {
    typedef typename  boost::proto::result_of
               ::child_c<Expr&,0>::value_type::value_type  intype;
    typedef typename meta::as_complex<intype>::type type; 
  };
} }
#endif
