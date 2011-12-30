//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_COMPLEX_DETAILS_COMPLEX_META_HPP_INCLUDED
#define NT2_SDK_COMPLEX_DETAILS_COMPLEX_META_HPP_INCLUDED

#include <nt2/sdk/complex/details/complex/fusion_adapt.hpp>
#include <nt2/sdk/complex/meta/real_of.hpp>
#include <nt2/sdk/complex/hierarchy.hpp>

namespace nt2 { namespace meta
{
  template<class T>
  struct real_of< std::complex<T> >
  {
    typedef T type;
  };
} }

namespace boost { namespace dispatch { namespace meta
{
  template<class T, class Origin>
  struct property_of< std::complex<T>, Origin >
  {
    typedef complex_< typename property_of<T, Origin>::type > type;
  };
  
  template<class T, class Origin>
  struct hierarchy_of< std::complex<T>, Origin >
  {
    typedef scalar_< complex_< typename property_of<T, Origin>::type > > type;
  };
} } }

namespace boost
{
  template<class T>
  struct is_floating_point< std::complex<T> > : is_floating_point<T>
  {
  };
}

#endif
