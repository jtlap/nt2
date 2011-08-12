//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SCALAR_PREDECESSOR_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SCALAR_PREDECESSOR_HPP_INCLUDED
#include <boost/simd/include/constants/infinites.hpp>

#include <boost/simd/include/functions/bitfloating.hpp>
#include <boost/simd/include/functions/bitinteger.hpp>
#include <boost/simd/include/functions/minusone.hpp>
#include <boost/simd/include/functions/is_nan.hpp>
#include <boost/simd/include/functions/abs.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::predecessor_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< arithmetic_<A0> >)(scalar_< integer_<A1> >)
                            )
  {

    typedef A0 result_type;

    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      if (Valmin<A0>()+boost::simd::abs(a1) > a0) return Valmin<A0>(); 
      return a0-boost::simd::abs(a1);
    }
  };
} } }


namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::predecessor_, tag::cpu_
                            , (A0)
                            , (scalar_< arithmetic_<A0> >)
                            )
  {

    typedef A0 result_type;

    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      if (a0 != Valmin<A0>())
	return minusone(a0);
      else
	return Valmin<A0>(); 
    }
  };
} } }


////
/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is real_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::predecessor_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< real_<A0> >)(scalar_< integer_<A1> >)
                            )
  {

    typedef A0 result_type;

    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      if (is_nan(a0)) return a0; 
      return a0==Minf<A0>() ? a0 : bitfloating(bitinteger(a0)-boost::simd::abs(a1));
    }
  };
} } }


namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::predecessor_, tag::cpu_
                            , (A0)
                            , (scalar_< real_<A0> >)
                            )
  {

    typedef A0 result_type;

    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      if (is_nan(a0)) return a0; 
      return a0==Minf<A0>() ? a0 : bitfloating(minusone(bitinteger(a0)));
    }
  };
} } }


#endif
