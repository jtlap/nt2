//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_POLYNOM_FUNCTIONS_POLYVAL_HPP_INCLUDED
#define NT2_TOOLBOX_POLYNOM_FUNCTIONS_POLYVAL_HPP_INCLUDED
#include <nt2/include/simd.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/sdk/meta/tieable_hierarchy.hpp>
#include <nt2/core/container/dsl/value_type.hpp>
// polyval(p, x)
// This compute the valuation of a polynomial p of degree N at x
// The polynomial is supposed to be given by an array of N+1 elements
// in decreasing degrees order

namespace nt2 { namespace tag
  {         
    struct polyval_ : ext::tieable_<polyval_> { typedef ext::tieable_<polyval_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::polyval_, polyval, 2)
    NT2_FUNCTION_IMPLEMENTATION(tag::polyval_, polyval, 3)
    NT2_FUNCTION_IMPLEMENTATION(tag::polyval_, polyval, 5)
    NT2_FUNCTION_IMPLEMENTATION(tag::polyval_, polyval, 6)
}
 
 namespace nt2 { namespace ext
{
  template<class Domain, int N, class Expr>
  struct  size_of<tag::polyval_,Domain,N,Expr>
  {
    typedef typename  boost::proto::result_of::child_c<Expr&,1>::value_type::extent_type result_type;
    
    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      return boost::proto::child_c<1>(e).extent();
    }
  };

  template<class Domain, int N, class Expr>
  struct  value_type<tag::polyval_,Domain,N,Expr>
        : meta::value_as<Expr,0>
  {};
} }
#endif
