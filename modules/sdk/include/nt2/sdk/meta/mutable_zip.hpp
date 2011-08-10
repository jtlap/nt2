/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_META_MUTABLE_ZIP_HPP_INCLUDED
#define NT2_SDK_META_MUTABLE_ZIP_HPP_INCLUDED

#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/include/zip_view.hpp>

////////////////////////////////////////////////////////////////////////////////
// Build a zip_view of mutable elements
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  template<class S1,class S2>
  boost::fusion::zip_view< boost::fusion::vector<S1&,S2&> >
  mutable_zip(S1& s1, S2& s2)
  {
    typedef boost::fusion::vector<S1&,S2&> sequences;
    return boost::fusion::zip_view<sequences>( sequences ( s1,s2 ) );
  }
} }

#endif
