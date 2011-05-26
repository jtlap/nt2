/*******************************************************************************
 *         Copyright 2003-2010 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2010 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_PACK_EVALUATION_HPP_INCLUDED
#define NT2_SDK_SIMD_PACK_EVALUATION_HPP_INCLUDED

#include <nt2/sdk/dsl/compute.hpp>
#include <nt2/sdk/dsl/category.hpp>
#include <nt2/sdk/dsl/litteral.hpp>
#include <nt2/sdk/dsl/evaluation.hpp>

////////////////////////////////////////////////////////////////////////////////
// Native pack
////////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::evaluate_, tag::cpu_,
                      (A0)(X)
                      (A1)(T)(C)(Tag)(Sema),
                      ((simd_<arithmetic_<A0>,X>))
                      ((expr_<A1, domain_< simd::domain<T,C> >,Tag, Sema>))
                     );

namespace nt2 { namespace ext
{
  template<class X,class T, class C, class Tag, class Sema, class Dummy>
  struct call < tag::evaluate_
                ( tag::simd_<tag::arithmetic_,X>
                , tag::expr_<simd::domain<T,C>, Tag, Sema>
                )
              , tag::cpu_, Dummy
              > : callable
  {
    typedef void result_type;

    template<class A0, class A1> inline void
    operator()( A0& a0, A1 const& a1) const
    {
      meta::as_<A0> target;
      meta::compile < meta::compute<boost::mpl::_1,tag::cpu_> > callee;
      a0 = callee(a1,target);
    }
  };
} }

////////////////////////////////////////////////////////////////////////////////
// Non-native pack
////////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH_TPL (  tag::evaluate_,tag::cpu_
                          , (class A0)(std::size_t N)
                            (class A1)(class T)(class C)(class Tag)(class Sema)
                          , ((array_<arithmetic_<A0>,N>))
                            ((expr_<A1, domain_< simd::domain<T,C> >,Tag, Sema>))
                          )

namespace nt2 { namespace ext
{
  template<std::size_t N,class T, class C, class Tag, class Sema, class Dummy>
  struct call < tag::evaluate_
                ( tag::array_<tag::arithmetic_,N>
                , tag::expr_<simd::domain<T,C>, Tag, Sema>
                )
              , tag::cpu_, Dummy
              > : callable
  {
    typedef void result_type;

    template<class A0, class A1> inline void
    operator()( A0& a0, A1 const& a1) const
    {
      meta::as_<A0> target;
      meta::compile< meta::compute<boost::mpl::_1,tag::cpu_> > callee;

      for(std::size_t i=0;i<C::value;++i)
          a0[i] = callee(a1,target,i);
    }
  };
} }

#endif
