/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_SDK_SIMD_PACK_UNALIGNED_STORE_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_PACK_UNALIGNED_STORE_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// unaligned store for SIMD packs
////////////////////////////////////////////////////////////////////////////////
#include <boost/simd/sdk/simd/category.hpp>
#include <boost/simd/include/functions/unaligned_store.hpp>
#include <boost/simd/include/functions/evaluate.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::unaligned_store_ , tag::cpu_
                            , (A0)(A1)(A2)
                            , ((ast_<A0, boost::simd::domain>))
                              (iterator_< scalar_< fundamental_<A1> > >)
                              (scalar_< integer_<A2> >)
                            )
  {
    typedef typename remove_reference< typename boost::dispatch::meta::
                                       semantic_of<A0 const&>::type
                                     >::type                result_type;

    BOOST_SIMD_FUNCTOR_CALL(3)
    {
      result_type that = unaligned_store(evaluate(a0),a1,a2);
      return that;
    }
  };
} } }

#endif
