//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_SPECIFIC_DETAILS_MAYBE_GENMASK_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_SPECIFIC_DETAILS_MAYBE_GENMASK_HPP_INCLUDED

#include <boost/simd/include/constants/digits.hpp>
#include <boost/simd/include/constants/nan.hpp>

#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_floating_point.hpp>

namespace boost { namespace simd { namespace details
{
  template<typename F, typename R, typename A0, typename Enable = void>
  struct as_native
  {
    typedef R type;
  };
   
  template<typename F, typename R, typename A0>
  struct as_native<F, R, A0, typename boost::enable_if_c<sizeof(R)!=sizeof(A0) || boost::is_same<R, bool>::value>::type>
  {
    typedef A0 type;
  };
  
  template<typename T, typename Enable = void>
  struct maybe_genmask_impl
  {
      T operator()(bool b) const
      {
          return b ? Mone<T>() : Zero<T>();
      }
  };
  
  template<typename T>
  struct maybe_genmask_impl<T, typename boost::enable_if< boost::is_floating_point<T> >::type>
  {
      T operator()(bool b) const
      {
          return b ? Nan<T>() : Zero<T>();
      }
  };
  
  template<class T>
  typename boost::disable_if<
    boost::is_same<T, bool>,
    T
  >::type
  maybe_genmask(T const& t)
  {
    return t;
  }
  
  template<class T, class A>
  typename boost::enable_if<
    boost::is_same<A, bool>,
    T
  >::type
  maybe_genmask(A const& t)
  {
    return maybe_genmask_impl<T>()(t);
  }
  
} } }

#endif
