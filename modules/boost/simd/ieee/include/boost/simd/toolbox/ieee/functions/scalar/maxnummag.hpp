//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SCALAR_MAXNUMMAG_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SCALAR_MAXNUMMAG_HPP_INCLUDED

#include <boost/simd/include/functions/is_nan.hpp>
#include <boost/simd/include/functions/abs.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::maxnummag_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< arithmetic_<A0> >)(scalar_< arithmetic_<A1> >)
                            )
  {

    typedef typename dispatch::meta::result_of<dispatch::meta::arithmetic(A0,A1)>::type result_type;

    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      typedef result_type type;
      return boost::simd::abs(type(a0)) >  boost::simd::abs(type(a1)) ? type(a0) : type(a1);
    }
  };
} } }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is real_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::maxnummag_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< real_<A0> >)(scalar_< real_<A1> >)
                            )
  {

    typedef typename dispatch::meta::result_of<dispatch::meta::arithmetic(A0,A1)>::type result_type;

    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      typedef result_type type;
      if (is_nan(a0))
      return type(a1);
      else if (is_nan(a1))
      return type(a0);
      else
      return boost::simd::abs(type(a0)) >  boost::simd::abs(type(a1)) ? type(a0) : type(a1);
    }
  };
} } }


#endif
