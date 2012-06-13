//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SCALAR_SATURATE_TO_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SCALAR_SATURATE_TO_HPP_INCLUDED

#include <boost/simd/toolbox/ieee/functions/saturate_to.hpp>
#include <boost/simd/include/constants/real.hpp>
#include <boost/simd/include/constants/properties.hpp>
#include <boost/simd/include/functions/min.hpp>
#include <boost/simd/include/functions/max.hpp>
#include <iostream>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::saturate_to_ , tag::cpu_,
                      (A0)(To),
                      (scalar_<signed_<A0> >)
                      (target_<scalar_<unsigned_<To> > > )               
                     )
  {
    typedef typename To::type result_type;
    result_type operator()(A0 const& a0, To const&) const
    {
      if (a0 < Zero<A0> ())
        return Valmin<result_type>();
      else if (a0 > Valmax<result_type>())
        return  Valmax<result_type>();
      else
        return a0;
    }
  };
  
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::saturate_to_ , tag::cpu_,
                      (A0)(To),
                      (scalar_<unsigned_<A0> >)
                      (target_<scalar_<signed_<To> > > )               
                     )
  {
    typedef typename To::type result_type;
    result_type operator()(A0 const& a0, To const&) const
    {
      if (a0 > Valmax<result_type>() ||
          result_type(a0) < Zero<result_type> ())
        return Valmax<result_type>();
      else 
        return boost::simd::min(result_type(a0),Valmax<result_type>());
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::saturate_to_ , tag::cpu_,
                      (A0)(To),
                      (scalar_<signed_<A0> >)
                      (target_<scalar_<signed_<To> > > )               
                     )
  {
    typedef typename To::type result_type;
    result_type operator()(A0 const& a0, To const&) const
    {
      if (a0 > Valmax<result_type>())
        return Valmax<result_type>();
      else if (a0 < Valmin<result_type>())
        return Valmin<result_type>();
      else
        return a0;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::saturate_to_ , tag::cpu_,
                      (A0)(To),
                      (scalar_<unsigned_<A0> >)
                      (target_<scalar_<unsigned_<To> > > )               
                     )
  {
    typedef typename To::type result_type;
    result_type operator()(A0 const& a0, To const&) const
    {
      if (a0 > Valmax<result_type>())
        return Valmax<result_type>();
      else
        return a0;
    }
  };
} } }
#endif
