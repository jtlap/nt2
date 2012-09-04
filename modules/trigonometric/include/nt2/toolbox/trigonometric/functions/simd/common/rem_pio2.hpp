//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_SIMD_COMMON_REM_PIO2_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_SIMD_COMMON_REM_PIO2_HPP_INCLUDED

#include <nt2/toolbox/trigonometric/functions/rem_pio2.hpp>

#include <boost/fusion/tuple.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/meta/cardinal_of.hpp>
#include <nt2/include/functions/simd/load.hpp>
#include <boost/simd/sdk/memory/aligned_type.hpp>
#include <nt2/toolbox/trigonometric/functions/scalar/impl/trigo/selection_tags.hpp>
//#include <iostream>

/////////////////////////////////////////////////////////////////////////////
// reference based Implementation
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::rem_pio2_, boost::simd::tag::simd_,
                      (A0)(X),
                      ((simd_ < floating_<A0>,X > ))
                    )
  {
    typedef typename meta::as_integer<A0>::type            itype;
    typedef boost::fusion::tuple<A0,A0,itype>        result_type;

    inline result_type operator()(A0 const& a0) const
    {
      result_type res;
      boost::fusion::at_c<2>(res) =
        nt2::rem_pio2(a0,
                      boost::fusion::at_c<0>(res),
                      boost::fusion::at_c<1>(res)
                     );
      return res;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION(  nt2::tag::rem_pio2_, tag::cpu_, (A0)(X)
                            , ((simd_<floating_<A0>,X>))
                              ((simd_<floating_<A0>,X>))
                              ((simd_<floating_<A0>,X>))
                            )
  {
    typedef typename meta::as_integer<A0>::type result_type;
    inline result_type operator()(A0 const& a0,A0 & xr,A0 & xc) const
    {
      typedef typename meta::scalar_of<A0>::type          stype;
      typedef typename meta::scalar_of<result_type>::type itype;
      static const nt2::uint32_t size = meta::cardinal_of<result_type>::value;
      BOOST_SIMD_ALIGNED_TYPE(itype) tmp[size];
      BOOST_SIMD_ALIGNED_TYPE(stype) txr[size];
      BOOST_SIMD_ALIGNED_TYPE(stype) txc[size];
      for(nt2::uint32_t i=0; i!=size; ++i)
      {
        // This prevent the may_alias ICE
        stype a = a0[i], r = txr[i], c = txc[i];
        tmp[i] =  nt2::rem_pio2(a, r, c);
        txr[i] = r;
        txc[i] = c;
      }

      xr = load<A0>(&txr[0], 0);
      xc = load<A0>(&txc[0], 0);
      return load<result_type>(&tmp[0], 0);
    }
  };
  
  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::rem_pio2_, tag::cpu_,
                             (A0)(A1)(X),
                             ((simd_ <floating_<A0>,X  > ))
                             ((simd_ <floating_<A0>,X  > ))
                             ((simd_ <floating_<A0>,X  > ))
                             ((target_ <unspecified_<A1> >))                          
                 )
  {
    typedef typename meta::as_integer<A0>::type result_type;
    inline result_type operator()(A0 const& a0, A0 & xr, A0& xc, A1 const&) const
    {
      typedef typename A1::type selector;
      return rempio2<selector, void>::rem(a0, xr, xc); 
    }
  private:
    template < class T, class dummy = void> struct rempio2
    {
      static inline result_type rem(A0 const& x, A0 & xr, A0& xc)
      {
        BOOST_ASSERT_MSG(false, "wrong target for rem_pio2"); 
        return Zero<result_type>();
      }
    };
    template < class dummy> struct rempio2 < big, dummy>
    {
      static inline result_type rem(A0 const& x, A0 & xr, A0& xc)
      {
        //        std::cout << "big" << std::endl; 
        return nt2::rem_pio2(x, xr, xc);
      }
    }; 
    template < class dummy> struct rempio2 < verysmall, dummy >
    {
      static inline result_type rem(A0 const& x, A0 & xr, A0& xc)
      {
        //        std::cout << "verysmall" << std::endl; 
        return nt2::rem_pio2_straight(x, xr, xc);
      }
    }; 
    template < class dummy> struct rempio2 < small_, dummy >
    {
      static inline result_type rem(A0 const& x, A0 & xr, A0& xc)
      {
        //        std::cout << "small" << std::endl; 
        return nt2::rem_pio2_cephes(x, xr, xc);
      }
    }; 
    template < class dummy> struct rempio2 < medium, dummy >
    {
      static inline result_type rem(A0 const& x, A0 & xr, A0& xc)
      {
        //        std::cout << "medium" << std::endl; 
        return nt2::rem_pio2_medium(x, xr, xc);
      }
    }; 
  }; 
  
} }
#endif
