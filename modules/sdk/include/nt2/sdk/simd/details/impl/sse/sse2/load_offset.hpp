/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_DETAILS_IMPL_SSE_SSE2_LOAD_OFFSET_HPP_INCLUDED
#define NT2_SDK_SIMD_DETAILS_IMPL_SSE_SSE2_LOAD_OFFSET_HPP_INCLUDED

#include <nt2/sdk/simd/meta/as_simd.hpp>

////////////////////////////////////////////////////////////////////////////////
// Register dispatch over load_ on simd types with an offset
////////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH ( tag::load_
                      , tag::cpu_
                      , (A0)(A1)(T)(N)
                      , (iterator_<fundamental_<A0> >)
                        (fundamental_<A1>)
                        ((target_< simd_< fundamental_<T>, tag::sse_ > >))
                        (mpl_integral_< integer_<N> >)
                      )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct  call< tag::load_( tag::iterator_<tag::fundamental_>
                          , tag::fundamental_
                          , tag::target_< tag::simd_<tag::fundamental_,tag::sse_> >
                          , tag::mpl_integral_<tag::integer_>
                          )
              , tag::cpu_
              , Dummy
              >
        : callable
  {
    template<class Sig> struct result;
    template<class This, class A0,class A1,class A2,class A3>
    struct result<This(A0,A1,A2,A3)> : meta::strip<A2>::type {};

    ////////////////////////////////////////////////////////////////////////////
    // Some helpers for discriminating periodic and forward/backward offset
    ////////////////////////////////////////////////////////////////////////////
    template<class Type, class Offset>
    struct  is_periodic
          : boost::mpl
            ::bool_<  ( Offset::value
                      % meta::cardinal_of<typename Type::type>::value
                      ) == 0 >
    {};

    template<class Offset>
    struct  is_forward : boost::mpl::bool_< (Offset::value > 0) >
    {};

    ////////////////////////////////////////////////////////////////////////////
    // Periodic case - Just add up to the runtime offset
    ////////////////////////////////////////////////////////////////////////////
    template<class A0,class A1,class A2,class A3>
    typename boost::lazy_enable_if_c< is_periodic<A2,A3>::value
                                    , NT2_RETURN_TYPE(4)
                                    >::type
    inline  operator()(A0 const& a0, A1 const& a1, A2 const&, A3 const&) const
    {
      BOOST_STATIC_CONSTANT
      ( std::size_t
      , offset = A3::value/ meta::cardinal_of<typename A2::type>::value
      );

      typedef typename NT2_RETURN_TYPE(4)::type type;
      return nt2::load<type>(a0,a1+offset);
    }

    ////////////////////////////////////////////////////////////////////////////
    // Forward, non-periodic case
    ////////////////////////////////////////////////////////////////////////////
    template<class A0,class A1,class A2,class A3>
    typename boost::lazy_enable_if_c< (  !is_periodic<A2,A3>::value
                                      &&  is_forward<A3>::value
                                      )
                                    , NT2_RETURN_TYPE(4)
                                    >::type
    inline  operator()(A0 const& a0, A1 const& a1, A2 const&, A3 const&) const
    {
      typedef typename NT2_RETURN_TYPE(4)::type type;

      BOOST_STATIC_CONSTANT( std::size_t, card    = meta::cardinal_of<type>::value);
      BOOST_STATIC_CONSTANT( std::size_t, offset  = A3::value/card                );
      BOOST_STATIC_CONSTANT( std::size_t, bytes   = 16/card                       );
      BOOST_STATIC_CONSTANT( std::size_t, shifta  = bytes*(A3::value%card)        );
      BOOST_STATIC_CONSTANT( std::size_t, shiftb  = bytes*(card-A3::value%card)   );

      typedef typename meta::as_simd< typename meta::scalar_of<type>::type
                                    , tag::sse_
                                    >::type     raw_type;

      type a      = load<type>(a0,a1+offset);
      type b      = load<type>(a0,a1+offset+1);
      __m128i sa = _mm_srli_si128(bitwise_cast<__m128i>(a.data_),shifta);
      __m128i sb = _mm_slli_si128(bitwise_cast<__m128i>(b.data_),shiftb);
      type that   = { bitwise_cast<raw_type>(_mm_or_si128(sa,sb)) };
      return that;
    }
    ////////////////////////////////////////////////////////////////////////////
    // backward, non-periodic case
    ////////////////////////////////////////////////////////////////////////////
    template<class A0,class A1,class A2,class A3>
    typename boost::lazy_enable_if_c< (  !is_periodic<A2,A3>::value
                                      && !is_forward<A3>::value
                                      )
                                    , NT2_RETURN_TYPE(4)
                                    >::type
    inline  operator()(A0 const& a0, A1 const& a1, A2 const&, A3 const&) const
    {
      typedef typename NT2_RETURN_TYPE(4)::type type;

      BOOST_STATIC_CONSTANT( std::size_t, card    = meta::cardinal_of<type>::value);
      BOOST_STATIC_CONSTANT( std::size_t, offset  = (-A3::value)/card             );
      BOOST_STATIC_CONSTANT( std::size_t, bytes   = 16/card                       );
      BOOST_STATIC_CONSTANT( std::size_t, shifta  = bytes*((-A3::value)%card)     );
      BOOST_STATIC_CONSTANT( std::size_t, shiftb  = bytes*(card-(-A3::value)%card));

      typedef typename meta::as_simd< typename meta::scalar_of<type>::type
                                    , tag::sse_
                                    >::type     raw_type;

      type a      = load<type>(a0,a1-offset);
      type b      = load<type>(a0,a1-offset-1);
      __m128i sa = _mm_slli_si128(bitwise_cast<__m128i>(a.data_),shifta);
      __m128i sb = _mm_srli_si128(bitwise_cast<__m128i>(b.data_),shiftb);
      type that   = { bitwise_cast<raw_type>(_mm_or_si128(sa,sb)) };
      return that;
    }
  };
} }

#endif
