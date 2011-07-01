//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_ARITHMETIC_FUNCTION_SIMD_COMMON_REMQUO_HPP_INCLUDED
#define NT2_TOOLBOX_ARITHMETIC_FUNCTION_SIMD_COMMON_REMQUO_HPP_INCLUDED
#include <boost/fusion/tuple.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/idivround.hpp>
#include <nt2/include/functions/tofloat.hpp>
#include <nt2/include/functions/is_gtz.hpp>
#include <nt2/include/functions/remainder.hpp>
/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION(tag::remquo_, tag::cpu_,
                         (A0)(X),
                         ((simd_<arithmetic_<A0>,X>))
                         ((simd_<arithmetic_<A0>,X>))
                        )
  {
      typedef typename meta::strip<A0>::type                 stA0;
      typedef typename meta::as_integer<A0>::type             iA0;             
      typedef boost::fusion::tuple<stA0,iA0>          result_type;
    
    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      result_type res;
      eval( a0, a1
          , boost::fusion::at_c<0>(res),  boost::fusion::at_c<1>(res)
          );
      return res;
    }
  private:
    template<class AA0,class AA1,class R0,class R1> inline void
    eval(AA0 const& a0,AA1 const& a1,R0& r0, R1& r1) const
    {
      r1 = idivround(a0, a1);
      r0 = remainder(a0, a1);
//       r1 = b_and(r1, nt2::Seven<R1>());
//       R1 r2 =  b_not(b_xor(nt2::Seven<R1>(), r1));
//       r1 = sel(is_gtz(b_and(a0, a1)), r1, r2); 
    }
  };
} }
#endif
