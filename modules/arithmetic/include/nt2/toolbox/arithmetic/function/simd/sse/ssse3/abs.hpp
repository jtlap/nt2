//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_ARITHMETIC_FUNCTION_SIMD_SSE_SSSE3_ABS_HPP_INCLUDED
#define NT2_TOOLBOX_ARITHMETIC_FUNCTION_SIMD_SSE_SSSE3_ABS_HPP_INCLUDED
#include <nt2/include/constants/real.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/include/constants/digits.hpp>
#include <nt2/include/constants/properties.hpp>
#include <nt2/include/functions/select.hpp>
#include <nt2/include/functions/is_lez.hpp>
#include <nt2/include/functions/bitwise_notand.hpp>
#include <nt2/include/functions/shri.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is int32_t
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::abs_, tag::cpu_
                            , (A0)
                            , ((simd_<int32_<A0>,tag::sse_>))
                            )
  {

    typedef typename meta::strip<A0>::type result_type;

    NT2_FUNCTOR_CALL(1)
    { A0 that = {_mm_abs_epi32(a0) }; return that; }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is int8_t
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::abs_, tag::cpu_
                            , (A0)
                            , ((simd_<int8_<A0>,tag::sse_>))
                            )
  {

    typedef typename meta::strip<A0>::type result_type;

    NT2_FUNCTOR_CALL(1)
    { A0 that = {_mm_abs_epi8(a0) }; return that; }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is int16_t
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::abs_, tag::cpu_
                            , (A0)
                            , ((simd_<int16_<A0>,tag::sse_>))
                            )
  {

    typedef typename meta::strip<A0>::type result_type;

    NT2_FUNCTOR_CALL(1)
    { A0 that = {_mm_abs_epi16(a0) };return that; }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is real_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::abs_, tag::cpu_
                            , (A0)
                            , ((simd_<real_<A0>,tag::sse_>))
                            )
  {

    typedef typename meta::strip<A0>::type result_type;

    NT2_FUNCTOR_CALL(1)
    { return b_notand(Mzero<A0>(),a0); }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is int64_t
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::abs_, tag::cpu_
                            , (A0)
                            , ((simd_<int64_<A0>,tag::sse_>))
                            )
  {

    typedef typename meta::strip<A0>::type result_type;

    NT2_FUNCTOR_CALL(1)
    {
       typedef typename meta::as_integer<A0, signed>::type int_type;
       typedef typename meta::scalar_of<int_type>::type   sint_type;
       A0 const s = shri(a0, 8*sizeof(sint_type)-1);
       return (a0-s)^(-s);
       //      return select(is_lez(a0),-a0,a0);
    }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is unsigned_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::abs_, tag::cpu_
                            , (A0)
                            , ((simd_<unsigned_<A0>,tag::sse_>))
                            )
  {

    typedef typename meta::strip<A0>::type result_type;

    NT2_FUNCTOR_CALL(1)
    { return a0; }
  };
} }


#endif
