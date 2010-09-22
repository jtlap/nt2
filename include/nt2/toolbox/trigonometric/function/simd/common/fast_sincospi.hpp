//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_FUNCTION_SIMD_COMMON_FAST_SINCOSPI_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_FUNCTION_SIMD_COMMON_FAST_SINCOSPI_HPP_INCLUDED
#include <nt2/sdk/meta/adapted_traits.hpp>
#include <boost/fusion/tuple.hpp>
#include <nt2/sdk/meta/strip.hpp>
 #include <nt2/toolbox/trigonometric/function/simd/common/impl/trigo.hpp>
//  MIGRATION WARNING you have to provide the file for the previous include from
//  nt2/core/numeric/function/details/simd/common/impl/trigo.hpp
//  of the old nt2


namespace nt2 { namespace functors
{
  template<class Extension,class Info>
  struct validate<fast_sincospi_,tag::simd_(tag::arithmetic_,Extension),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : 
      meta::is_floating_point<A0>{};
  };
  /////////////////////////////////////////////////////////////////////////////
  // Compute fast_sincospi(const A0& a0)
  /////////////////////////////////////////////////////////////////////////////
  template<class Extension,class Info>
  struct call<fast_sincospi_,
              tag::simd_(tag::arithmetic_,Extension),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> { typedef boost::fusion::tuple<A0, A0>  type; };

    NT2_FUNCTOR_CALL(1)
    {
      typename NT2_CALL_RETURN_TYPE(1)::type res;
     impl::trig_base < A0,pi_tag
                      , fast_tag, tag::simd_type
                      >::sincosa( a0
                                , boost::fusion::at_c<0>(res)
                                , boost::fusion::at_c<1>(res)
                                );
    }
  };
} }

      
#endif
