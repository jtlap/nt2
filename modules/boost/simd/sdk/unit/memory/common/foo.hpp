//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef FOO_HPP_INCLUDED
#define FOO_HPP_INCLUDED

#include <boost/fusion/include/io.hpp>
#include <boost/fusion/include/at_c.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include "fill.hpp"

struct foo { short d; float f; char c; };
BOOST_FUSION_ADAPT_STRUCT(foo,(short,d)(float,f)(char,c))

template<> struct fill<foo>
{
  // Handle soa_proxy
  template<class T>
  inline void operator()(T v, std::size_t i, int m = 0) const
  {
    foo x = v;
    this->operator()(x,i,m);
    v = x;
  }

  inline void operator()(foo& v, std::size_t i, int m = 0) const
  {
    boost::fusion::at_c<0>(v) = short(1+i+m);
    boost::fusion::at_c<1>(v) = float(2+i+m);
    boost::fusion::at_c<2>(v) = char (3+i+m);
  }
};

inline std::ostream& operator<<(std::ostream& os, foo const& f )
{
  return boost::fusion::operator<<(os, f);
}

#endif
