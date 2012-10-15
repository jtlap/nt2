//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_COMMON_EXTRACT_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_COMMON_EXTRACT_HPP_INCLUDED

#include <boost/simd/toolbox/operator/functions/extract.hpp>
#include <boost/simd/include/functions/simd/bitwise_cast.hpp>
#include <boost/simd/sdk/meta/scalar_of.hpp>
#include <boost/simd/sdk/details/aliasing.hpp>
#include <boost/simd/sdk/simd/logical.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/sizeof.hpp>
#include <boost/simd/sdk/simd/native_tuple.hpp>
#include <boost/fusion/include/copy.hpp>
#include <boost/type_traits/remove_reference.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::extract_, tag::cpu_, (A0)(A1)(X)
                            , ((simd_< fusion_sequence_<A0>, X >))
                              (scalar_< integer_<A1> >)
                            )
  {
    struct extract_fusion
    {
      extract_fusion(A1 const& a1_)
        : a1(a1_)
      {
      }

      template<class Sig>
      struct result;

      template<class This, class T>
      struct result<This(T)>
       : dispatch::meta::strip<typename meta::scalar_of<T>::type>
      {
      };

      template<class T>
      typename meta::scalar_of<T>::type operator()(T const& a0) const
      {
        return extract(a0, a1);
      }

      A1 const& a1;
    };

    typedef typename meta::scalar_of<A0>::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& a1) const
    {
      result_type that;
      boost::fusion::copy(simd::as_tuple(a0, extract_fusion(a1)),that);
      return that;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::extract_, tag::cpu_, (A0)(A1)(X)
                            , ((simd_< arithmetic_<A0>, X >))
                              (scalar_< integer_<A1> >)
                            )
  {
    template<class Sig>
    struct result;

    template<class This, class A0_, class A1_>
    struct result<This(A0_, A1_)>
    {
      typedef typename meta::scalar_of<typename remove_reference<A0_>::type>::type stype;
      typedef typename meta::may_alias<stype>::type& type;
    };

    template<class A0_>
    BOOST_FORCEINLINE typename result<implement(A0_&, A1 const&)>::type
    operator()(A0_& a0, A1 const& a1) const
    {
      typedef typename meta::scalar_of<A0_>::type stype;
      return reinterpret_cast<typename meta::may_alias<stype>::type*>(&a0)[a1];
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::extract_, tag::cpu_, (A0)(A1)(X)
                            , (mpl::equal_to< mpl::sizeof_<A0>, mpl::sizeof_<typename A0::type> >)
                            , ((simd_< logical_<A0>, X >))
                              (scalar_< integer_<A1> >)
                            )
  {
    typedef typename meta::scalar_of<A0>::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& a1) const
    {
      return result_type(extract(bitwise_cast<typename A0::type>(a0), a1) ? true : false);
    }
  };

} } }

#endif
