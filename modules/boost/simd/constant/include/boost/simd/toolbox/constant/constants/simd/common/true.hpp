//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_SIMD_TRUE_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_SIMD_TRUE_HPP_INCLUDED

#include <boost/dispatch/meta/scalar_of.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/dispatch/meta/as_unsigned.hpp>
#include <boost/simd/sdk/meta/int_c.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( simd::tag::True, tag::cpu_, (A0)(X)
                                    , ((target_< simd_< arithmetic_<A0>,X> >))
                                    )
  {
    typedef typename A0::type result_type;

    inline result_type operator()(A0 const&) const
    {
      typedef typename dispatch::meta::as_integer<result_type>::type  tmp_type;
      typedef typename dispatch::meta::scalar_of<tmp_type>::type      cst_type;
      typedef typename dispatch::meta::as_unsigned<cst_type>::type    ucst_type;
      typedef meta::int_c<cst_type, ~ucst_type()>                     bits_type;
      
      return native_cast<result_type> ( boost::simd::
                                        splat<tmp_type>( cst_type(bits_type::value) )
                                      );
    }
  };
} } }

#endif
