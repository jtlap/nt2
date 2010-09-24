/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_CONSTANT_REAL_HPP_INCLUDED
#define NT2_SDK_CONSTANT_REAL_HPP_INCLUDED
////////////////////////////////////////////////////////////////////////////////
// Make True and False
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/constant/constant.hpp>
#include <nt2/sdk/constant/details/real_constant.hpp>

namespace nt2 { namespace constants
{
  struct nan_         {};
  struct m_half_      {};
  struct m_zero_      {};
  struct half_        {};
  struct third_       {};
  struct quarter_     {};
  struct ldexp_mask_  {};
  struct two_to_m10_  {};
  struct two_to_nmb_  {};
  struct pi_          {};
  struct split_factor_{};
  struct sqrt_2_o_2_  {};
  struct gold_        {};
  struct c_gold_      {};
}  }

namespace nt2
{
  NT2_CONSTANT_IMPLEMENTATION(constants::nan_         , Nan     )
  NT2_CONSTANT_IMPLEMENTATION(constants::m_half_      , Mhalf   )
  NT2_CONSTANT_IMPLEMENTATION(constants::m_zero_      , Mzero   )
  NT2_CONSTANT_IMPLEMENTATION(constants::half_        , Half    )
  NT2_CONSTANT_IMPLEMENTATION(constants::third_       , Third   )
  NT2_CONSTANT_IMPLEMENTATION(constants::quarter_     , Quarter )
  NT2_CONSTANT_IMPLEMENTATION(constants::ldexp_mask_  , Ldexpmask)
  NT2_CONSTANT_IMPLEMENTATION(constants::two_to_m10_  , Twotom10)
  NT2_CONSTANT_IMPLEMENTATION(constants::two_to_nmb_  , Two2nmb )
  NT2_CONSTANT_IMPLEMENTATION(constants::pi_          , Pi      ) 
  NT2_CONSTANT_IMPLEMENTATION(constants::split_factor_, Splitfactor) 
  NT2_CONSTANT_IMPLEMENTATION(constants::sqrt_2_o_2_  , Sqrt_2o_2) 
  NT2_CONSTANT_IMPLEMENTATION(constants::gold_        , Gold    ) 
  NT2_CONSTANT_IMPLEMENTATION(constants::c_gold_      , Cgold   ) 

}

////////////////////////////////////////////////////////////////////////////////
// Custom local real functor
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace functors
{
  template<class Category,uint64_t Double, uint32_t Float,class Info>
  struct  call<details::pattern<Double,Float>,tag::constant_(Category),Info>
        : details::real_constant<details::pattern<Double,Float>,Category>
  {};
} }

namespace nt2
{
  template<class Target, uint64_t D, uint32_t F> inline
  typename meta::enable_call<details::pattern<D,F>(meta::as_<Target>)>::type
  real_constant()
  {
    nt2::functors::functor< details::pattern<D,F> > callee;
    return callee( nt2::meta::as_<Target>() );
  }

  template<class Target, uint32_t F> inline
  typename meta::enable_call<details::pattern<0,F>(meta::as_<Target>)>::type
  single_constant()
  {
    nt2::functors::functor< details::pattern<0,F> > callee;
    return callee( nt2::meta::as_<Target>() );
  }

  template<class Target, uint64_t D> inline
  typename meta::enable_call<details::pattern<D,0>(meta::as_<Target>)>::type
  double_constant()
  {
    nt2::functors::functor< details::pattern<D,0> > callee;
    return callee( nt2::meta::as_<Target>() );
  }
}
////////////////////////////////////////////////////////////////////////////////
// Fill up the call needed for a real consatnt call
////////////////////////////////////////////////////////////////////////////////
#define NT2_CONSTANT_MAKE_REAL(NAME,DOUBLE,FLOAT)                         \
namespace nt2 { namespace functors                                        \
{                                                                         \
  template<class Category,class Info>                                     \
  struct  call<NAME,tag::constant_(Category),Info>                        \
        : details::real_constant<details::pattern<DOUBLE,FLOAT>,Category> \
  {};                                                                     \
} }                                                                       \
/**/

////////////////////////////////////////////////////////////////////////////////
// Real only constants
////////////////////////////////////////////////////////////////////////////////
NT2_CONSTANT_MAKE_REAL(constants::nan_         ,0xFFFFFFFFFFFFFFFFLL, 0xFFFFFFFF  )
NT2_CONSTANT_MAKE_REAL(constants::m_half_      ,0xBFE0000000000000LL, 0xBF000000  )
NT2_CONSTANT_MAKE_REAL(constants::m_zero_      ,0x8000000000000000LL, 0x80000000  )
NT2_CONSTANT_MAKE_REAL(constants::half_        ,0x3FE0000000000000LL, 0x3F000000  )
NT2_CONSTANT_MAKE_REAL(constants::third_       ,0x3FD5555555555555LL, 0x3EAAAAAB  )
NT2_CONSTANT_MAKE_REAL(constants::quarter_     ,0x3FD0000000000000LL, 0x3E800000  )
NT2_CONSTANT_MAKE_REAL(constants::ldexp_mask_  ,0x7FF0000000000000ll, 0x7F800000  ) //      9218868437227405312ll, 2139095040) 
NT2_CONSTANT_MAKE_REAL(constants::two_to_m10_  ,0x0804D558B7EB8AD0ll, 0x3a800000  )
NT2_CONSTANT_MAKE_REAL(constants::two_to_nmb_  ,0x4330000000000000ll, 0x4b000000  )
NT2_CONSTANT_MAKE_REAL(constants::pi_          ,0x400921fb54442d18ll, 0x40490fdb  )
NT2_CONSTANT_MAKE_REAL(constants::split_factor_,0x41a0000000000000ll, 0x46000000  ) 
NT2_CONSTANT_MAKE_REAL(constants::sqrt_2_o_2_  ,0x3fe6a09e667f3bcdLL, 0x3f3504f3  )
NT2_CONSTANT_MAKE_REAL(constants::gold_        ,0x3ff9e3779b97f4a8LL, 0x3fcf1bbd  )
NT2_CONSTANT_MAKE_REAL(constants::c_gold_      ,0x3fd8722191a02d61LL, 0x3ec3910d  )


/*
  namespace nt2 { namespace constants
  {
  } }

  namespace nt2
  {
  }
*/

////////////////////////////////////////////////////////////////////////////////
// Real only constants - PI related
////////////////////////////////////////////////////////////////////////////////
/*
NT2_CONSTANT_MAKE_REAL(constants::pi_     , 0x400921fb54442d18LL, 0x40490fdb)
NT2_CONSTANT_MAKE_REAL(constants::pi_o_2_ , 0x3ff921fb54442d18LL, 0x3fc90fdb)
NT2_CONSTANT_MAKE_REAL(constants::pi_o_4_ , 0x3fe921fb54442d18LL, 0x3f490fdb)
NT2_CONSTANT_MAKE_REAL(constants::pi_x_4_ , 0x402921fb54442d18LL, 0x41490fdb)
NT2_CONSTANT_MAKE_REAL(constants::pi_x_2_ , 0x401921fb54442d18LL, 0x40c90fdb)
NT2_CONSTANT_MAKE_REAL(constants::_4_o_pi_, 0x3ff45f306dc9c883LL, 0x3fa2f983)
NT2_CONSTANT_MAKE_REAL(constants::inv_pi_ , 0x3fd45f306dc9c883LL, 0x3ea2f983)
NT2_CONSTANT_MAKE_REAL(constants::pi_o_180_ , Category , boost::mpl::_
                        , 0x3f91df46a2529d3all,0x3c8efa35
                        );
NT2_CONSTANT_MAKE_REAL(constants::one_o_180_ , Category , boost::mpl::_
                        , 0x3f76c16c16c16c17ll,0x3bb60b61
                        );
NT2_CONSTANT_MAKE_REAL(constants::one_o_6_ , Category , boost::mpl::_
                        , 0x3fc5555555555555ll,0x3e2aaaab
                        );
NT2_CONSTANT_MAKE_REAL(constants::mone_o_6_ , Category , boost::mpl::_
                        , 0xbfc5555555555555ll,0xbe2aaaab
                        );
NT2_CONSTANT_MAKE_REAL(constants::one_o_120_ , Category , boost::mpl::_
                        , 0x3f81111111111111ll,0x3c088889
                        );
*/


#endif
