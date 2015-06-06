//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_AD_IO_HPP_INCLUDED
#define NT2_AD_IO_HPP_INCLUDED

#include <nt2/include/functions/ad.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/repnum.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/one.hpp>
#include <iostream>
#include <nt2/core/container/table/table.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>

namespace nt2
{
  namespace ad
  {
    template<typename T>
    class valder
    {
    public:
      typedef T                                  value_t;
      typedef typename meta::scalar_of<T>::type   elem_t;
      typedef valder<T>                           type_t;
      valder()
        : value(Zero<T>()), derivative(One<value_t>())
      {};
      valder(const T& a)
        : value(a), derivative(One<value_t>())
      {};
      valder(const T& v, const T& d)
        : value(v), derivative(d)
      {};
      valder(const type_t& a)
        : value(a.val()), derivative(a.der())
      {};
      value_t val() const { return value; }
      value_t der() const{ return derivative; }
      value_t& val(const value_t & v) { return value = v; }
      value_t& der(const value_t & d) { return derivative = d; }

    private:
      T value,  derivative;
    };

    template<typename T>
    class valder <typename container::table<T>>
    {
    public:
      typedef typename container::table<T>                  value_t;
      typedef T                                              elem_t;
      typedef valder<typename nt2::container::table<T>>      type_t;
      valder()
        : value(), derivative()
      {};
      valder(const value_t & a)
        : value(a), derivative(ones(size(a), meta::as_<elem_t>()))
      {};
      valder(const value_t & v, const elem_t & d)
        : value(v), derivative(repnum(d, size(v)))
      {};
      valder(const elem_t & v, const elem_t & d)
        : value(repnum(v, size(d)), derivative(d))
      {};
      valder(const value_t & v, const value_t & d)
        : value(v), derivative(d)
      {};
      valder(const type_t& a)
        : value(a.val()), derivative(a.der())
      {};
      value_t  val() const { return value; }
      value_t  der() const{ return derivative; }
      value_t & val(const value_t & v) { return value = v; }
      value_t & der(const value_t & d) { return derivative = d; }
      template < class I1,  class I2>
      type_t operator()(const I1 & i1,  const I2 & i2) const
      {
        return type_t(value(i1, i2), derivative(i1, i2));
      }
      template < class I1,  class I2>
      type_t operator()(const I1 & i1,  const I2 & i2)
      {
        return type_t(value(i1, i2), derivative(i1, i2));
      }

    private:
      value_t value,  derivative;
    };

    template < class T >
    struct vtype
    {
      typedef T type;
    };
    template < class T >
    struct vtype<nt2::ad::valder<T>>
    {
      typedef  typename nt2::ad::valder<T>::value_t type;
    };

    template < class T >
    struct etype
    {
      typedef typename nt2::meta::scalar_of<T>::type type;
    };
    template < class T >
    struct etype<nt2::ad::valder<T>>
    {
      typedef typename nt2::ad::valder<T>::elem_t type;
    };
  }
}

#endif
