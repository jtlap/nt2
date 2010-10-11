/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_FUNCTOR_HIERARCHY_HPP_INCLUDED
#define NT2_SDK_FUNCTOR_HIERARCHY_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Pre-made types hierarchy used for internal tag dispatching.
// Documentation: http://nt2.lri.fr/sdk/functor/hierarchy.html
////////////////////////////////////////////////////////////////////////////////
#include <boost/mpl/vector.hpp>
#include <nt2/sdk/meta/set.hpp>
#include <nt2/sdk/meta/join.hpp>
#include <nt2/sdk/config/types.hpp>

namespace nt2 { namespace functors
{
  typedef meta::set<>                                       empty_;
  typedef meta::set<bool>                                   bool_;
  typedef meta::set<uint8_t , int8_t  >                     int8_;
  typedef meta::set<uint16_t, int16_t >                     int16_;
  typedef meta::set<uint32_t, int32_t >                     int32_;
  typedef meta::set<uint64_t, int64_t >                     int64_;
  typedef int8_                                             types8_;
  typedef int16_                                            types16_;
  typedef meta::set<uint32_t, int32_t , float >             types32_;
  typedef meta::set<uint64_t, int64_t , double>             types64_;
  typedef meta::set<uint8_t , uint16_t, uint32_t, uint64_t> uint_;
  typedef meta::set<int8_t  , int16_t , int32_t , int64_t>  int_;
  typedef meta::set<float, double>                          real_;
  typedef meta::join<real_, int_>                           signed_;
  typedef uint_                                             unsigned_;
  typedef meta::join<uint_        , int_  >                 integer_;
  typedef meta::join<integer_     , real_ >                 arithmetic_;
  typedef meta::join<arithmetic_  , bool_ >                 fundamental_;

  //////////////////////////////////////////////////////////////////////////////
  // Ordered universal list of hierarchies
  // Modify if you added a new hierarchy
  //////////////////////////////////////////////////////////////////////////////
  typedef boost::mpl::vector14< functors::int8_
                              , functors::int16_
                              , functors::int32_
                              , functors::int64_
                              , functors::types32_
                              , functors::types64_
                              , functors::uint_
                              , functors::int_
                              , functors::real_
                              , functors::signed_
                              , functors::integer_
                              , functors::arithmetic_
                              , functors::bool_
                              , functors::fundamental_
                              > hierarchies;
} }

#endif
