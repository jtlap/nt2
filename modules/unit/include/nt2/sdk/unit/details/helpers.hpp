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
#include <boost/dispatch/meta/is_signed.hpp>
#include <boost/mpl/bool.hpp>

namespace nt2
{
  ////////////////////////////////////////////////////////////////////////////////
  // roll a random number (will be nt2::rand afterward)
  ////////////////////////////////////////////////////////////////////////////////
  template<class T,class X, class Y> inline T roll(X mn, Y mx)
  {
    double r = ((double)rand()/RAND_MAX)*(mx-mn) + mn;
    return nt2::splat<T>(r);
  }

  template<class T, bool B>
  struct inner_roll;

  template<class T>
  struct inner_roll<T, true>
  {
    static inline T call()
    {
      double r1 = ((double)rand()/RAND_MAX);
      double r2 = ((double)rand()/RAND_MAX);
      return  (r1 > 0.5) ? r2*nt2::Valmin<T>() : r2*nt2::Valmax<T>();
    }
  };

  template<class T>
  struct inner_roll<T, false>
  {
    static inline T call()
    {
      double r1 = ((double)rand()/RAND_MAX);
      return r1*nt2::Valmax<T>();
    }
  };

  template<class T> inline T roll()
  {
    return inner_roll<T, boost::dispatch::meta::is_signed<T>::value>::call();
  }

}
using nt2::roll;

#endif
