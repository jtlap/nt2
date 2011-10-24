//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SCALAR_FREXP_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SCALAR_FREXP_HPP_INCLUDED
#include <boost/mpl/vector.hpp>
#include <boost/dispatch/meta/adapted_traits.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/include/at.hpp>
#include <boost/simd/include/functions/is_inf.hpp>
#include <math.h>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::frexp_, tag::cpu_, (A0)(A2)
                            , (scalar_< double_<A0> >)
                              (scalar_< double_<A0> >)
                              (scalar_< int64_<A2> >)
                            )
  {
    typedef int result_type;
    inline int operator()(A0 const& a0,A0 & a1,A2 & a2) const
    {
      boost::simd::int32_t aa2 = 0; 
      a1 = ::frexp(a0, &aa2);
      a2 =  aa2; 
      return 0; 
    }
  };
  
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::frexp_, tag::cpu_, (A0)(A2)
                            , (scalar_< double_<A0> >)
                              (scalar_< int64_<A2> >)
                            )
  {
    typedef A0 result_type;    
    inline int operator()(A0 const& a0,A2 & a2) const
    {
      boost::simd::int32_t aa2; 
      A0 aa1 = ::frexp(a0, &aa2);
      a2 =  aa2;
      return 0; 
    }
  };
  
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::frexp_, tag::cpu_, (A0)(A2)
                            , (scalar_< single_<A0> >)
                              (scalar_< single_<A0> >)
      (scalar_< int32_<A2> >)
                            )
  {
    typedef int result_type;
    inline result_type operator()(A0 const& a0,A0 & a1,A2 & a2) const
    {
      if (is_inf(a0))
{
  a2 = 0; 
  a1 = a0; 
}
      else
a1 = ::frexpf(a0, &a2);
      return 0; 
    }
  };
  
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::frexp_, tag::cpu_, (A0)(A2)
                            , (scalar_< single_<A0> >)
                              (scalar_< int32_<A2> >)
                            )
  {
    typedef A0 result_type;    
    inline result_type operator()(A0 const& a0,A2 & a2) const
    {
      if (is_inf(a0))
{
  a2 = 0; 
  return a0; 
}
      return ::frexpf(a0, &a2);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::frexp_, tag::cpu_, (A0)
                            , (scalar_< double_<A0> >)
                            )
  {
    typedef A0                                                                     mantissa;
    typedef typename dispatch::meta::as_integer<A0,signed>::type                   exponent;
    typedef boost::fusion::vector<mantissa,exponent>                            result_type;

    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      result_type res;
      if (is_inf(a0))
      {
        boost::fusion::at_c<0>(res) = a0;
        boost::fusion::at_c<1>(res) = 0;
        return res; 
      }
      boost::simd::int32_t r1t;
      boost::fusion::at_c<0>(res) = ::frexp(a0, &r1t);
      boost::fusion::at_c<1>(res) = r1t;
      return res;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::frexp_, tag::cpu_, (A0)
                            , (scalar_< single_<A0> >)
                            )
  {
    typedef typename dispatch::meta::result_of<dispatch::meta::floating(A0)>::type mantissa;
    typedef typename dispatch::meta::as_integer<A0,signed>::type                   exponent;
    typedef boost::fusion::vector<mantissa,exponent>                            result_type;

    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      result_type res;
      if (is_inf(a0))
      {
        boost::fusion::at_c<0>(res) = a0;
        boost::fusion::at_c<1>(res) = 0;
        return res; 
      }
      boost::fusion::at_c<0>(res) = ::frexpf(a0, &boost::fusion::at_c<1>(res));
      return res;
    }
  };
} } }

#endif
