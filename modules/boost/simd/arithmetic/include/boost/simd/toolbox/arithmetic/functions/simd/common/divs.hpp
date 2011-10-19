//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SIMD_COMMON_DIVS_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SIMD_COMMON_DIVS_HPP_INCLUDED

#include <boost/simd/toolbox/arithmetic/functions/divs.hpp>
#include <boost/simd/include/functions/is_eqz.hpp>
#include <boost/simd/include/functions/is_ltz.hpp>
#include <boost/simd/include/functions/is_equal.hpp>
#include <boost/simd/include/functions/plus.hpp>
#include <boost/simd/include/functions/minus.hpp>
#include <boost/simd/include/functions/bitwise_and.hpp>
#include <boost/simd/include/functions/divides.hpp>
#include <boost/simd/include/functions/select.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/mone.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/valmin.hpp>
#include <boost/simd/include/constants/valmax.hpp>
#include <boost/dispatch/meta/as_integer.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::divs_, tag::cpu_, (A0)(X)
                            , ((simd_<floating_<A0>,X>))
                              ((simd_<floating_<A0>,X>))
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return a0/a1;
    }
  };
  
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::divs_, tag::cpu_, (A0)(X)
                            , ((simd_<uint_<A0>,X>))
                              ((simd_<uint_<A0>,X>))
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      const A0 iseqza1 = is_eqz(a1);
      const A0 aa1 = a1+(iseqza1&One<A0>());
      const A0 r1 = a0/aa1; //a1!= 0
      const A0 r2 = select(is_eqz(a0),Zero<A0>(),Valmax<A0>());
      return select(iseqza1, r2, r1);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::divs_, tag::cpu_, (A0)(X)
                            , ((simd_<int_<A0>,X>))
                              ((simd_<int_<A0>,X>))
                            )
  {
    typedef A0 result_type;

    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      const A0 iseqza1 = is_eqz(a1);
      const A0 c = b_and(eq(a0,Valmin<A0>()),eq(a1, Mone<A0>()));
      const A0 aa1 = a1+(iseqza1&One<A0>());
      const A0 r1 = (a0-c)/aa1; //a1!= 0
      const A0 v2 = select(is_ltz(a0),Valmin<A0>(),Valmax<A0>());
      const A0 r2 = select(is_eqz(a0),Zero<A0>(),v2); //a1 == 0
      return select(iseqza1, r2, r1);
    }
  };
} } }

#endif
