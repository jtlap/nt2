//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_COMMON_SHIFT_RIGHT_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_COMMON_SHIFT_RIGHT_HPP_INCLUDED
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/mpl/logical.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/sizeof.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF ( boost::simd::tag::shift_right_, tag::cpu_,
                                  (A0)(A1)(X),
                                  ( boost::mpl::and_<
                                    boost::mpl::not_< boost::is_same<A0, A1> >
                                  , boost::mpl::equal_to
                                                < boost::mpl::sizeof_<A0>
                                                , boost::mpl::sizeof_<A1>
                                                >
                                 >),
                                  ((simd_<arithmetic_<A0>,X>))
                                  ((simd_<integer_<A1>,X>))
                                )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      typedef typename dispatch::meta::as_integer<A0>::type int_type;
      return bitwise_cast<result_type>(shift_right(boost::simd::bitwise_cast<int_type>(a0), a1));
    }
  };
} } }

#endif
