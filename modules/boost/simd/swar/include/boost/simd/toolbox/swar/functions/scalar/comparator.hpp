//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_SCALAR_COMPARATOR_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_SCALAR_COMPARATOR_HPP_INCLUDED
#include <boost/fusion/tuple.hpp>
#include <boost/simd/include/functions/min.hpp>
#include <boost/simd/include/functions/max.hpp>
#include <boost/simd/include/functions/any.hpp>
/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::comparator_, tag::cpu_,
                            (A0)(A1)(A2),
			     ((scalar_<arithmetic_<A0> >))
			     ((scalar_<arithmetic_<A1> >))
			     ((scalar_<arithmetic_<A2> >))
                           )
  {
      typedef A0           stA0;
      typedef boost::fusion::tuple<stA0,stA0,bool>     result_type;
    
    BOOST_SIMD_FUNCTOR_CALL(3)
    {
      result_type res;
      eval( a0, a1, a2
           , boost::fusion::at_c<0>(res)
           , boost::fusion::at_c<1>(res)
           , boost::fusion::at_c<2>(res)
           );
      return res;
    }
  private:
    template<class AA0,class AA2,class R0,class R1> inline void
    eval(AA0 const& a0, AA0 const& a1, AA2 const& a2, R0& r0, R1& r1, bool& modified)const
    {
      r0 = a0;
      r1 = a1;
      if (a2)
      {
        if ( (modified = (a0 > a1)) ) std::swap(r0, r1);
      }
      else
      {
        if ( (modified = (a1 > a0)) ) std::swap(r0, r1);
      }
//       r0 =  boost::simd::min(a0, a1);
//       r1 =  boost::simd::max(a0, a1);
//       if (a2) {
//    A0 t =  r1;
//    r1 = r0;
//    r0 = t;
//       }
//       modified = any(a0-r0);
    }
  };
} } }
#endif
