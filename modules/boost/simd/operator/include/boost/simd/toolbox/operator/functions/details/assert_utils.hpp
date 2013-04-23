//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_DETAILS_ASSERT_UTILS_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_DETAILS_ASSERT_UTILS_HPP_INCLUDED

#include <boost/simd/include/functions/extract.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/allbits.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/simd/sdk/meta/scalar_of.hpp>

namespace boost { namespace simd
{

  template<class T>
  bool assert_all( T const& t )
  {
    for(std::size_t i = 0; i != meta::cardinal_of<T>::value; ++i)
      if(!extract(t, i))
        return false;
    return true;
  }

  template<class T>
  bool assert_is_mask( T const& t )
  {
    for(std::size_t i = 0; i != meta::cardinal_of<T>::value; ++i)
    {
      typedef typename meta::scalar_of<T>::type sT;
      sT v = extract(t, i);
      if(v != Zero<sT>() && v != Allbits<sT>())
        return false;
    }
    return true;
  }

} }

#endif
