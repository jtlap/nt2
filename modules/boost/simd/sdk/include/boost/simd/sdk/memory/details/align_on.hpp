//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_MEMORY_DETAILS_ALIGN_ON_HPP_INCLUDED
#define BOOST_SIMD_SDK_MEMORY_DETAILS_ALIGN_ON_HPP_INCLUDED

#include <boost/dispatch/meta/mpl.hpp>
#include <boost/type_traits/common_type.hpp>
#include <boost/simd/sdk/memory/parameters.hpp>
#include <boost/simd/sdk/memory/meta/align_on.hpp>
#include <boost/simd/sdk/memory/details/category.hpp>
#include <boost/simd/sdk/functor/preprocessor/call.hpp>

//==============================================================================
// Align integer on integer
//==============================================================================
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::align_on_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< integer_<A0> >)(scalar_< integer_<A1> >)
                            )
  {
    typedef typename boost::common_type<A0,A1>::type result_type;

    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      return (a0+a1-1) & ~(a1-1);
    }
  };
} } }

//==============================================================================
// Align integer on mpl integer
//==============================================================================
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::align_on_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< integer_<A0> >)
                              (mpl_integral_< scalar_< integer_<A1> > >)
                            )
  {
    typedef typename boost::common_type<A0,typename A1::value_type>::type result_type;
    inline result_type operator()(A0 const& a0, A1 const&)const
    {
      return (a0+A1::value-1) & ~(A1::value-1);
    }
  };
} } }

//==============================================================================
// Align integer on default alignment
//==============================================================================
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::align_on_, tag::cpu_
                            , (A0), (scalar_< integer_<A0> >)
                            )
  {
    typedef typename boost::common_type<A0,int>::type result_type;

    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return boost::simd::memory::align_on<BOOST_SIMD_CONFIG_ALIGNMENT>(a0);
    }
  };
} } }

//==============================================================================
// Align mpl integer on mpl integer
//==============================================================================
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::align_on_, tag::cpu_
                            , (A0)(A1)
                            , (mpl_integral_< scalar_< integer_<A0> > >)
                              (mpl_integral_< scalar_< integer_<A1> > >)
                            )
  {
    typedef typename meta::align_on<A0, A1>::type result_type;

    result_type operator()(A0 const&,A1 const&) const { return result_type(); }
  };
} } }

//==============================================================================
// Align mpl integer on default alignment
//==============================================================================
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::align_on_, tag::cpu_
                            , (A0), (mpl_integral_<scalar_< integer_<A0> > >)
                            )
  {
    typedef typename boost::simd::meta::align_on < A0
                                    , boost::mpl::int_<BOOST_SIMD_CONFIG_ALIGNMENT>
                                    >::type                         result_type;

    result_type operator()(A0 const&) const { return result_type(); }
  };
} } }

//==============================================================================
// Align iterator on integer
//==============================================================================
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::align_on_, tag::cpu_
                            , (A0)(A1)
                            , (iterator_< generic_< fundamental_<A0> > >)
                              (scalar_< integer_<A1> >)
                            )
  {
    typedef A0 result_type;

    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      std::size_t ptr = reinterpret_cast<std::size_t>(a0);
      return reinterpret_cast<result_type>(boost::simd::memory::align_on(ptr,a1));
    }
  };
} } }

//==============================================================================
// Align iterator on mpl integer
//==============================================================================
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::align_on_, tag::cpu_
                            , (A0)(A1)
                            , (iterator_< generic_< fundamental_<A0> > >)
                              (mpl_integral_<scalar_< integer_<A1> > >)
                            )
  {
    typedef A0 result_type;

    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      std::size_t ptr = reinterpret_cast<std::size_t>(a0);
      return reinterpret_cast<result_type>(boost::simd::memory::align_on(ptr,a1));
    }
  };
} } }

////////////////////////////////////////////////////////////////////////////////
// Align iterator on default alignment
////////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::align_on_,tag::cpu_
                            , (A0), (iterator_< generic_< fundamental_<A0> > >)
                            )
  {
    typedef A0 result_type;

    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return boost::simd::memory::align_on<BOOST_SIMD_CONFIG_ALIGNMENT>(a0);
    }
  };
} } }

#endif
