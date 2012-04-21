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
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::maximum_, maximum , 3)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::maximum_, max     , 3)
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

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::maximum_, tag::cpu_
                            , (A0)(A1)(A2)
                            , (ast_<A0>)
                              (target_< unspecified_<A1> >)
                              (scalar_< integer_<A2> >)
                            )
  {
    typedef typename meta::call< nt2::tag::maximum_(A0 const&, A2)>::type result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& a0,A1 const&,A2 const& a2) const
    {
      return nt2::maximum(a0,a2);
    }
  };
} }

#endif
