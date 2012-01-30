//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_SIMD_VMX_ALTIVEC_ENUMERATE_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_SIMD_VMX_ALTIVEC_ENUMERATE_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_VMX_SUPPORT

#include <boost/simd/toolbox/swar/functions/enumerate.hpp>
#include <boost/simd/include/functions/splat.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::enumerate_
                                    , boost::simd::tag::altivec_
                                    , (A0)(T)
                                    , (scalar_< arithmetic_<A0> >)
                                      ((target_
                                        < simd_ < ints8_<T>
                                                , boost::simd::tag::altivec_
                                                >
                                        >
                                      ))
                                    )
  {
    typedef typename T::type result_type;

    result_type operator()(A0 const& a0, T const& ) const
    {
      // add [a0 ... a0] with [0 1 2 ... 12 15]
      result_type that =  { vec_add ( splat<result_type>(a0)()
                                    , vec_lvsl(0,(char*)(0))
                                    )
                          };
      return that;
    }
  };
} } }

#endif
#endif
