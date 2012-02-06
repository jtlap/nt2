//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_SIMD_VMX_ALTIVEC_ARITH_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_SIMD_VMX_ALTIVEC_ARITH_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_VMX_SUPPORT

#include <boost/simd/toolbox/swar/functions/arith.hpp>
#include <boost/simd/include/functions/splat.hpp>
// Is there nothing to do for float vectors ? TO DO
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::arith_
                                    , boost::simd::tag::altivec_
                                    , (T)
                                    , ((target_
                                        < simd_ < ints8_<T>
                                                , boost::simd::tag::altivec_
                                                >
                                        >
                                      ))
                                    )
  {
    typedef typename T::type result_type;

    result_type operator()(T const& ) const
    {
      // add [a0 ... a0] with [0 1 2 ... 12 15]
      result_type that =  { vec_add ( splat<result_type>(0)()
                                    , vec_lvsl(0,(char*)(0))
                                    )
                          };
      return that;
    }
  };
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::arith_
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
  // I am not sure as don't know altivec well and have not support available (JTL). Does vec_madd is to be used here ?
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::arith_
                                    , boost::simd::tag::altivec_
                                      , (A0)(A1)(T)
                                    , (scalar_< arithmetic_<A0> >)
                                      (scalar_< arithmetic_<A1> >)  
                                      ((target_
                                        < simd_ < ints8_<T>
                                                , boost::simd::tag::altivec_
                                                >
                                        >
                                      ))
                                    )
  {
    typedef typename T::type result_type;

    result_type operator()(A0 const& a0, A1 const& a1, T const& ) const
    {
      // add [a0 ... a0] with [0 1 2 ... 12 15]*[a1 ... a1]
      result_type that =  { vec_add ( splat<result_type>(a0)()
                                      , vec_mul(splat<result_type>(a1)(),
                                                vec_lvsl(0,(char*)(0))
                                                )
                                    )
                          };
      return that;
    }
  };  
} } }

#endif
#endif
