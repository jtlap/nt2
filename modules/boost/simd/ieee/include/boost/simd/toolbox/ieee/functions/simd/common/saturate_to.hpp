//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SIMD_COMMON_SATURATE_TO_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SIMD_COMMON_SATURATE_TO_HPP_INCLUDED

#include <boost/simd/toolbox/ieee/functions/saturate_to.hpp>
#include <boost/simd/include/functions/simd/if_else.hpp>
#include <boost/simd/include/functions/simd/if_zero_else.hpp> 
#include <boost/simd/include/functions/simd/splat.hpp>
#include <boost/simd/include/functions/simd/is_greater.hpp>
#include <boost/simd/include/functions/simd/is_less.hpp>
#include <boost/simd/include/functions/simd/is_ltz.hpp>
#include <boost/simd/include/constants/valmax.hpp>
#include <boost/simd/include/constants/valmin.hpp>
#include <boost/simd/include/functions/tofloat.hpp>
#include <boost/simd/include/functions/toint.hpp>
// TO DO metatest that input and output have same vector size

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::saturate_to_, tag::cpu_,
                                    (A0)(To)(X),
                                    ((simd_<int_<A0>,X>))
                                    ((target_<simd_<uint_<To> ,X > > ))               
                                    )
  {
    typedef typename To::type result_type;
    result_type operator()(A0 const& a0, To const&) const
    {
      return if_zero_else(is_ltz(a0), bitwise_cast<result_type>(a0)); 
    }
  };
  
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::saturate_to_, tag::cpu_,
                                    (A0)(To)(X),
                                    ((simd_<uint_<A0>,X>))
                                    ((target_<simd_<int_<To>,X> >  ))               
                                    )
  {
    typedef typename To::type result_type;
    result_type operator()(A0 const& a0, To const&) const
    {
      result_type a00 = bitwise_cast<result_type>(a0); 
      return if_else(is_ltz(a00), Valmax<result_type>(), a00); 
    }
  };
  
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::saturate_to_, tag::cpu_,
                                    (A0)(To)(X),
                                    ((simd_<uint_<A0>,X>))
                                    ((target_<simd_<uint_<To>,X> >  ))               
                                    )
  {
    typedef typename To::type result_type;
    result_type operator()(A0 const& a0, To const&) const
    {
      return a0; 
    }
  };
  
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::saturate_to_, tag::cpu_,
                                    (A0)(To)(X),
                                    ((simd_<int_<A0>,X>))
                                    ((target_<simd_<int_<To>,X> >  ))               
                                    )
  {
    typedef typename To::type result_type;
    result_type operator()(A0 const& a0, To const&) const
    {
      return a0; 
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::saturate_to_, tag::cpu_,
                                    (A0)(To)(X),
                                    ((simd_<integer_<A0>,X>))
                                    ((target_<simd_<floating_<To>,X> >  ))               
                                    )
  {
    typedef typename To::type result_type;
    result_type operator()(A0 const& a0, To const&) const
    {
      return tofloat(a0); 
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::saturate_to_, tag::cpu_,
                                    (A0)(To)(X),
                                    ((simd_<floating_<A0>,X>))
                                    ((target_<simd_<integer_<To>,X> >  ))               
                                    )
  {
    typedef typename To::type result_type;
    result_type operator()(A0 const& a0, To const&) const
    {
      return toint(a0); 
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::saturate_to_, tag::cpu_,
                                    (A0)(To)(X),
                                    ((simd_<floating_<A0>,X>))
                                    ((target_<simd_<floating_<To>,X> >  ))               
                                    )
  {
    typedef typename To::type result_type;
    result_type operator()(A0 const& a0, To const&) const
    {
      return a0; 
    }
  };  
} } }
#endif
