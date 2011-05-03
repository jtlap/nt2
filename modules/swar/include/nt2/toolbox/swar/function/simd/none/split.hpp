//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_SWAR_FUNCTION_SIMD_NONE_SPLIT_HPP_INCLUDED
#define NT2_TOOLBOX_SWAR_FUNCTION_SIMD_NONE_SPLIT_HPP_INCLUDED
#include <nt2/sdk/meta/upgrade.hpp>
#include <nt2/sdk/meta/templatize.hpp>
#include <nt2/sdk/meta/adapted_traits.hpp>
#include <nt2/sdk/constant/digits.hpp>
#include <boost/fusion/tuple.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/is_ltz.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::split_, tag::cpu_,
                        (A0)(N),
                        ((simd_<arithmetic_<A0>,tag::none_<N> >))
                       );

namespace nt2 { namespace ext
{
  template<class N, class Dummy>
  struct call<tag::split_(tag::simd_<tag::arithmetic_, tag::none_<N> > ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>
    {
      typedef typename meta::scalar_of<A0>::type                            stype;
      typedef typename meta::upgrade<stype>::type                           utype;
      typedef simd::native<utype,tag::none_<N> >                            ttype;
      typedef meta::is_floating_point<stype>                                 rtag;
      typedef simd::native<typename  meta::double__<A0>::type,tag::none_<N> > dtype;

      typedef typename boost::mpl::if_c<rtag::value,dtype,ttype>::type      rtype;
      typedef boost::fusion::tuple<rtype,rtype>                              type;
    };

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::scalar_of<A0>::type                            stype;
      typedef meta::is_floating_point<stype>                                 rtag;
      typedef typename meta::upgrade<stype>::type                           utype;
      typedef simd::native<utype,tag::none_<N> >                            ttype;
      typedef typename boost::mpl::if_c<rtag::value,
                                        simd::native<double,tag::none_<N> >,
	                                ttype>::type                        rtype;
      typename NT2_RETURN_TYPE(1)::type                                       res;
      typedef rtype                                                           tag;

      return res;
    }

  };
} }

#endif
