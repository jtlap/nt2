//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_SWAR_FUNCTIONS_COMPLEX_SIMD_COMMON_COMPARATOR_HPP_INCLUDED
#define NT2_TOOLBOX_SWAR_FUNCTIONS_COMPLEX_SIMD_COMMON_COMPARATOR_HPP_INCLUDED

#include <nt2/toolbox/swar/functions/comparator.hpp>
#include <nt2/include/functions/min.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/include/functions/any.hpp>
#include <nt2/include/functions/is_not_equal_with_equal_nans.hpp>
#include <boost/fusion/include/vector.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>
#include <nt2/sdk/complex/meta/as_real.hpp>
#include <nt2/include/functions/imag.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/as_dry.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::comparator_, tag::cpu_,
                             (A0)(A1)(X),
                             ((simd_<complex_ <arithmetic_<A0> >,X>))
                             ((simd_<complex_ <arithmetic_<A0> >,X>))
                             ((scalar_<integer_<A1> >))
                             ((simd_<complex_ <arithmetic_<A0> >,X>))
                             ((simd_<complex_ <arithmetic_<A0> >,X>))
                            )
  {
    typedef bool result_type;
    inline result_type operator()(A0 const& a0,A0 const& a1,const A1 & a2, A0 & r0, A0 & r1) const
    {
      if (a2)
      {
        r1 =  nt2::min(a0, a1);
        r0 =  nt2::max(a0, a1);
      }
      else
      {
        r0 =  nt2::min(a0, a1);
        r1 =  nt2::max(a0, a1);
      }
      return nt2::any(is_not_equal_with_equal_nans(a0, r0)); 
    }
  };
  
  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::comparator_, tag::cpu_,
                             (A0)(A1)(X),
                             ((simd_<complex_ < arithmetic_<A0> >,X>))
                             ((simd_<complex_ < arithmetic_<A0> >,X>))
                             ((scalar_<integer_<A1> >))
                            )
  {
    typedef boost::fusion::vector<A0,A0,bool>           result_type;
    inline result_type operator()(A0 const& a0,A0 const & a1,const A1 & a2) const
    {
      result_type res;
      boost::fusion::at_c<2>(res) = nt2::comparator(a0, a1, a2, boost::fusion::at_c<0>(res),  boost::fusion::at_c<1>(res)); 
      return res; 
    }
  };
} }
#endif
