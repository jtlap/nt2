//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_SSE_AVX_DETAILS_LOAD_OFFSET_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_SSE_AVX_DETAILS_LOAD_OFFSET_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_AVX_SUPPORT
#include <boost/simd/sdk/simd/meta/as_simd.hpp>
#include <boost/simd/sdk/meta/scalar_of.hpp>
#include <boost/simd/include/functions/unaligned_load.hpp>
#include <boost/simd/sdk/memory/is_aligned.hpp>
#include <nt2/sdk/error/assert.hpp>

////////////////////////////////////////////////////////////////////////////////
// Register dispatch over load_ on simd types with an offset
////////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::load_ , boost::simd::tag::avx_
                            , (A0)(A1)(A2)(A3)
                            , (iterator_< scalar_< fundamental_<A0> > >)
                              (scalar_< fundamental_<A1> >)
                              ((target_< simd_< fundamental_<A2>, boost::simd::tag::avx_ > >))
                              (mpl_integral_< scalar_< integer_<A3> > >)
                            )
  {
    typedef typename A2::type result_type;

    ////////////////////////////////////////////////////////////////////////////
    // Some helpers for discriminating periodic and forward/backward offset
    ////////////////////////////////////////////////////////////////////////////
    template<class Type, class Offset>
    struct  is_periodic
          : boost::mpl
            ::bool_<  ( std::size_t(Offset::value)
                      % boost::simd::meta::cardinal_of<typename Type::type>::value
                      ) == 0 >
    {};

    template<class Offset>
    struct  is_forward : boost::mpl::bool_< (Offset::value > 0) >
    {};

    inline result_type operator()(const A0& a0, const A1& a1,
                                  const A2&, const A3&)const
    {
      BOOST_ASSERT_MSG
      ( boost::simd::memory::is_aligned(a0+a1,sizeof(result_type))
      , "load has been called on a pointer which alignment is not "
        "compatible with current SIMD extension."
      );

      return eval( a0, a1, typename is_periodic<A2,A3>::type() );
    }

    ////////////////////////////////////////////////////////////////////////////
    // Periodic case - Just add up to the runtime offset
    ////////////////////////////////////////////////////////////////////////////
    inline result_type eval ( A0 const& a0, A1 const& a1
                            , boost::mpl::true_ const&
                            ) const
    {
      BOOST_STATIC_CONSTANT
      ( std::size_t
      , offset  = std::size_t(A3::value)
      );

      return boost::simd::load<result_type>(a0,a1+offset);
    }

    ////////////////////////////////////////////////////////////////////////////
    // Non-periodic case
    ////////////////////////////////////////////////////////////////////////////
    inline result_type eval ( A0 const& a0, A1 const& a1
                            , boost::mpl::false_ const&
                            ) const
    {
      return boost::simd::unaligned_load<result_type>(a0+A3::value,a1);
    }
  };
} } }

#endif
#endif
