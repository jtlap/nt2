//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SCALAR_BITWISE_AND_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SCALAR_BITWISE_AND_HPP_INCLUDED
#include <boost/simd/sdk/simd/logical.hpp>
#include <boost/mpl/sizeof.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/dispatch/meta/as_integer.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF ( boost::simd::tag::bitwise_and_ , tag::cpu_, (A0)(A1)
                                , (boost::mpl::equal_to < boost::mpl::sizeof_<A0>
                                                        , boost::mpl::sizeof_<A1>
                                                        >
                                  )
                                , (scalar_< arithmetic_<A0> >)
                                  (scalar_< arithmetic_<A1> >)
                                )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      typedef typename dispatch::meta::as_integer<A0, unsigned>::type bts;
      return bitwise_cast<A0>(bts(
        bitwise_cast<bts>(a0) &
        bitwise_cast<bts>(a1)
      )); 
    }
  };

//   BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::bitwise_and_, tag::cpu_, (A0)(A1)
//                             , (scalar_< logical_<A0> >)
//                               (scalar_< logical_<A1> >)
//                             )
//   {
//     typedef A0 result_type;
//     BOOST_SIMD_FUNCTOR_CALL(2) { return result_type(a0.value() & a1.value()); }
//   };

} } }

#endif
