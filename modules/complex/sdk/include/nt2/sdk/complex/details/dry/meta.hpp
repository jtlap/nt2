//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_COMPLEX_DETAILS_DRY_META_HPP_INCLUDED
#define NT2_SDK_COMPLEX_DETAILS_DRY_META_HPP_INCLUDED

#include <nt2/sdk/complex/hierarchy.hpp>
#include <nt2/sdk/complex/meta/real_of.hpp>
#include <boost/simd/sdk/simd/meta/as_simd.hpp>
#include <boost/dispatch/meta/property_of.hpp>
#include <boost/dispatch/meta/hierarchy_of.hpp>
#include <boost/dispatch/meta/scalar_of.hpp>

namespace nt2
{
  template<class T>
  struct dry;
}

namespace nt2 { namespace meta
{
  template<class T>
  struct real_of< nt2::dry<T> >
  {
    typedef T type;
  };
} }

namespace boost { namespace simd { namespace meta
{
  template<class T, class X>
  struct as_simd<nt2::dry<T>, X>
    : as_simd<T, X>
  {
  };
} } }

namespace boost { namespace dispatch { namespace meta
{
  template<class T, class Origin>
  struct property_of< nt2::dry<T>, Origin >
  {
    typedef dry_< typename property_of<T, Origin>::type > type;
  };
  
  template<class T, class Origin>
  struct hierarchy_of< nt2::dry<T>, Origin >
  {
    typedef typename remove_const<Origin>::type stripped;
    typedef typename mpl::if_< is_same< nt2::dry<T>, stripped >, stripped, Origin >::type origin_;
    typedef scalar_< dry_< typename property_of<T, origin_>::type > > type;
  };
  
  template<class T>
  struct scalar_of< nt2::dry<T> >
  {
    typedef nt2::dry<T> type;
  };
  
  template<class T>
  struct value_of< nt2::dry<T> >
  {
    typedef T type;
  };
  
} } }

#endif
