/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_PACK_LOAD_HPP_INCLUDED
#define NT2_SDK_SIMD_PACK_LOAD_HPP_INCLUDED

namespace nt2 { namespace functors
{
  //////////////////////////////////////////////////////////////////////////////
  // When loading pack, we dispatch on the fact the underlying type is SIMD
  //////////////////////////////////////////////////////////////////////////////
  template<class T, int Offset,class X, class Info>
  struct dispatch<load_<T,Offset>,tag::simd_(tag::ast_,X),Info>
  {
    template<class A0,class A1>
    struct  apply
          : meta::is_native<typename meta::strip<T>::type::base_type>
    {};
  };

  template<class T,class X, class Info>
  struct dispatch<load_<T,0>,tag::simd_(tag::ast_,X),Info>
  {
    template<class A0,class A1>
    struct  apply
          : meta::is_native<typename meta::strip<T>::type::base_type>
    {};
  };

  //////////////////////////////////////////////////////////////////////////////
  // Loading from a native SIMD type
  //////////////////////////////////////////////////////////////////////////////
  template<class T, int Offset, class X, class Info>
  struct  call<load_<T,Offset>,tag::simd_(tag::ast_,X), boost::mpl::true_, Info>
        : callable
  {
    typedef T result_type;

    NT2_FUNCTOR_CALL(2)
    {
      T that = load<typename T::base_type,Offset>(a0,a1);
      return that;
    }
  };

  //////////////////////////////////////////////////////////////////////////////
  // Loading from an emulated SIMD type
  //////////////////////////////////////////////////////////////////////////////
  template<class T, int Offset, class X, class Info>
  struct  call<load_<T,Offset>,tag::simd_(tag::ast_,X), boost::mpl::false_, Info>
        : callable
  {
    typedef T result_type;

    NT2_FUNCTOR_CALL(2)
    {
      typename T::base_type values;
      for(typename T::size_type i=0;i<T::static_size;++i)
        values[i] = a0[T::static_size*a1+Offset+i];

      T that(values);
      return that;
    }
  };
} }

#endif
