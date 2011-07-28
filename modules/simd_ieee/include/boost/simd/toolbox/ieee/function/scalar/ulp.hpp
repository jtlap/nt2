//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_IEEE_FUNCTION_SCALAR_ULP_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_IEEE_FUNCTION_SCALAR_ULP_HPP_INCLUDED
#include <boost/simd/include/constants/properties.hpp>
#include <boost/simd/include/constants/digits.hpp>
#include <boost/simd/include/constants/infinites.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/simd/include/constants/eps_related.hpp>
#include <boost/simd/include/functions/prev.hpp>
#include <boost/simd/include/functions/min.hpp>
#include <boost/simd/include/functions/is_eqz.hpp>
#include <boost/simd/include/functions/abs.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace dispatch { namespace meta
{
  BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION( boost::simd::tag::ulp_, tag::cpu_
                            , (A0)
                            , (scalar_< arithmetic_<A0> >)
                            )
  {
    typedef typename meta::result_of<meta::arithmetic(A0)>::type result_type;
    BOOST_DISPATCH_FUNCTOR_CALL(1)
    {
      using namespace boost::simd;
      ignore_unused(a0);
      return One<A0>();
    }
  };
} } }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is real_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace dispatch { namespace meta
{
  BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION( boost::simd::tag::ulp_, tag::cpu_
                            , (A0)
                            , (scalar_< real_<A0> >)
                            )
  {
    typedef typename meta::strip<A0>::type result_type;
    BOOST_DISPATCH_FUNCTOR_CALL(1)
    {
      using namespace boost::simd;
      typedef typename meta::as_integer<A0,unsigned>::type int_type;
      if (is_eqz(a0)) return Mindenormal<A0>();
      const A0 x = boost::simd::abs(a0);
      if (x == Inf<A0>()) return x;
      int_type aa = bitwise_cast<int_type>(x);
      int_type bb = aa;
      --bb;
      ++aa;
      return boost::simd::min(x-bitwise_cast<A0>(bb),
		      bitwise_cast<A0>(aa)-x);
    }
  };
} } }


#endif
