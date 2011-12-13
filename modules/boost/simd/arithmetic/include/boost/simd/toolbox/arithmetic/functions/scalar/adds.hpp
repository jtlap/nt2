//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SCALAR_ADDS_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SCALAR_ADDS_HPP_INCLUDED
#include <boost/simd/toolbox/arithmetic/functions/adds.hpp>
#include <boost/simd/include/functions/saturate.hpp>
#include <boost/simd/include/functions/is_gtz.hpp>
#include <boost/simd/include/functions/is_greater.hpp>
#include <boost/simd/include/functions/is_less.hpp>
#include <boost/simd/include/functions/min.hpp>
#include <boost/simd/include/functions/max.hpp>
#include <boost/simd/include/constants/valmin.hpp>
#include <boost/simd/include/constants/valmax.hpp>
#include <boost/dispatch/meta/upgrade.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::adds_, tag::cpu_
                            , (A0)
                            , (scalar_< integer_<A0> >)(scalar_< integer_<A0> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      typedef typename dispatch::meta::upgrade<A0>::type utype; 
      return static_cast<A0>(boost::simd::saturate<A0>(utype(a0)+utype(a1)));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::adds_, tag::cpu_
                            , (A0)
                            , (scalar_< unsigned_<A0> >)(scalar_< unsigned_<A0> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      typedef typename dispatch::meta::upgrade<A0>::type utype; 
      return static_cast<A0>(boost::simd::min(utype(boost::simd::Valmax<A0>()), utype(a0+a1)));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::adds_, tag::cpu_
                            , (A0)
                            , (scalar_< int64_<A0> >)(scalar_< int64_<A0> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      bool gtza0 = is_gtz(a0);
      bool gtza1 = is_gtz(a1);
      A0 a0pa1 = a0+a1;
      if (gtza0 && gtza1 && (lt(a0pa1, a0)))
      {
        return Valmax<A0>();
      }
      else if (!gtza0 && !gtza1 && (is_gtz(a0pa1) || (gt(a0pa1, boost::simd::min(a0, a1)))))
      {
        return Valmin<A0>();
      }
      else
      {
        return a0pa1;
      }
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::adds_, tag::cpu_
                            , (A0)
                            , (scalar_< uint64_<A0> >)(scalar_< uint64_<A0> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      A0 a0pa1 = a0+a1;
      if (lt(a0pa1, boost::simd::max(a0, a1)))
      {
        return Valmax<A0>();
      }
      else
      {
        return a0pa1;
      }
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::adds_, tag::cpu_
                            , (A0)
                            , (scalar_< uint32_<A0> >)(scalar_< uint32_<A0> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      A0 a0pa1 = a0+a1;
      if (lt(a0pa1, boost::simd::max(a0, a1)))
      {
        return Valmax<A0>();
      }
      else
      {
        return a0pa1;
      }
    }
  };
} } }


#endif
