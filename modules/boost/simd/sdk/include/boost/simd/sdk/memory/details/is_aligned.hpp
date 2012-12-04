//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_MEMORY_DETAILS_IS_ALIGNED_HPP_INCLUDED
#define BOOST_SIMD_SDK_MEMORY_DETAILS_IS_ALIGNED_HPP_INCLUDED

#include <boost/dispatch/meta/mpl.hpp>
#include <boost/simd/sdk/memory/parameters.hpp>
#include <boost/simd/sdk/memory/meta/is_aligned.hpp>
#include <boost/simd/sdk/memory/details/category.hpp>
#include <boost/simd/sdk/functor/preprocessor/call.hpp>

//==============================================================================
// Check alignment of integer on integer
//==============================================================================
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::is_aligned_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< integer_<A0> >)
                              (scalar_< integer_<A1> >)
                            )
  {
    typedef bool result_type;

    BOOST_SIMD_FUNCTOR_CALL(2) { return !(a0 & (a1-1) ); }
  };
} } }

//==============================================================================
// Check alignment of integer on mpl integer
//==============================================================================
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::is_aligned_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< integer_<A0> >)
                              (mpl_integral_< scalar_< integer_<A1> > >)
                            )
  {
    typedef bool result_type;

    inline result_type operator()(A0 const& a0, A1 const&)const
    {
      return !(a0 & (A1::value-1) );
    }
  };
} } }

//==============================================================================
// Check alignment of integer on default alignment
//==============================================================================
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::is_aligned_, tag::cpu_
                            , (A0)
                            , (scalar_< integer_<A0> >)
                            )
  {
    typedef bool result_type;

    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return boost::simd::memory::is_aligned<BOOST_SIMD_CONFIG_ALIGNMENT>(a0);
    }
  };
} } }

//==============================================================================
// Check alignment of mpl integer on mpl integer
//==============================================================================
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::is_aligned_, tag::cpu_
                            , (A0)(A1)
                            , (mpl_integral_< scalar_< integer_<A0> > >)
                              (mpl_integral_< scalar_< integer_<A1> > >)
                            )
  {
    typedef bool result_type;
    inline result_type operator()(const A0&, const A1&)const
    {
      return boost::simd::meta::is_aligned<A0,A1>::value;
    }
  };
} } }

//==============================================================================
// Check alignment of mpl integer on default alignment
//==============================================================================
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::is_aligned_, tag::cpu_
                            , (A0)
                            , (mpl_integral_< scalar_< integer_<A0> > >)
                            )
  {
    typedef bool result_type;

    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return boost::simd::memory::is_aligned<BOOST_SIMD_CONFIG_ALIGNMENT>(a0);
    }
  };
} } }

//==============================================================================
// Check alignment of iterator on integer
//==============================================================================
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::is_aligned_, tag::cpu_
                            , (A0)(A1)
                            , (iterator_<unspecified_<A0> >)
                              (scalar_< integer_<A1> >)
                            )
  {
    typedef bool result_type;

    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      return boost::simd::memory::is_aligned( reinterpret_cast<std::size_t>(a0), a1 );
    }
  };
} } }

//==============================================================================
// Check alignment of iterator on default alignment
//==============================================================================
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::is_aligned_,tag::cpu_
                            , (A0)
                            , (iterator_<unspecified_<A0> >)
                            )
  {
    typedef bool result_type;

    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return boost::simd::memory::is_aligned<BOOST_SIMD_CONFIG_ALIGNMENT>(a0);
    }
  };
} } }

#endif
