/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_SDK_SIMD_PACK_STORE_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_PACK_STORE_HPP_INCLUDED

#include <boost/dispatch/meta/strip.hpp>
#include <boost/simd/include/functions/store.hpp>

////////////////////////////////////////////////////////////////////////////////
// Splat over terminal of simd domain using the pack::fill method
////////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::store_ , tag::cpu_
                            , (A0)(A1)(A2)(T)(C)(Sema)
                            , (( expr_< A0
                                      , domain_< boost::simd::domain<T,C> >
                                      , tag::terminal_
                                      , Sema
                                      >
                              ))
                              (iterator_< scalar_< fundamental_<A1> > >)
                              (scalar_< integer_<A2> >)
                            )
  {
    typedef A0 result_type;

    BOOST_SIMD_FUNCTOR_CALL(3)
    {
      A0 that = store(boost::proto::value(a0).value(),a1,a2);
      return that;
    }
  };
} } }

#endif
