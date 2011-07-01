//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_OPERATOR_FUNCTION_SIMD_VMX_ALTIVEC_LOAD_OFFSET_HPP_INCLUDED
#define NT2_TOOLBOX_OPERATOR_FUNCTION_SIMD_VMX_ALTIVEC_LOAD_OFFSET_HPP_INCLUDED

#include <nt2/sdk/simd/meta/as_simd.hpp>

namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::load_, tag::cpu_, (A0)(A1)(A2)(A3)
                            , (iterator_<fundamental_<A0> >)
                              (fundamental_<A1>)
                              ((target_<simd_<fundamental_<A2>,tag::altivec_> >))
                              (mpl_integral_< integer_<A3> >)
                      )
  {
    typedef typename A2::type result_type;

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

    NT2_FUNCTOR_CALL(4)
    {
      return eval ( a0,a1
                  , typename is_periodic<A2,A3>::type()
                  , typename is_forward<A3>::type()
                  );
    }
    ////////////////////////////////////////////////////////////////////////////
    // Periodic case - Just add up to the runtime offset
    ////////////////////////////////////////////////////////////////////////////
    template<class X> inline result_type
    eval(A0 const& a0, A1 const& a1, boost::mpl::true_ const&, X const&) const
    {
      BOOST_STATIC_CONSTANT
      ( std::size_t, o = A3::value/meta::cardinal_of<result_type>::value );

      return nt2::load<result_type>(a0,a1+o);
    }

    ////////////////////////////////////////////////////////////////////////////
    // Forward, non-periodic case
    ////////////////////////////////////////////////////////////////////////////
    inline result_type eval ( A0 const& a0, A1 const& a1
                            , boost::mpl::false_ const&
                            , boost::mpl::true_  const&   ) const
    {
      typedef typename meta::scalar_of<result_type>::type scalar_type;
      BOOST_STATIC_CONSTANT( std::size_t, card   = meta::cardinal_of<result_type>::value);
      BOOST_STATIC_CONSTANT( std::size_t, offset = A3::value/card                );
      BOOST_STATIC_CONSTANT( std::size_t, bytes  = sizeof(scalar_type)           );
      BOOST_STATIC_CONSTANT( std::size_t, shift  = bytes*(A3::value%card)        );

      result_type a      = load<result_type>(a0,a1+offset);
      result_type b      = load<result_type>(a0,a1+offset+1);
      result_type that   = { vec_sld(a(),b(),shift) };
      return that;
    }

    ////////////////////////////////////////////////////////////////////////////
    // backward, non-periodic case
    ////////////////////////////////////////////////////////////////////////////
    inline result_type eval ( A0 const& a0, A1 const& a1
                            , boost::mpl::false_ const&
                            , boost::mpl::false_  const&  ) const
    {
      typedef typename meta::scalar_of<result_type>::type scalar_type;
      BOOST_STATIC_CONSTANT( std::size_t, card   = meta::cardinal_of<result_type>::value );
      BOOST_STATIC_CONSTANT( std::size_t, offset = -A3::value/card                );
      BOOST_STATIC_CONSTANT( std::size_t, bytes  = sizeof(scalar_type)            );
      BOOST_STATIC_CONSTANT( std::size_t, shift  = bytes*(card-(-A3::value)%card) );

      result_type a     = load<result_type>(a0,a1-offset);
      result_type b     = load<result_type>(a0,a1-offset-1);
      result_type that  = { vec_sld(b(),a(),shift) };
      return that;
    }
  };
} }

#endif
