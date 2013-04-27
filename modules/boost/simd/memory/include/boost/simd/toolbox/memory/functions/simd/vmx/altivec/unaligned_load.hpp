//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_MEMORY_FUNCTIONS_SIMD_VMX_ALTIVEC_UNALIGNED_LOAD_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_MEMORY_FUNCTIONS_SIMD_VMX_ALTIVEC_UNALIGNED_LOAD_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_VMX_SUPPORT

#include <boost/simd/toolbox/memory/functions/unaligned_load.hpp>
#include <boost/simd/toolbox/memory/functions/details/char_helper.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <iterator>

namespace boost { namespace simd { namespace ext
{
  /// INTERNAL ONLY - SIMD unaligned load with offset
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::unaligned_load_
                                    , boost::simd::tag::altivec_
                                    , (A0)(A1)(A2)
                                    , (iterator_< scalar_< arithmetic_<A0> > >)
                                      (scalar_< integer_<A1> >)
                                      ((target_
                                        < simd_ < arithmetic_<A2>
                                                , boost::simd::tag::altivec_
                                                >
                                        >
                                      ))
                                    )
  {
    typedef typename A2::type                             result_type;
    typedef typename std::iterator_traits<A0>::value_type value_t;
    typedef typename result_type::native_type                 n_t;

    static const std::size_t sz   = sizeof(value_t);
    static const std::size_t card = meta::cardinal_of<result_type>::value;
    static const std::size_t cdz  = card*sz-1;

    BOOST_FORCEINLINE result_type operator()(A0 a0, A1 a1, const A2&) const
    {
      a1 *= sz;

      n_t                     MSQ  = vec_ld  (a1     , char_helper(a0) );
      __vector unsigned char  mask = vec_lvsl(a1     , char_helper(a0) );
      n_t                     LSQ  = vec_ld  (a1+cdz , char_helper(a0) );

      return vec_perm(MSQ, LSQ, mask);
    }
  };

  /// INTERNAL ONLY - SIMD unaligned load without offset
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::unaligned_load_
                                    , boost::simd::tag::altivec_
                                    , (A0)(A2)
                                    , (iterator_< scalar_< arithmetic_<A0> > >)
                                      ((target_
                                        < simd_ < arithmetic_<A2>
                                                , boost::simd::tag::altivec_
                                                >
                                        >
                                      ))
                                    )
  {
    typedef typename A2::type                             result_type;
    typedef typename std::iterator_traits<A0>::value_type value_t;
    typedef typename result_type::native_type                 n_t;

    static const std::size_t sz   = sizeof(value_t);
    static const std::size_t card = meta::cardinal_of<result_type>::value;
    static const std::size_t cdz  = card*sz-1;

    BOOST_FORCEINLINE result_type operator()(A0 a0, const A2&) const
    {
      n_t                     MSQ  = vec_ld   ( 0   , char_helper(a0) );
      __vector unsigned char  mask = vec_lvsl ( 0   , char_helper(a0) );
      n_t                     LSQ  = vec_ld   ( cdz , char_helper(a0) );

      return vec_perm(MSQ, LSQ, mask);
    }
  };
} } }

#endif
#endif
