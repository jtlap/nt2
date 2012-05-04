//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_REDUCTION_FUNCTIONS_CONTAINER_SUM_HPP_INCLUDED
#define NT2_TOOLBOX_REDUCTION_FUNCTIONS_CONTAINER_SUM_HPP_INCLUDED

#include <nt2/toolbox/reduction/functions/sum.hpp>
#include <boost/simd/toolbox/reduction/functions/sum.hpp>
#include <nt2/core/container/dsl/details/reduction.hpp>
#include <nt2/core/container/dsl/size.hpp>

namespace nt2 { namespace container { namespace ext
{
  template<class Domain, class Expr>
  struct size_of<boost::simd::tag::sum_,Domain,1,Expr>
    : reduction_size_of<boost::simd::tag::sum_, 1, Expr>{};

  template<class Domain, class Expr>
  struct size_of<boost::simd::tag::sum_,Domain,2,Expr>
    : reduction_size_of<boost::simd::tag::sum_, 2, Expr>{};

  template<class Domain, int N, class Expr>
  struct generator<boost::simd::tag::sum_,Domain,N,Expr>
    : reduction_generator<boost::simd::tag::sum_,N,Expr> {};
} } }

#endif
