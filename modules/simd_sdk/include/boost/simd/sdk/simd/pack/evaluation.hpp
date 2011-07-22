/*******************************************************************************
 *         Copyright 2003-2010 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2010 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_SDK_SIMD_PACK_EVALUATION_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_PACK_EVALUATION_HPP_INCLUDED

#include <boost/simd/sdk/dsl/literal.hpp>
#include <boost/simd/sdk/dsl/compute.hpp>
#include <boost/simd/sdk/dsl/category.hpp>
#include <boost/simd/sdk/dsl/evaluation.hpp>


#include <iostream>
#include <boost/simd/sdk/details/type_id.hpp>

//==============================================================================
// Evaluation of simd native pack
//==============================================================================
namespace boost { namespace dispatch { namespace meta
{
  BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION( tag::evaluate_, tag::cpu_
                            , (A0)(X)(A1)(T)(C)(Tag)(S)
                            , ((simd_<arithmetic_<A0>,X>))
                              ((expr_<A1,domain_< boost::simd::domain<T,C> >, Tag, S>))
                            )
  {
    typedef int result_type;

    inline result_type operator()( A0& a0, A1 const& a1) const
    {
      meta::as_<A0> target;
      boost::simd::meta::compile < boost::simd::meta::compute<boost::mpl::_1,tag::cpu_> > callee;
      a0 = callee(a1,target);
      return 0;
    }
  };
} } }

//==============================================================================
// Evaluation of non-simd pack
//==============================================================================
namespace boost { namespace dispatch { namespace meta
{
  BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION_TPL(  tag::evaluate_,tag::cpu_
                                , (class A0)(std::size_t N)
                                  (class A1)(class T)(class C)
                                  (class Tag)(class S)
                                , ((array_< scalar_<arithmetic_<A0> >,N>))
                                  ((expr_<A1,domain_<boost::simd::domain<T,C> >,Tag,S>))
                                )
  {
    typedef int result_type;

    template<class Dst, class Src>
    inline result_type operator()( Dst& a0, Src const& a1) const
    {
      meta::as_<A0> target;
      boost::simd::meta::compile< boost::simd::meta::compute<boost::mpl::_1,tag::cpu_> > callee;

      for(std::size_t i=0;i<C::value;++i)
          a0[i] = callee(a1,target,i);
          
      return 0;
    }
  };
} } }

#endif
