//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTION_SCALAR_BITWISE_AND_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTION_SCALAR_BITWISE_AND_HPP_INCLUDED

#include <boost/mpl/sizeof.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/simd/sdk/meta/as_bits.hpp>

namespace boost { namespace dispatch { namespace meta
{
  BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION_IF ( boost::simd::tag::bitwise_and_ , tag::cpu_, (A0)(A1)
                                , (boost::mpl::equal_to < boost::mpl::sizeof_<A0>
                                                        , boost::mpl::sizeof_<A1>
                                                        >
                                  )
                                , boost::simd::tag::bitwise_and_ ( scalar_< fundamental_<A0> >
                                                    , scalar_< fundamental_<A1> >
                                                    )
                                , (scalar_< fundamental_<A0> >)
                                  (scalar_< fundamental_<A1> >)
                                )
  {
    typedef A0 result_type;
    BOOST_DISPATCH_FUNCTOR_CALL(2)
    {
      typename boost::simd::meta::as_bits<A0>::type t0 = {a0};
      typename boost::simd::meta::as_bits<A1>::type t1 = {a1};
      t0.bits &= t1.bits;
      return t0.value;
    }
  };
} } }

#endif
