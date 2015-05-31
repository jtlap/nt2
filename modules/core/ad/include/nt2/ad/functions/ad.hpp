//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_OPERATOR_FUNCTIONS_SCALAR_AD_HPP_INCLUDED
#define BOOST_SIMD_OPERATOR_FUNCTIONS_SCALAR_AD_HPP_INCLUDED

#include <nt2/include/functions/ad.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/one.hpp>

namespace nt2 { namespace ad
{
  template < class T >
  class valder
  {
  public:
    typedef T                         value_type;
    typedef valder<T>                     type_t;
    valder()
      : value(Zero<value_type>()), derivative(Zero<value_type>())
    { };
    valder(const value_type& a)
      : value(a), derivative(One<value_type>())
    { };
    valder(const value_type & v, const value_type & d)
      : value(v), derivative(d)
    { };
    valder(const type_t & a)
      : value(a.value), derivative(a.derivative)
    { };
    T& val(const T & v)
    { return value = v; }
    const T& val() const
    { return value; }
    T& der(const T& d)
    { return derivative = d; }
    const T& der() const
    { return derivative; }

  private:
    T value, derivative;
  };

} }

#endif
