//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_OPERATOR_FUNCTIONS_SCALAR_MULTIPLIES_HPP_INCLUDED
#define BOOST_SIMD_OPERATOR_FUNCTIONS_SCALAR_MULTIPLIES_HPP_INCLUDED

#include <boost/simd/operator/functions/multiplies.hpp>
#include <boost/dispatch/attributes.hpp>
#include <boost/dispatch/meta/upgrade.hpp>
#include <boost/mpl/times.hpp>
#include <iostream>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::multiplies_, tag::cpu_
                                    , (A0)
                                    , (scalar_< arithmetic_<A0> >)
                                      (scalar_< arithmetic_<A0> >)
                                    )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(2) { return a0 * a1; }
  };

#ifdef __clang__
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::multiplies_, tag::cpu_
                                    , (A0)
                                    , (scalar_< uint16_<A0> >)
                                      (scalar_< uint16_<A0> >)
                                    )
  {
    // this is a workaround a clang pb
    // When multiplying two unsigned short clang internally promote to int
    // then a product as 65535*65535 of two short is not wrapped but produces
    // a signed integer overflow.
    // Note that the problem does not occur for unsigned int an unsigned long
    // nor for unsigned char
    // utype here is always uint32_t
    // C++ standard tells  in 3.9.1 Fundamental types, paragraph 4:
    //    Unsigned integers, declared unsigned, shall obey the laws of arithmetic
    //    modulo 2^n where n is the number of bits in the value representation
    //    of that particular size of integer.

    typedef A0 result_type;
    typedef typename dispatch::meta::upgrade<A0>::type utype;
    std::cout << "clang" << std::endl;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(2) { return A0(utype(a0) * utype(a1)); }
  };
#endif

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::multiplies_, tag::cpu_
                                    , (A0)(A1)
                                    , (mpl_integral_< scalar_< arithmetic_<A0> > >)
                                      (mpl_integral_< scalar_< arithmetic_<A1> > >)
                                    )
  {
    typedef typename mpl::times<A0, A1>::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const&, A1 const&) const
    {
      return result_type();
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::multiplies_, tag::cpu_
                                    , (A0)(A1)
                                    , (scalar_< arithmetic_<A0> >)
                                      (mpl_integral_< scalar_< arithmetic_<A1> > >)
                                    )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const&) const
    {
      return a0*A1::value;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::multiplies_, tag::cpu_
                                    , (A0)(A1)
                                    , (mpl_integral_< scalar_< arithmetic_<A0> > >)
                                      (scalar_< arithmetic_<A1> >)
                                    )
  {
    typedef A1 result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const&, A1 const& a1) const
    {
      return a1*A0::value;
    }
  };
} } }

#endif
