 /*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_META_MAKE_REAL_HPP_INCLUDED
#define NT2_SDK_META_MAKE_REAL_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Meta-function that creates a standard real type from a size in bytes.
// As all make_xxx, also provides an optional lambda to apply to the result.
// See: http://nt2.metascale.org/sdk/meta/traits/make_real.html
////////////////////////////////////////////////////////////////////////////////
#include <boost/mpl/apply.hpp>
#include <nt2/sdk/meta/na.hpp>

namespace nt2 { namespace meta
{
  template<std::size_t Size, class Transform = na_>
  struct  make_real;

  template<> struct  make_real<sizeof(double) , na_ > { typedef double  type; };
  template<> struct  make_real<sizeof(float)  , na_ > { typedef float   type; };

  template<class Transform>
  struct  make_real<sizeof(double),Transform>
        : boost::mpl::apply<Transform,double> {};

  template<class Transform>
  struct  make_real<sizeof(float),Transform>
        : boost::mpl::apply<Transform,float> {};
} }

#endif
