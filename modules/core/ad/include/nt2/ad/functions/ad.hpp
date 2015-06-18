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
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/expand_to.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/one.hpp>
#include <iostream>
#include <nt2/core/container/table/table.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>
#include <boost/mpl/bool.hpp>

namespace nt2
{
  namespace ad
  {
    template<class T, class S = typename meta::is_scalar<T>::type>
    class valder;

    template<class T>
    class valder<T, boost::mpl::true_>
    {
    public:
      typedef T                                  value_t;
      typedef typename meta::scalar_of<T>::type   elem_t;
      typedef valder<T,boost::mpl::true_ >        type_t;
      typedef valder<T>                              v_t;
      valder()
        : value(Zero<T>()), derivative(Zero<value_t>())
      {};
      valder(const T& a)
        : value(a), derivative(Zero<value_t>())
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

    template<class T>
    class valder <T, boost::mpl::false_>
    {
    public:
      typedef typename meta::scalar_of<T>::type              elem_t;
      typedef typename container::table<elem_t>             value_t;
      typedef valder<T, boost::mpl::false_>                  type_t;
      typedef valder<value_t, boost::mpl::false_>               v_t;
      valder()
      : value(), derivative()
      {};
      valder(const value_t & a)
        : value(a), derivative(zeros(size(a), meta::as_<elem_t>()))
      {};
      valder(const value_t & v, const value_t & d)
        : value(v), derivative(expand_to(d, size(v)))
      {};
      valder(const type_t& a)
        : value(a.val()), derivative(a.der())
      {};
      value_t  val() const { return value; }
      value_t  der() const{ return derivative; }
      value_t & val(const value_t & v) { return value = v; }
      value_t & der(const value_t & d) { return derivative = d; }
      template < class I1,  class I2>
      v_t operator()(const I1 & i1,  const I2 & i2) const
      {
        return v_t(value(i1, i2), derivative(i1, i2));
      }
      template < class I1,  class I2>
      v_t operator()(const I1 & i1,  const I2 & i2)
      {
        return v_t(value(i1, i2), derivative(i1, i2));
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
