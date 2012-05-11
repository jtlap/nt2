//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_REDUCTION_FUNCTIONS_CONTAINER_PROD_HPP_INCLUDED
#define NT2_TOOLBOX_REDUCTION_FUNCTIONS_CONTAINER_PROD_HPP_INCLUDED

#include <nt2/toolbox/reduction/functions/prod.hpp>
#include <boost/simd/toolbox/reduction/functions/prod.hpp>
#include <nt2/core/container/dsl/details/reduction.hpp>
#include <nt2/core/container/dsl/size.hpp>

#include <nt2/include/functions/multiplies.hpp>
#include <nt2/include/constants/one.hpp>

namespace nt2 { namespace container { namespace ext
{
  template<class Domain, class Expr>
  struct size_of<boost::simd::tag::prod_,Domain,1,Expr>
    : reduction_size_of<boost::simd::tag::prod_, 1, Expr>{};

  template<class Domain, class Expr>
  struct size_of<boost::simd::tag::prod_,Domain,2,Expr>
    : reduction_size_of<boost::simd::tag::prod_, 2, Expr>{};

  template<class Domain, class Expr, int N>
  struct generator<boost::simd::tag::prod_,Domain,N,Expr>
    : reduction_generator<boost::simd::tag::prod_,N,Expr> {};
} } }

#endif
