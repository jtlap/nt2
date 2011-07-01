//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_ARITHMETIC_FUNCTION_SIMD_COMMON_SUBS_HPP_INCLUDED
#define NT2_TOOLBOX_ARITHMETIC_FUNCTION_SIMD_COMMON_SUBS_HPP_INCLUDED
#include <nt2/include/functions/bitwise_andnot.hpp>
#include <nt2/include/functions/is_gtz.hpp>
#include <nt2/include/functions/adds.hpp>
#include <nt2/include/functions/any.hpp>
#ifdef NT2_SIMD_DETECTED

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is real_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::subs_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<real_<A0>,X>))((simd_<real_<A0>,X>))
                            )
  {

    typedef typename meta::strip<A0>::type result_type;

    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      return nt2::sub(a0, a1);
    }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is uint_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::subs_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<uint_<A0>,X>))((simd_<uint_<A0>,X>))
                            )
  {

    typedef typename meta::strip<A0>::type result_type;

    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      A0 a0ma1 = a0-a1;
      return b_and(a0ma1, le(a0ma1, a0)); 
      //      return seladd(gt(a0, a1), Zero<A0>(), a0-a1); 
    }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is int_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::subs_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<int_<A0>,X>))((simd_<int_<A0>,X>))
                            )
  {

    typedef A0 result_type;

    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      A0 res =  adds(a0, -a1); 
      if (nt2::any(eq(a1, Valmin<A0>())))
	return sel(eq(a1, Valmin<A0>()), adds(adds(a0, Valmax<A0>()),One<A0>()), res);
      else
	return res; 
    }
  };
} }


#endif
#endif
