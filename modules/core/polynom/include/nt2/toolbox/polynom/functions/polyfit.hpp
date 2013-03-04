//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_POLYNOM_FUNCTIONS_POLYFIT_HPP_INCLUDED
#define NT2_TOOLBOX_POLYNOM_FUNCTIONS_POLYFIT_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/sdk/meta/tieable_hierarchy.hpp>
#include <nt2/core/container/dsl/value_type.hpp>

namespace nt2 { namespace tag
  {
    struct polyfit_ : ext::tieable_<polyfit_> { typedef ext::tieable_<polyfit_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::polyfit_, polyfit, 2)
  NT2_FUNCTION_IMPLEMENTATION(tag::polyfit_, polyfit, 3)
}

 namespace nt2 { namespace ext
{
  template<class Domain, int N, class Expr>
  struct  size_of<tag::polyfit_,Domain,N,Expr>
  {
    typedef _2D result_type;

    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      _2D sizee;
      sizee[0] = 1;
      sizee[1] = size_t(boost::proto::child_c<2>(e))+1;
      return sizee;
    }
  };
  template<class Domain, class Expr>
  struct  size_of<tag::polyfit_,Domain,2,Expr>
  {
    typedef _2D result_type;

    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      _2D sizee;
      sizee[0] = 1;
      sizee[1] = nt2::numel(boost::proto::child_c<0>(e))+1u;
      return sizee;
    }
  };


  template<class Domain, int N, class Expr>
  struct  value_type<tag::polyfit_,Domain,N,Expr>
        : meta::value_as<Expr,0>
  {};
} }
#endif
