//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_REDUCTION_FUNCTIONS_CONTAINER_NONE_HPP_INCLUDED
#define NT2_TOOLBOX_REDUCTION_FUNCTIONS_CONTAINER_NONE_HPP_INCLUDED

#include <boost/simd/toolbox/reduction/functions/none.hpp>
#include <nt2/core/container/dsl/details/reduction.hpp>
#include <nt2/include/functions/is_nez.hpp>
#include <nt2/core/container/dsl/size.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::none_, tag::cpu_
                            , (A0)(T)(N)
                            , ((expr_< generic_<arithmetic_<A0> >,T,N >))
                            )
  {
    typedef typename meta::call< nt2::tag::is_nez_(A0 const&)>::type base_t;
    typedef typename meta::call< nt2::tag::none_(base_t)>::type      result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      return nt2::none( nt2::is_nez(a0) );
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::none_, tag::cpu_
                            , (A0)(T)(N)(A1)
                            , ((expr_< generic_<arithmetic_<A0> >,T,N >))
                              (scalar_< integer_<A1> >)
                            )
  {
    typedef typename meta::call< nt2::tag::is_nez_(A0 const&)>::type base_t;
    typedef typename meta::call< nt2::tag::none_(base_t,A1)>::type    result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& a1) const
    {
      return nt2::none( nt2::is_nez(a0), a1 );
    }
  };
} }

namespace nt2 { namespace container { namespace ext
{
  template<class Domain, class Expr>
  struct size_of<boost::simd::tag::none_,Domain,1,Expr>
    : reduction_size_of<boost::simd::tag::none_, 1, Expr>{};

  template<class Domain, class Expr>
  struct size_of<boost::simd::tag::none_,Domain,2,Expr>
    : reduction_size_of<boost::simd::tag::none_, 2, Expr>{};

  template<class Domain, int N, class Expr>
  struct generator<boost::simd::tag::none_,Domain,N,Expr>
    : reduction_generator<boost::simd::tag::none_,N,Expr> {};
} } }

#endif
