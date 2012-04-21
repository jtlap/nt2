//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_REDUCTION_FUNCTIONS_CONTAINER_MAXIMUM_HPP_INCLUDED
#define NT2_TOOLBOX_REDUCTION_FUNCTIONS_CONTAINER_MAXIMUM_HPP_INCLUDED

#include <boost/simd/toolbox/reduction/functions/maximum.hpp>
#include <nt2/core/container/dsl/details/reduction.hpp>
#include <nt2/core/container/colon/colon.hpp>
#include <nt2/core/container/dsl/size.hpp>

namespace nt2
{
  template<class A0,class A1> BOOST_FORCEINLINE
  typename boost::dispatch::meta::call<tag::maximum_ (A0 const&, A1 const&)>::type
  maximum(A0 const& a0,meta::as_<details::empty_t> const&,A1 const& a1)
  {
    typename boost::dispatch::make_functor<tag::maximum_, A0>::type callee;
    return callee(a0,a1);
  }

  template<class A0,class A1> BOOST_FORCEINLINE
  typename boost::dispatch::meta::call<tag::maximum_ (A0 const&, A1 const&)>::type
  max(A0 const& a0,meta::as_<details::empty_t> const&,A1 const& a1)
  {
    typename boost::dispatch::make_functor<tag::maximum_, A0>::type callee;
    return callee(a0,a1);
  }
}

namespace nt2 { namespace container { namespace ext
{
  template<class Domain, class Expr>
  struct size_of<boost::simd::tag::maximum_,Domain,1,Expr>
    : reduction_size_of<boost::simd::tag::maximum_, 1, Expr>{};

  template<class Domain, class Expr>
  struct size_of<boost::simd::tag::maximum_,Domain,2,Expr>
    : reduction_size_of<boost::simd::tag::maximum_, 2, Expr>{};

  template<class Domain, int N, class Expr>
  struct generator<boost::simd::tag::maximum_,Domain,N,Expr>
    : reduction_generator<boost::simd::tag::maximum_,N,Expr> {};
} } }

#endif
