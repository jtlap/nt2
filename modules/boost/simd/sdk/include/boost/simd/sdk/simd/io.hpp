/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_SDK_SIMD_IO_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_IO_HPP_INCLUDED

#include <boost/simd/sdk/simd/native.hpp>
#include <boost/fusion/sequence/io/out.hpp>

namespace boost { namespace simd
{
  //////////////////////////////////////////////////////////////////////////////
  // Stream insertion for swar types
  //////////////////////////////////////////////////////////////////////////////
  template<class S,class E> inline std::ostream&
  operator<<( std::ostream& os, native<S,E> const & v )
  {
    return boost::fusion::operators::operator<<(os, v);
    #if 0
    // We want to display (u)int8_t as a number
    typedef typename
            boost::mpl::if_c< (sizeof(S)==1)
                            , int
                            , typename native<S,E>::value_type
                            >::type display_type;

    os << "{";
    for(std::size_t i=0;i<v.size()-1;++i)
      os << static_cast<display_type>(v[i]) << ",";
    os << static_cast<display_type>(v[v.size()-1UL]) << "}";
    return os;
    #endif
  }
} }

#endif
