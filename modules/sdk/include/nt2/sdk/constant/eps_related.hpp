/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_CONSTANT_EPS_RELATED_HPP_INCLUDED
#define NT2_SDK_CONSTANT_EPS_RELATED_HPP_INCLUDED

#include <nt2/sdk/meta/from_bits.hpp>
#include <nt2/sdk/constant/splat.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>
#include <nt2/sdk/meta/adapted_traits.hpp>
#include <nt2/sdk/functor/preprocessor/call.hpp>
#include <nt2/sdk/constant/properties.hpp>

namespace nt2 { namespace tag
{
  struct eps__            {};
  struct half_eps__       {};
  struct _3_x_eps_        {};
  struct sqrt_eps_        {};
  struct forth_root_eps_  {};
  struct third_root_eps_  {};
  struct mlog_eps_2_      {};
  struct min_denormal_    {};
  struct smallest_pos_val_{};
} }

namespace nt2
{
  NT2_CONSTANT_IMPLEMENTATION(nt2::tag::eps__            , Eps           )
  NT2_CONSTANT_IMPLEMENTATION(nt2::tag::half_eps__       , Halfeps       )
  NT2_CONSTANT_IMPLEMENTATION(nt2::tag::_3_x_eps_        , Threeeps      )
  NT2_CONSTANT_IMPLEMENTATION(nt2::tag::sqrt_eps_        , Sqrteps       )
  NT2_CONSTANT_IMPLEMENTATION(nt2::tag::forth_root_eps_  , Fourthrooteps  )
  NT2_CONSTANT_IMPLEMENTATION(nt2::tag::third_root_eps_  , Thirdrooteps  )
  NT2_CONSTANT_IMPLEMENTATION(nt2::tag::mlog_eps_2_      , Mlogeps2      )
  NT2_CONSTANT_IMPLEMENTATION(nt2::tag::min_denormal_    , Mindenormal   )
  NT2_CONSTANT_IMPLEMENTATION(nt2::tag::smallest_pos_val_, Smallestposval)
}

#include <nt2/sdk/constant/details/eps_related.hpp>

#endif
