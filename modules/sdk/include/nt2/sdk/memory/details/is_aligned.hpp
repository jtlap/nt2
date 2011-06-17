//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_MEMORY_DETAILS_IS_ALIGNED_HPP_INCLUDED
#define NT2_SDK_MEMORY_DETAILS_IS_ALIGNED_HPP_INCLUDED

#include <nt2/sdk/meta/mpl.hpp>
#include <nt2/sdk/memory/parameters.hpp>
#include <nt2/sdk/memory/meta/is_aligned.hpp>
#include <nt2/sdk/memory/details/category.hpp>
#include <nt2/sdk/functor/preprocessor/call.hpp>

//==============================================================================
// Check alignment of integer on integer
//==============================================================================
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::is_aligned_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< integer_<A0> >)
                              (scalar_< integer_<A1> >)
                            )
  {
    typedef bool result_type;

    NT2_FUNCTOR_CALL(2) { return !(a0 & (a1-1) ); }
  };
} }

//==============================================================================
// Check alignment of integer on mpl integer
//==============================================================================
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::is_aligned_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< integer_<A0> >)
                              (mpl_integral_< scalar_< integer_<A1> > >)
                            )
  {
    typedef bool result_type;

    NT2_FUNCTOR_CALL(2)
    {
      ignore_unused(a1);
      return !(a0 & (A1::value-1) );
    }
  };
} }

//==============================================================================
// Check alignment of integer on default alignment
//==============================================================================
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::is_aligned_, tag::cpu_
                            , (A0)
                            , (scalar_< integer_<A0> >)
                            )
  {
    typedef bool result_type;

    NT2_FUNCTOR_CALL(1)
    {
      return nt2::memory::is_aligned<NT2_CONFIG_ALIGNMENT>(a0);
    }
  };
} }

//==============================================================================
// Check alignment of mpl integer on mpl integer
//==============================================================================
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::is_aligned_, tag::cpu_
                            , (A0)(A1)
                            , (mpl_integral_< scalar_< integer_<A0> > >)
                              (mpl_integral_< scalar_< integer_<A1> > >)
                            )
  {
    typedef bool result_type;
    NT2_FUNCTOR_CALL(2)
    {
      ignore_unused((a0,a1));
      return meta::is_aligned<A0,A1>::value;
    }
  };
} }

//==============================================================================
// Check alignment of mpl integer on default alignment
//==============================================================================
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::is_aligned_, tag::cpu_
                            , (A0)
                            , (mpl_integral_< scalar_< integer_<A0> > >)
                            )
  {
    typedef bool result_type;

    NT2_FUNCTOR_CALL(1)
    {
      return nt2::memory::is_aligned<NT2_CONFIG_ALIGNMENT>(a0);
    }
  };
} }

//==============================================================================
// Check alignment of iterator on integer
//==============================================================================
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::is_aligned_, tag::cpu_
                            , (A0)(A1)
                            , (iterator_<unspecified_<A0> >)
                              (scalar_< integer_<A1> >)
                            )
  {
    typedef bool result_type;

    NT2_FUNCTOR_CALL(2)
    {
      return nt2::memory::is_aligned( reinterpret_cast<std::size_t>(a0), a1 );
    }
  };
} }

//==============================================================================
// Check alignment of iterator on default alignment
//==============================================================================
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::is_aligned_,tag::cpu_
                            , (A0)
                            , (iterator_<unspecified_<A0> >)
                            )
  {
    typedef bool result_type;

    NT2_FUNCTOR_CALL(1)
    {
      return nt2::memory::is_aligned<NT2_CONFIG_ALIGNMENT>(a0);
    }
  };
} }

#endif
