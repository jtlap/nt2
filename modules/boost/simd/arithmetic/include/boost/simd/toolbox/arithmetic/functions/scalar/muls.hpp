//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SCALAR_MULS_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SCALAR_MULS_HPP_INCLUDED
#include <boost/simd/sdk/simd/logical.hpp>
#include <boost/simd/include/functions/genmask.hpp>
#include <boost/simd/include/functions/adds.hpp>
#include <boost/simd/include/functions/abs.hpp>
#include <boost/simd/include/functions/is_ltz.hpp>
#include <boost/simd/include/functions/bitofsign.hpp>
#include <boost/simd/include/functions/saturate.hpp>
#include <boost/dispatch/meta/downgrade.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is unsigned_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::muls_, tag::cpu_
                            , (A0)
                            , (scalar_< unsigned_<A0> >)(scalar_< unsigned_<A0> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      typedef typename dispatch::meta::upgrade<A0>::type utype; 
      utype res = utype(a0)*utype(a1);
      return A0(res) | genmask(A0(res >> sizeof(A0)*8)); 	
    }
  };
} } }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is integer_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::muls_, tag::cpu_
                            , (A0)
                            , (scalar_< integer_<A0> >)(scalar_< integer_<A0> >)
                            )
  {

    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      typedef typename dispatch::meta::upgrade<A0>::type uptype;
      return A0(saturate<A0>(uptype(a0)*uptype(a1)));
    }
  };
} } }



/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is uint64_t_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::muls_, tag::cpu_
                            , (A0)
                            , (scalar_< uint64_<A0> >)(scalar_< uint64_<A0> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      if (a1 == 0 || a0 == 0) return Zero<A0>(); 
      if (a1 >= a0)
      {
        A0 z = Valmax<A0>()/a1;
        if (z < a0)
        {
          return  Valmax<A0>();
	    }
        else
        {
          return a0*a1; 
        }
      }
      else
      {
        return muls(a1, a0); 
      }

//    typedef typename dispatch::meta::downgrade<A0>::type dtype; 
//    A0 a0hi = a0 >> sizeof(dtype)*8;
//    A0 a1hi = a1 >> sizeof(dtype)*8;
//    if (a0hi && a1hi)
//    {
//      return Valmax<A0>();
//    }
//    else
//    {
//      A0 a0lo = (a0 & 0xFFFFFFFF);
// 	    A0 a1lo = (a1 & 0xFFFFFFFF);
// 	    A0 res = a0lo*a1lo;
// 	    A0 z = (a0hi*a1lo+a1hi*a0lo) << (sizeof(dtype)*8);
// 	    if (res+z < res || z > Valmax<A0>() ) return Valmax<A0>();
// 	      return (res+z); 
//    }
//    typedef __uint128_t utype;
//    utype res = utype(a0)*utype(a1);
//    return A0(res) | genmask(A0(res >> /*6*/4));
//    return Zero<A0>(); 
    }
  };
} } }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is integer_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::muls_, tag::cpu_
                            , (A0)
                            , (scalar_< int64_<A0> >)(scalar_< int64_<A0> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      typedef typename meta::as_logical<A0>::type bA0; 
      if (a1 == 0 || a0 == 0) return Zero<A0>();
      typedef typename dispatch::meta::as_integer<A0, unsigned>::type untype;
      A0 sign =  bitofsign(a0)^bitofsign(a1);
      untype aa0 = boost::simd::abs(a0);
      untype aa1 = boost::simd::abs(a1);
      if (aa1 >= aa0)
      {
        untype z = Valmax<A0>()/aa1;
        if (z < aa0)
        {
          return sign ? Valmin<A0>():Valmax<A0>();
        }
        else
        {
          return a0*a1; 
        }
      }
      else
      {
        return muls(a1, a0); 
      }
    }
  };
} } }



#endif
