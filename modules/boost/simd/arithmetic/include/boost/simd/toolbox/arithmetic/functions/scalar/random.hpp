//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SCALAR_RANDOM_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SCALAR_RANDOM_HPP_INCLUDED
#include <boost/dispatch/meta/strip.hpp>
#include <boost/simd/include/functions/iround.hpp>
#include <boost/simd/include/functions/min.hpp>
#include <boost/simd/include/functions/dist.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 and A1 are not equal types
// This oddity is due to the fact that many tests up to now
// don't pass typed integer parameters to the macro NT2_CREATE_BUF
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::random_, tag::cpu_
                             , (A0)(A1)
                             , (scalar_< arithmetic_<A0> >)
                                 (scalar_< arithmetic_<A1> >)
                             )
  {
    typedef A0 result_type;  
    BOOST_SIMD_FUNCTOR_CALL(2)
      {
      return boost::simd::random(static_cast<result_type>(a0),
                           static_cast<result_type>(a1)); 
      }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::random_, tag::cpu_
                            , (A0)
                            , (scalar_< arithmetic_<A0> >)
                        (scalar_< arithmetic_<A0> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return iround(static_cast<double>(a1-a0)*(static_cast<double>(::rand())/RAND_MAX)+
                static_cast<double>(a0)); //TO DO proper generator
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::random_, tag::cpu_
                            , (A0)
                            , (scalar_< unsigned_<A0> >)
                        (scalar_< unsigned_<A0> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return iround(static_cast<double>(dist(a1, a0))*(static_cast<double>(::rand())/RAND_MAX)+
                static_cast<double>(min(a0, a1))); //TO DO proper generator
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::random_, tag::cpu_
                            , (A0)
                            , (scalar_< floating_<A0> >)
                        (scalar_< floating_<A0> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return static_cast<double>(a1-a0)*(static_cast<double>(::rand())/RAND_MAX)+
      static_cast<double>(a0); //TO DO proper generator
    }
  };
} } }


#endif
