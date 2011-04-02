/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_MEMORY_DETAILS_ALIGN_ON_HPP_INCLUDED
#define NT2_SDK_MEMORY_DETAILS_ALIGN_ON_HPP_INCLUDED

#include <nt2/sdk/meta/mpl.hpp>
#include <nt2/sdk/memory/parameters.hpp>
#include <nt2/sdk/memory/meta/align_on.hpp>
#include <nt2/sdk/memory/details/category.hpp>
#include <nt2/sdk/functor/preprocessor/call.hpp>

////////////////////////////////////////////////////////////////////////////////
// Align integer on integer
////////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH ( tag::align_on_, tag::cpu_
                      , (A0)(A1)      , (integer_<A0>)(integer_<A1>)
                      )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct  call< tag::align_on_( tag::integer_, tag::integer_), tag::cpu_, Dummy>
        : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> : meta::strip<A0> {};

    NT2_FUNCTOR_CALL(2)
    {
      return (a0+a1-1) & ~(a1-1);
    }
  };
} }

////////////////////////////////////////////////////////////////////////////////
// Align integer on mpl integer
////////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH ( tag::align_on_, tag::cpu_
                      , (A0)(A1), (integer_<A0>)(mpl_integral_< integer_<A1> >)
                      )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct  call< tag::align_on_( tag::integer_, tag::mpl_integral_<tag::integer_>)
              , tag::cpu_, Dummy
              >
        : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> : meta::strip<A0> {};

    NT2_FUNCTOR_CALL(2)
    {
      return (a0+A1::value-1) & ~(A1::value-1);
    }
  };
} }

////////////////////////////////////////////////////////////////////////////////
// Align integer on default alignment
////////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH ( tag::align_on_, tag::cpu_, (A0), (integer_<A0>) )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct  call< tag::align_on_( tag::integer_), tag::cpu_, Dummy >
        : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::strip<A0> {};

    NT2_FUNCTOR_CALL(1)
    {
      return nt2::memory::align_on<NT2_CONFIG_ALIGNMENT>(a0);
    }
  };
} }

////////////////////////////////////////////////////////////////////////////////
// Align mpl integer on mpl integer
////////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH ( tag::align_on_, tag::cpu_
                      , (A0)(A1)
                      , (mpl_integral_< integer_<A0> >)(mpl_integral_< integer_<A1> >)
                      )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct  call< tag::align_on_( tag::mpl_integral_<tag::integer_>
                              , tag::mpl_integral_<tag::integer_>
                              )
              , tag::cpu_, Dummy
              >
        : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct  result<This(A0,A1)>
          : meta::align_on< typename meta::strip<A0>::type
                          , typename meta::strip<A1>::type
                          >
    {};

    NT2_FUNCTOR_CALL(2) { return typename NT2_RETURN_TYPE(2)::type(); }
  };
} }

////////////////////////////////////////////////////////////////////////////////
// Align mpl integer on default alignment
////////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH ( tag::align_on_, tag::cpu_
                      , (A0), (mpl_integral_< integer_<A0> >)
                      )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct  call< tag::align_on_(tag::mpl_integral_<tag::integer_>)
              , tag::cpu_, Dummy
              >
        : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct  result<This(A0)>
          : meta::align_on< typename meta::strip<A0>::type
                          , boost::mpl::int_<NT2_CONFIG_ALIGNMENT>
                          >
    {};

    NT2_FUNCTOR_CALL(1) { return typename NT2_RETURN_TYPE(1)::type(); }
  };
} }

////////////////////////////////////////////////////////////////////////////////
// Align iterator on integer
////////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH ( tag::align_on_, tag::cpu_
                      , (A0)(A1)      , (iterator_<fundamental_<A0> >)(integer_<A1>)
                      )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct  call< tag::align_on_( tag::iterator_<tag::fundamental_>
                              , tag::integer_
                              )
              , tag::cpu_, Dummy
              >
        : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> : meta::strip<A0> {};

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename NT2_RETURN_TYPE(2)::type type;
      std::size_t ptr = reinterpret_cast<std::size_t>(a0);
      return reinterpret_cast<type>(nt2::memory::align_on(ptr,a1));
    }
  };
} }

////////////////////////////////////////////////////////////////////////////////
// Align iterator on mpl integer
////////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH ( tag::align_on_, tag::cpu_
                      , (A0)(A1)
                      , (iterator_<fundamental_<A0> >)(mpl_integral_< integer_<A1> >)
                      )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct  call< tag::align_on_( tag::iterator_<tag::fundamental_>
                              , tag::mpl_integral_<tag::integer_>
                              )
              , tag::cpu_, Dummy
              >
        : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> : meta::strip<A0> {};

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename NT2_RETURN_TYPE(2)::type type;
      std::size_t ptr = reinterpret_cast<std::size_t>(a0);
      return reinterpret_cast<type>(nt2::memory::align_on(ptr,a1));
    }
  };
} }

////////////////////////////////////////////////////////////////////////////////
// Align iterator on default alignment
////////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::align_on_,tag::cpu_,(A0),(iterator_<fundamental_<A0> >))

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct  call< tag::align_on_(tag::iterator_<tag::fundamental_>), tag::cpu_, Dummy >
        : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::strip<A0> {};

    NT2_FUNCTOR_CALL(1)
    {
      return nt2::memory::align_on<NT2_CONFIG_ALIGNMENT>(a0);
    }
  };
} }

#endif
