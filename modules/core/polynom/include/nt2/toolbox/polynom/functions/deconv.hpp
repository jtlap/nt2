//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_POLYNOM_FUNCTIONS_DECONV_HPP_INCLUDED
#define NT2_TOOLBOX_POLYNOM_FUNCTIONS_DECONV_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/sdk/meta/tieable_hierarchy.hpp>
#include <nt2/core/container/dsl/value_type.hpp>
// tie(p, q) = deconv(a, b)
// This compute the deconvolution of a polynomial a by a polynomial b
// i.e. division returning quotent and remainder,
// such that a = polyadd(conv(a, q), r)
// The polynomials are supposed to be given by an array of elements
// in decreasing degrees order

namespace nt2 { namespace tag
  {
    struct deconv_ : ext::tieable_<deconv_> { typedef ext::tieable_<deconv_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::deconv_, deconv, 2)
}

 namespace nt2 { namespace ext
{
  template<class Domain, int N, class Expr>
  struct  size_of<tag::deconv_,Domain,N,Expr>
  {
    typedef _2D result_type;

    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      _2D sizee;
      sizee[0] = 1;
      sizee[1] = nt2::numel(boost::proto::child_c<0>(e)) > nt2::numel(boost::proto::child_c<1>(e)) ?
        nt2::numel(boost::proto::child_c<0>(e))-nt2::numel(boost::proto::child_c<1>(e))+1 : 0;
      return sizee;
    }
  };

  template<class Domain, int N, class Expr>
  struct  value_type<tag::deconv_,Domain,N,Expr>
        : meta::value_as<Expr,0>
  {};
} }
#endif
