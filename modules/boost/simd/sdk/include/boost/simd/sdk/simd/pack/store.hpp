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

#include <boost/simd/include/functions/store.hpp>
#include <boost/simd/include/functions/evaluate.hpp>

// store forces evaluation due to side-effect
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::store_ , tag::cpu_
                            , (A0)(A1)(A2)
                            , (ast_<A0>)
                              (iterator_< scalar_< fundamental_<A1> > >)
                              (scalar_< integer_<A2> >)
                            )
  {
    typedef typename remove_reference< typename boost::dispatch::meta::
                                       semantic_of<A0 const&>::type
                                     >::type                result_type;

    BOOST_SIMD_FUNCTOR_CALL(3)
    {
      return store(evaluate(a0),a1,a2);
    }
  };
} } }

#endif
