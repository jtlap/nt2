//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SCALAR_REMQUO_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SCALAR_REMQUO_HPP_INCLUDED
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/fusion/tuple.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/simd/include/functions/remainder.hpp>
#include <boost/simd/include/functions/idivround.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::remquo_, tag::cpu_,
                       (A0),
                       (scalar_ < floating_<A0> > )
                       (scalar_ < floating_<A0> > )
                       )
  {
    typedef typename dispatch::meta::as_integer<A0,signed>::type           quo;
    typedef boost::fusion::tuple<A0,quo>                           result_type;

    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      result_type res;
      boost::simd::remquo(a0, a1, boost::fusion::at_c<0>(res), boost::fusion::at_c<1>(res));
      return res; 
    }
    
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::remquo_, tag::cpu_,
                       (A0)(A1),
                       (scalar_ < floating_<A0> > )
                       (scalar_ < floating_<A0> > )
                       (scalar_ < floating_<A0> > )
                       (scalar_ < integer_<A1> > )
                       )
  {
    typedef boost::simd::int32_t result_type;
    inline result_type operator()(A0 const& a0,const A0 & a1,A0 & a2,A1 & a3) const
    {
      a2 = boost::simd::remainder(a0, a1);
      a3 = boost::simd::idivround(a0, a1);
      return 0;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::remquo_, tag::cpu_,
                       (A0)(A1),
                       (scalar_ < integer_<A0> > )
                       (scalar_ < integer_<A0> > )
                       (scalar_ < floating_<A1> > )
                       (scalar_ < integer_<A0> > )
                       )
  {
    typedef boost::simd::int32_t result_type;
    inline result_type operator()(A0 const& a0,const A0 & a1,A0 & a2,A1 & a3) const
    {
      a2 = boost::simd::remainder(A1(a0), A1(a1));
      a3 = boost::simd::idivround(A1(a0), A1(a1));
      return 0;
    }
  };  
} } }

#endif
