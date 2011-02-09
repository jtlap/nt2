/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_MEMORY_DETAILS_IS_ALIGNED_HPP_INCLUDED
#define NT2_SDK_MEMORY_DETAILS_IS_ALIGNED_HPP_INCLUDED

#include <nt2/sdk/meta/mpl.hpp>
#include <nt2/sdk/memory/parameters.hpp>
#include <nt2/sdk/memory/meta/is_aligned.hpp>
#include <nt2/sdk/memory/details/category.hpp>
#include <nt2/sdk/functor/preprocessor/call.hpp>

////////////////////////////////////////////////////////////////////////////////
// Check alignment of integer on integer
////////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH ( tag::is_aligned_, tag::cpu_
                      , (A0)(A1)      , (integer_<A0>)(integer_<A1>)
                      )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct  call< tag::is_aligned_( tag::integer_, tag::integer_), tag::cpu_, Dummy>
        : callable
  {
    typedef bool result_type;
    NT2_FUNCTOR_CALL(2) { return !(a0 & (a1-1) ); }
  };
} }

////////////////////////////////////////////////////////////////////////////////
// Check alignment of integer on mpl integer
////////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH ( tag::is_aligned_, tag::cpu_
                      , (A0)(A1), (integer_<A0>)(mpl_integral_< integer_<A1> >)
                      )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct  call< tag::is_aligned_( tag::integer_
                                , tag::mpl_integral_<tag::integer_>
                                )
              , tag::cpu_, Dummy
              >
        : callable
  {
    typedef bool result_type;
    NT2_FUNCTOR_CALL(2) { return !(a0 & (A1::value-1) ); }
  };
} }

////////////////////////////////////////////////////////////////////////////////
// Check alignment of integer on default alignment
////////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH ( tag::is_aligned_, tag::cpu_, (A0), (integer_<A0>) )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct  call< tag::is_aligned_( tag::integer_), tag::cpu_, Dummy >
        : callable
  {
    typedef bool result_type;

    NT2_FUNCTOR_CALL(1)
    {
      return nt2::memory::is_aligned<NT2_CONFIG_ALIGNMENT>(a0);
    }
  };
} }

////////////////////////////////////////////////////////////////////////////////
// Check alignment of mpl integer on mpl integer
////////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH ( tag::is_aligned_, tag::cpu_
                      , (A0)(A1)
                      , (mpl_integral_< integer_<A0> >)(mpl_integral_< integer_<A1> >)
                      )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct  call< tag::is_aligned_( tag::mpl_integral_<tag::integer_>
                                , tag::mpl_integral_<tag::integer_>
                                )
              , tag::cpu_, Dummy
              >
        : callable
  {
    typedef bool result_type;

    NT2_FUNCTOR_CALL(2) { return meta::is_aligned<A0,A1>::value; }
  };
} }

////////////////////////////////////////////////////////////////////////////////
// Check alignment of mpl integer on default alignment
////////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH ( tag::is_aligned_, tag::cpu_
                      , (A0), (mpl_integral_< integer_<A0> >)
                      )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct  call< tag::is_aligned_(tag::mpl_integral_<tag::integer_>)
              , tag::cpu_, Dummy
              >
        : callable
  {
    typedef bool result_type;

    NT2_FUNCTOR_CALL(1)
    {
      return nt2::memory::is_aligned<NT2_CONFIG_ALIGNMENT>(a0);
    }
  };
} }

////////////////////////////////////////////////////////////////////////////////
// Check alignment of iterator on integer
////////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH ( tag::is_aligned_, tag::cpu_
                      , (A0)(A1)      , (iterator_<unspecified_<A0> >)(integer_<A1>)
                      )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct  call< tag::is_aligned_( tag::iterator_<tag::unspecified_>
                                , tag::integer_
                                )
              , tag::cpu_, Dummy
              >
        : callable
  {
    typedef bool result_type;

    NT2_FUNCTOR_CALL(2)
    {
      return nt2::memory::is_aligned( reinterpret_cast<std::size_t>(a0), a1 );
    }
  };
} }

////////////////////////////////////////////////////////////////////////////////
// Check alignment of iterator on mpl integer
////////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH ( tag::is_aligned_, tag::cpu_
                      , (A0)(A1)
                      , (iterator_<unspecified_<A0> >)(mpl_integral_< integer_<A1> >)
                      )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct  call< tag::is_aligned_( tag::iterator_<tag::unspecified_>
                                , tag::mpl_integral_<tag::integer_>
                                )
              , tag::cpu_, Dummy
              >
        : callable
  {
    typedef bool result_type;

    NT2_FUNCTOR_CALL(2)
    {
      return nt2::memory::is_aligned( reinterpret_cast<std::size_t>(a0), a1 );
    }
  };
} }

////////////////////////////////////////////////////////////////////////////////
// Check alignment of iterator on default alignment
////////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::is_aligned_,tag::cpu_,(A0),(iterator_<unspecified_<A0> >))

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct  call< tag::is_aligned_(tag::iterator_<tag::unspecified_>)
              , tag::cpu_, Dummy
              >
        : callable
  {
    typedef bool result_type;

    NT2_FUNCTOR_CALL(1)
    {
      return nt2::memory::is_aligned<NT2_CONFIG_ALIGNMENT>(a0);
    }
  };
} }

#endif
