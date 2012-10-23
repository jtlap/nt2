/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_UNIT_DETAILS_HELPERS_HPP_INCLUDED
#define NT2_SDK_UNIT_DETAILS_HELPERS_HPP_INCLUDED

#include <nt2/include/functions/splat.hpp>
#include <nt2/include/constants/valmin.hpp>
#include <nt2/include/constants/valmax.hpp>

namespace nt2
{
  ////////////////////////////////////////////////////////////////////////////////
  // roll a random number (will be nt2::rand afterward)
  ////////////////////////////////////////////////////////////////////////////////
  template<class T,class X, class Y> inline T roll(X mn, Y mx)
  {
    double r = ((double)rand()/RAND_MAX)*(mx-mn) + mn;
    T that  = nt2::splat<T>(r);
    return that;
  }

  template<class T> inline T roll()
  {
    return roll<T>(nt2::Valmin<T>()/2, nt2::Valmax<T>()/2) * 2;
  }
}
using nt2::roll;

#endif
