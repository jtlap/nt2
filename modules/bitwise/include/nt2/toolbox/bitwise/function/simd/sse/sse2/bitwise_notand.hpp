//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_BITWISE_FUNCTION_SIMD_SSE_SSE2_BITWISE_NOTAND_HPP_INCLUDED
#define NT2_TOOLBOX_BITWISE_FUNCTION_SIMD_SSE_SSE2_BITWISE_NOTAND_HPP_INCLUDED

namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION_IF ( tag::bitwise_notand_, tag::cpu_, (A0)(A1)
                                , (boost::mpl::equal_to < boost::mpl::sizeof_<A0>
                                                        , boost::mpl::sizeof_<A1>
                                                        >
                                  )
                                , ( tag::bitwise_notand_
                                    ( simd_<arithmetic_<A0>,tag::sse_>
                                    , simd_<arithmetic_<A1>,tag::sse_>
                                    )
                                  )
                                , ((simd_<arithmetic_<A0>,tag::sse_>))
                                  ((simd_<arithmetic_<A1>,tag::sse_>))
                              )
  {
    typedef A0 result_type;

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename meta::as_integer< A0 >::type int_type;
      A0     that = { simd::native_cast<A0>
                      ( _mm_andnot_si128( simd::native_cast<int_type>(a0)
                                        , simd::native_cast<int_type>(a1)
                                        )
                      )
                    };
      return that;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION(tag::bitwise_notand_, tag::cpu_, (A0),
                             ((simd_<double_<A0>,tag::sse_>))
                             ((simd_<double_<A0>,tag::sse_>))
                            )
  {
    typedef A0 result_type;

    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      A0 that = {_mm_andnot_pd(a0, a1)};
      return that;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( tag::bitwise_notand_, tag::cpu_, (A0)
                            , ((simd_<float_<A0>,tag::sse_>))
                              ((simd_<float_<A0>,tag::sse_>))
                            )
  {
    typedef A0 result_type;

    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      A0 that = {_mm_andnot_ps(a0, a1)};
      return that;
    }
  };
} }


#endif
