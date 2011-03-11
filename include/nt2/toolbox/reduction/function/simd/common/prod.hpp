//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_REDUCTION_FUNCTION_SIMD_COMMON_PROD_HPP_INCLUDED
#define NT2_TOOLBOX_REDUCTION_FUNCTION_SIMD_COMMON_PROD_HPP_INCLUDED
#include <nt2/sdk/constant/digits.hpp>
#include <boost/fusion/tuple.hpp>
#include <boost/fusion/include/fold.hpp>
#include <nt2/sdk/meta/strip.hpp>



/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::prod_, tag::cpu_,
                       (A0)(X),
                       ((simd_<arithmetic_<A0>,X>))
                      );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::prod_(tag::simd_<tag::arithmetic_, X> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>
    {
      typedef typename meta::scalar_of<A0>::type                base;
      typedef typename std::tr1::result_of<meta::arithmetic(base)>::type type;
    };

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename NT2_RETURN_TYPE(1)::type     type;
      return boost::fusion::fold(a0,One<type>(),functor<tag::multiplies_>());
    }

  };
} }

#endif
// modified by jt the 05/01/2011
