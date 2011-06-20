/*******************************************************************************
 *         Copyright 2003-2010 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2010 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_PACK_EVALUATION_HPP_INCLUDED
#define NT2_SDK_SIMD_PACK_EVALUATION_HPP_INCLUDED

#include <nt2/sdk/dsl/literal.hpp>
#include <nt2/sdk/dsl/compute.hpp>
#include <nt2/sdk/dsl/category.hpp>
#include <nt2/sdk/dsl/evaluation.hpp>

//==============================================================================
// Evaluation of simd native pack
//==============================================================================
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::evaluate_, tag::cpu_
                            , (A0)(X)(A1)(T)(C)(Tag)(S)
                            , ((simd_<arithmetic_<A0>,X>))
                              ((expr_<A1,domain_< simd::domain<T,C> >,Tag, S>))
                            )
  {
    typedef int result_type;

    inline result_type operator()( A0& a0, A1 const& a1) const
    {
      meta::as_<A0> target;
      meta::compile < meta::compute<boost::mpl::_1,tag::cpu_> > callee;
      a0 = callee(a1,target);
      
      return 0;
    }
  };
} }

//==============================================================================
// Evaluation of non-simd pack
//==============================================================================
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION_TPL(  tag::evaluate_,tag::cpu_
                                , (class A0)(std::size_t N)
                                  (class A1)(class T)(class C)
                                  (class Tag)(class S)
                                , ((array_<arithmetic_<A0>,N>))
                                  ((expr_<A1,domain_<simd::domain<T,C> >,Tag,S>))
                                )
  {
    typedef int result_type;

    inline result_type operator()( A0& a0, A1 const& a1) const
    {
      meta::as_<A0> target;
      meta::compile< meta::compute<boost::mpl::_1,tag::cpu_> > callee;

      for(std::size_t i=0;i<C::value;++i)
          a0[i] = callee(a1,target,i);
          
      return 0;
    }
  };
} }

#endif
