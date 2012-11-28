//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_SSE_SSE2_DETAILS_LOAD_OFFSET_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_SSE_SSE2_DETAILS_LOAD_OFFSET_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSE2_SUPPORT

#include <boost/simd/sdk/simd/meta/as_simd.hpp>
#include <boost/simd/include/functions/simd/bitwise_cast.hpp>
#include <boost/simd/sdk/memory/is_aligned.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/assert.hpp>

////////////////////////////////////////////////////////////////////////////////
// Register dispatch over load_ on simd types with an offset
////////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::load_ , boost::simd::tag::sse2_
                            , (A0)(A1)(A2)(A3)
                            , (iterator_< scalar_< arithmetic_<A0> > >)
                              (scalar_< fundamental_<A1> >)
                              ((target_< simd_< arithmetic_<A2>, boost::simd::tag::sse_ > >))
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

      return eval ( a0, a1
                  , typename is_periodic<A2,A3>::type()
                  , typename is_forward<A3>::type()
                  );
    }

    ////////////////////////////////////////////////////////////////////////////
    // Periodic case - Just add up to the runtime offset
    ////////////////////////////////////////////////////////////////////////////
    template<class Fwd> inline result_type
    eval( A0 const& a0, A1 const& a1, boost::mpl::true_ const&, Fwd const&) const
    {
      BOOST_STATIC_CONSTANT
      ( std::size_t
      , offset  = std::size_t(A3::value)
      );

      return boost::simd::load<result_type>(a0,a1+offset);
    }

    ////////////////////////////////////////////////////////////////////////////
    // Forward, non-periodic case
    ////////////////////////////////////////////////////////////////////////////
    inline result_type eval ( A0 const& a0, A1 const& a1
                            , boost::mpl::false_ const&, boost::mpl::true_ const&
                            ) const
    {
      BOOST_STATIC_CONSTANT( std::size_t, card    = boost::simd::meta::cardinal_of<result_type>::value );
      BOOST_STATIC_CONSTANT( std::size_t, offset  = std::size_t(A3::value)/card*card      );
      BOOST_STATIC_CONSTANT( std::size_t, bytes   = 16u/card                              );
      BOOST_STATIC_CONSTANT( std::size_t, shifta  = bytes*(A3::value%card)                );
      BOOST_STATIC_CONSTANT( std::size_t, shiftb  = bytes*(card-A3::value%card)           );

      typedef typename dispatch::meta::as_integer<result_type>::type itype;

      result_type a     = boost::simd::load<result_type>(a0,a1+offset);
      result_type b     = boost::simd::load<result_type>(a0,a1+offset+card);
      __m128i sa        = _mm_srli_si128(boost::simd::bitwise_cast<itype>(a.data_),shifta);
      __m128i sb        = _mm_slli_si128(boost::simd::bitwise_cast<itype>(b.data_),shiftb);
      return boost::simd::bitwise_cast<result_type>(_mm_or_si128(sa,sb));
    }

    ////////////////////////////////////////////////////////////////////////////
    // backward, non-periodic case
    ////////////////////////////////////////////////////////////////////////////
    inline result_type eval ( A0 const& a0, A1 const& a1
                            , boost::mpl::false_ const&, boost::mpl::false_ const&
                            ) const
    {
      BOOST_STATIC_CONSTANT( std::size_t, card    = boost::simd::meta::cardinal_of<result_type>::value    );
      BOOST_STATIC_CONSTANT( std::size_t, offset  = std::size_t(-A3::value)/card*card        );
      BOOST_STATIC_CONSTANT( std::size_t, bytes   = 16/card                                  );
      BOOST_STATIC_CONSTANT( std::size_t, shifta  = bytes*(std::size_t(-A3::value)%card)     );
      BOOST_STATIC_CONSTANT( std::size_t, shiftb  = bytes*(card-std::size_t(-A3::value)%card));

      typedef typename dispatch::meta::as_integer<result_type>::type itype;

      result_type a     = boost::simd::load<result_type>(a0,a1-offset);
      result_type b     = boost::simd::load<result_type>(a0,a1-offset-card);
      __m128i sa        = _mm_slli_si128(boost::simd::bitwise_cast<itype>(a),shifta);
      __m128i sb        = _mm_srli_si128(boost::simd::bitwise_cast<itype>(b),shiftb);
      return boost::simd::bitwise_cast<result_type>(_mm_or_si128(sa,sb));
    }
  };
} } }

#endif
#endif
