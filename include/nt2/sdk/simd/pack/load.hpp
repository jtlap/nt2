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
  template<class T, int Offset, class X, class Info>
  struct call<load_<T,Offset>,tag::simd_(tag::ast_,X), Info>
  {
    typedef T result_type;

    NT2_FUNCTOR_CALL_DISPATCH ( 2
                              , typename
                                meta::is_native<typename T::base_type>::type
                              , ( 2, (boost::mpl::true_, boost::mpl::false_))
                              )

    NT2_FUNCTOR_CALL_EVAL_IF(2,boost::mpl::true_)
    {
      T that = load<typename T::base_type,Offset>(a0,a1);
      return that;
    }

    NT2_FUNCTOR_CALL_EVAL_IF(2,boost::mpl::false_)
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
