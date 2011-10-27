//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SIMD_COMMON_ADDS_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SIMD_COMMON_ADDS_HPP_INCLUDED
#include <boost/mpl/logical.hpp>
#include <boost/simd/toolbox/arithmetic/functions/adds.hpp>
#include <boost/simd/include/functions/plus.hpp>
#include <boost/simd/include/functions/bitwise_or.hpp>
#include <boost/simd/include/functions/is_less.hpp>
#include <boost/simd/include/functions/is_greater.hpp>
#include <boost/simd/include/functions/is_gtz.hpp>
#include <boost/simd/include/functions/bitwise_and.hpp>
#include <boost/simd/include/functions/bitwise_andnot.hpp>
#include <boost/simd/include/functions/boolean_select.hpp>
#include <boost/simd/include/functions/min.hpp>
#include <boost/simd/include/functions/max.hpp>
#include <boost/simd/include/constants/valmin.hpp>
#include <boost/simd/include/constants/valmax.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is floating_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::adds_, tag::cpu_,
                          (A0)(X),
                          ((simd_<floating_<A0>,X>))
                          ((simd_<floating_<A0>,X>))
                         )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return boost::simd::add(a0, a1);
    }
  };

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is uint_
/////////////////////////////////////////////////////////////////////////////


  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::adds_, tag::cpu_,
                          (A0)(X),
                          ((simd_<uint_<A0>,X>))
                          ((simd_<uint_<A0>,X>))
                         )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      A0 a0pa1 = a0+a1;
      return boolean_select(lt(a0pa1, a0), Valmax<A0>(), a0pa1); 
    }
  };

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is int_
/////////////////////////////////////////////////////////////////////////////


  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::adds_, tag::cpu_,
                          (A0)(X),
                          ((simd_<int_<A0>,X>))
                          ((simd_<int_<A0>,X>))
                         )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      typedef typename meta::as_logical<A0>::type bA0; 
      //       A0 gtza0 = is_gtz(a0);
      //       A0 gtza1 = is_gtz(a1);
      //       A0 a0pa1 = a0+a1;
      //       A0 test1 = b_and(gtza0, b_and(gtza1, (lt(a0pa1, boost::simd::max(a0, a1))))); 
      //       A0 test2 = b_andnot(b_andnot(b_or(is_gtz(a0pa1),gt(a0pa1, boost::simd::min(a0, a1))),gtza0),gtza1);
      //       return select(test1,Valmax<A0>(),select(test2,Valmin<A0>(),a0pa1)); 
      bA0 gtza0 = is_gtz(a0);
      bA0 gtza1 = is_gtz(a1);
      //       std::cout << "a0 " << a0 << std::endl;
      //       std::cout << "a1 " << a1 << std::endl;
      //       std::cout << "gtza0 "<< gtza0 << std::endl;
      //       std::cout << "gtza1 "<< gtza1 << std::endl;
      A0 a0pa1 = a0+a1;
      //       std::cout << a0pa1 << std::endl;
      //       std::cout << boost::simd::max(a0, a1) << std::endl;
      //       std::cout << lt(a0pa1,a0) << std::endl;
      //      bA0 test1 = lt(a0pa1, boost::simd::max(a0, a1)); 
      bA0 test1 = b_and(gtza0, b_and(gtza1, lt(a0pa1, boost::simd::max(a0, a1))));
       //      std::cout << test1 << std::endl;
      bA0 test2 = b_andnot(b_or(is_gtz(a0pa1),gt(a0pa1, boost::simd::min(a0, a1))),
                        b_or(gtza0,gtza1)
                        );
       //      std::cout << test2 << std::endl;
      return boolean_select(test1,Valmax<A0>(),boolean_select(test2,Valmin<A0>(),a0pa1));
    }
  };
} } }
#endif
