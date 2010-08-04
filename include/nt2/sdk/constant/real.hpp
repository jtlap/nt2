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
  // Real only constants
  struct m_half_      {};
  struct m_zero_      {};
  struct half_        {};
  struct third_       {};
  struct quarter_     {};
} }

namespace nt2
{
  NT2_CONSTANT_IMPLEMENTATION(constants::m_half_    , MHalf     )
  NT2_CONSTANT_IMPLEMENTATION(constants::m_zero_    , MZero     )
  NT2_CONSTANT_IMPLEMENTATION(constants::half_      , Half      )
  NT2_CONSTANT_IMPLEMENTATION(constants::third_     , Third     )
  NT2_CONSTANT_IMPLEMENTATION(constants::quarter_   , Quarter   )
}

////////////////////////////////////////////////////////////////////////////////
// Fill up the call needed for a real consatnt call
////////////////////////////////////////////////////////////////////////////////
#define NT2_CONSTANT_MAKE_REAL(NAME,DOUBLE,FLOAT)                         \
namespace nt2 { namespace functors                                        \
{                                                                         \
  template<class Category,class Info>                                     \
  struct  call<NAME,Category,Info>                                        \
        : details::real_constant<details::pattern<DOUBLE,FLOAT>,Category> \
  {};                                                                     \
} }                                                                       \
/**/

////////////////////////////////////////////////////////////////////////////////
// Real only constants
////////////////////////////////////////////////////////////////////////////////
NT2_CONSTANT_MAKE_REAL(constants::m_half_ , 0xBFE0000000000000LL, 0xBF000000  )
NT2_CONSTANT_MAKE_REAL(constants::m_zero_ , 0x8000000000000000LL, 0x80000000  )
NT2_CONSTANT_MAKE_REAL(constants::half_   , 0x3FE0000000000000LL, 0x3F000000  )
NT2_CONSTANT_MAKE_REAL(constants::third_  , 0x3FD5555555555555LL, 0x3EAAAAAB  )
NT2_CONSTANT_MAKE_REAL(constants::quarter_, 0x3FD0000000000000LL, 0x3E800000  )

/*
  namespace nt2 { namespace constants
  {
    struct two_to_m10_  {};
  } }

  namespace nt2
  {
    NT2_CONSTANT_IMPLEMENTATION(constants::two_to_m10_, Twotom10  )
  }
  NT2_CONSTANT_MAKE_REAL(constants::two_to_m10_, 0x804d558b7eb8ad0ll,0x3a800000 )
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
/*
////////////////////////////////////////////////////////////////////////////////
// Real only constants - Trigonometrics
////////////////////////////////////////////////////////////////////////////////
NT2_CONSTANT_MAKE_REAL(constants::inv_180_ , Category , boost::mpl::_
                        , 0x3f76c16c16c16c17ll,0x3BB60B61
                        )
NT2_CONSTANT_MAKE_REAL(constants::deg_in_rad_ , Category , boost::mpl::_
                        , 0x3f91df46a2529d39LL,0x3c8efa35
                        )
NT2_CONSTANT_MAKE_REAL(constants::rad_in_deg_ , Category , boost::mpl::_
                        , 0x404ca5dc1a63c1f8LL,0x42652ee1
                        )
NT2_CONSTANT_MAKE_REAL(constants::rad_in_deg_r_ , Category , boost::mpl::_
                        , 0xbce1e7ab456405f8ll,0xb53387c1
                        )

////////////////////////////////////////////////////////////////////////////////
// Real only constants - Remarkable values
////////////////////////////////////////////////////////////////////////////////
NT2_CONSTANT_MAKE_REAL(constants::gold_  , Category , boost::mpl::_
                        , 0x3ff9e3779b97f4a8LL,0x3fcf1bbd
                        )
NT2_CONSTANT_MAKE_REAL(constants::c_gold_, Category , boost::mpl::_
                        , 0x3fd8722191a02d61LL,0x3ec3910d
                        )
NT2_CONSTANT_MAKE_REAL(constants::sqrt_2_ , Category , boost::mpl::_
                        , 0x3ff6a09e667f3bcdLL,0x3fb504f3
                        )
NT2_CONSTANT_MAKE_REAL(constants::sqrt_2_o_2_  , Category , boost::mpl::_
                        , 0x3fe6a09e667f3bcdLL,0x3f3504f3
                        )

////////////////////////////////////////////////////////////////////////////////
// Real only constants - Log and Exp
////////////////////////////////////////////////////////////////////////////////
NT2_CONSTANT_MAKE_REAL(constants::exp_1_ , Category , boost::mpl::_
                        , 0x4005bf0a8b145769LL,0x402df854
                        )
NT2_CONSTANT_MAKE_REAL(constants::log_2_ , Category , boost::mpl::_
                        , 0x3fe62e42fefa39efLL,0x3f317218
                        )
NT2_CONSTANT_MAKE_REAL(constants::inv_log_2_ , Category , boost::mpl::_
                        , 0x3ff71547652b82feLL,0x3fb8aa3b
                        )
NT2_CONSTANT_MAKE_REAL(constants::log_10_ , Category , boost::mpl::_
                        , 0x40026bb1bbb55516LL,0x40135d8e
                        )
NT2_CONSTANT_MAKE_REAL(constants::inv_log_10_ , Category , boost::mpl::_
                        , 0x3fdbcb7b1526e50dLL,0x3ede5bd9
                        )
NT2_CONSTANT_MAKE_REAL(constants::log2_o_log10_ , Category , boost::mpl::_
                        , 0x3fd34413509f79ffLL,0x3e9a209b
                        )
NT2_CONSTANT_MAKE_REAL(constants::split_factor_ , Category, boost::mpl::_
                        , 0x41a0000000000000ll,0x46000000
                        )
*/

#endif
