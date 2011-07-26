//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTION_SCALAR_SUBS_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTION_SCALAR_SUBS_HPP_INCLUDED
#include <boost/simd/include/functions/saturate.hpp>
#include <boost/simd/include/functions/adds.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is integer_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace dispatch { namespace meta
{
  BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION( boost::simd::tag::subs_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< integer_<A0> >)(scalar_< integer_<A1> >)
                            )
  {

    typedef typename meta::strip<A0>::type result_type;

    BOOST_DISPATCH_FUNCTOR_CALL(2)
    {
      typedef typename meta::upgrade<A0>::type utype; 
      return boost::simd::saturate<A0>(utype(a0)-utype(a1)); 
    }
  };
} } }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is unsigned_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace dispatch { namespace meta
{
  BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION( boost::simd::tag::subs_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< unsigned_<A0> >)(scalar_< unsigned_<A1> >)
                            )
  {

    typedef typename meta::strip<A0>::type result_type;

    BOOST_DISPATCH_FUNCTOR_CALL(2)
    {
      if (gt(a0, a1))
	return a0-a1;
      else
	return Zero<A0>(); 
    }
  };
} } }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace dispatch { namespace meta
{
  BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION( boost::simd::tag::subs_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< int64_<A0> >)(scalar_< int64_<A1> >)
                            )
  {

    typedef typename meta::strip<A0>::type result_type;

    BOOST_DISPATCH_FUNCTOR_CALL(2)
    {
       if (eq(a1, Valmin<A0>()))
 	{
          if (a0 >= Mone<A0>()) return Valmax<A0>(); 
 	  return adds(adds(a0, Valmax<A0>()),One<A0>());
 	}
      return boost::simd::adds(a0, -a1);     
    }
  };
} } }




#endif
