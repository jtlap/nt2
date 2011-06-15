//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_MEMORY_DETAILS_ALIGN_ON_HPP_INCLUDED
#define NT2_SDK_MEMORY_DETAILS_ALIGN_ON_HPP_INCLUDED

#include <nt2/sdk/meta/mpl.hpp>
#include <nt2/sdk/memory/parameters.hpp>
#include <nt2/sdk/memory/meta/align_on.hpp>
#include <nt2/sdk/memory/details/category.hpp>
#include <nt2/sdk/functor/preprocessor/call.hpp>

//==============================================================================
// Align integer on integer
//==============================================================================
NT2_REGISTER_DISPATCH ( tag::align_on_, tag::cpu_
                      , (A0)(A1)
                      , (scalar_< integer_<A0> >)(scalar_< integer_<A1> >)
                      )

namespace nt2 { namespace ext
{
  template<class A0, class A1, class Dummy>
  struct  call< tag::align_on_( meta::scalar_< meta::integer_<A0> >
                              , meta::scalar_< meta::integer_<A1> >
                              )
              , tag::cpu_, Dummy
              >
        : callable
  {
    typedef typename meta::strip<A0>::type result_type;

    result_type operator()(A0 const& a0, A1 const& a1) const
    {
      return (a0+a1-1) & ~(a1-1);
    }
  };
} }

//==============================================================================
// Align integer on mpl integer
//==============================================================================
NT2_REGISTER_DISPATCH ( tag::align_on_, tag::cpu_
                      , (A0)(A1)
                      , (scalar_< integer_<A0> >)
                        (mpl_integral_< scalar_< integer_<A1> > >)
                      )

namespace nt2 { namespace ext
{
  template<class A0, class A1, class Dummy>
  struct  call< tag::align_on_
                ( meta::scalar_< meta::integer_<A0> >
                , meta::mpl_integral_< meta::scalar_< meta::integer_<A1> > >
                )
              , tag::cpu_, Dummy
              >
        : callable
  {
    typedef typename meta::strip<A0>::type result_type;

    result_type operator()(A0 const& a0, A1 const& ) const
    {
      return (a0+A1::value-1) & ~(A1::value-1);
    }
  };
} }

//==============================================================================
// Align integer on default alignment
//==============================================================================
NT2_REGISTER_DISPATCH ( tag::align_on_, tag::cpu_
                      , (A0), (scalar_< integer_<A0> >)
                      )

namespace nt2 { namespace ext
{
  template<class A0, class Dummy>
  struct  call< tag::align_on_( meta::scalar_< meta::integer_<A0> > )
              , tag::cpu_, Dummy
              >
        : callable
  {
    typedef typename meta::strip<A0>::type result_type;

    result_type operator()(A0 const& a0 ) const
    {
      return nt2::memory::align_on<NT2_CONFIG_ALIGNMENT>(a0);
    }
  };
} }

//==============================================================================
// Align mpl integer on mpl integer
//==============================================================================
NT2_REGISTER_DISPATCH ( tag::align_on_, tag::cpu_
                      , (A0)(A1)
                      , (mpl_integral_< scalar_< integer_<A0> > >)
                        (mpl_integral_< scalar_< integer_<A1> > >)
                      )

namespace nt2 { namespace ext
{
  template<class A0, class A1, class Dummy>
  struct  call< tag::align_on_
                ( meta::mpl_integral_<meta::scalar_< meta::integer_<A0> > >
                , meta::mpl_integral_<meta::scalar_< meta::integer_<A1> > >
                )
              , tag::cpu_, Dummy
              >
        : callable
  {
    typedef typename meta::align_on < typename meta::strip<A0>::type
                                    , typename meta::strip<A1>::type
                                    >::type                         result_type;

    result_type operator()(A0 const&,A1 const&) const { return result_type(); }
  };
} }

//==============================================================================
// Align mpl integer on default alignment
//==============================================================================
NT2_REGISTER_DISPATCH ( tag::align_on_, tag::cpu_
                      , (A0), (mpl_integral_<scalar_< integer_<A0> > >)
                      )

namespace nt2 { namespace ext
{
  template<class A0, class Dummy>
  struct  call< tag::align_on_
                (meta::mpl_integral_<meta::scalar_< meta::integer_<A0> > >)
              , tag::cpu_, Dummy
              >
        : callable
  {
    typedef typename meta::align_on < typename meta::strip<A0>::type
                                    , boost::mpl::int_<NT2_CONFIG_ALIGNMENT>
                                    >::type                         result_type;

    result_type operator()(A0 const&) const { return result_type(); }
  };
} }

//==============================================================================
// Align iterator on integer
//==============================================================================
NT2_REGISTER_DISPATCH ( tag::align_on_, tag::cpu_
                      , (A0)(A1)
                      , (iterator_< generic_< fundamental_<A0> > >)
                        (scalar_< integer_<A1> >)
                      )

namespace nt2 { namespace ext
{
  template<class A0, class A1, class Dummy>
  struct  call< tag::align_on_
                ( meta::iterator_< meta::generic_< meta::fundamental_<A0> > >
                , meta::scalar_< meta::integer_<A1> >
                )
              , tag::cpu_, Dummy
              >
        : callable
  {
    typedef typename meta::strip<A0>::type result_type;

    result_type operator()(A0 const& a0, A1 const& a1) const
    {
      std::size_t ptr = reinterpret_cast<std::size_t>(a0);
      return reinterpret_cast<result_type>(nt2::memory::align_on(ptr,a1));
    }
  };
} }

//==============================================================================
// Align iterator on mpl integer
//==============================================================================
NT2_REGISTER_DISPATCH ( tag::align_on_, tag::cpu_
                      , (A0)(A1)
                      , (iterator_< generic_< fundamental_<A0> > >)
                        (mpl_integral_<scalar_< integer_<A1> > >)
                      )

namespace nt2 { namespace ext
{
  template<class A0, class A1, class Dummy>
  struct  call< tag::align_on_
                ( meta::iterator_< meta::generic_< meta::fundamental_<A0> > >
                , meta::mpl_integral_<meta::scalar_< meta::integer_<A1> > >
                )
              , tag::cpu_, Dummy
              >
        : callable
  {
    typedef typename meta::strip<A0>::type result_type;

    result_type operator()(A0 const& a0, A1 const& a1) const
    {
      std::size_t ptr = reinterpret_cast<std::size_t>(a0);
      return reinterpret_cast<result_type>(nt2::memory::align_on(ptr,a1));
    }
  };
} }

////////////////////////////////////////////////////////////////////////////////
// Align iterator on default alignment
////////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH ( tag::align_on_,tag::cpu_
                      , (A0), (iterator_< generic_< fundamental_<A0> > >)
                      )

namespace nt2 { namespace ext
{
  template<class A0, class Dummy>
  struct  call< tag::align_on_
                (meta::iterator_< meta::generic_< meta::fundamental_<A0> > >)
              , tag::cpu_, Dummy
              >
        : callable
  {
    typedef typename meta::strip<A0>::type result_type;

    result_type operator()(A0 const& a0) const
    {
      return nt2::memory::align_on<NT2_CONFIG_ALIGNMENT>(a0);
    }
  };
} }

#endif
