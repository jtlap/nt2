/*******************************************************************************
 *         Copyright 2003-2010 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2010 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_META_LOGICAL_HPP_INCLUDED
#define NT2_SDK_META_LOGICAL_HPP_INCLUDED



namespace nt2
{
  // logical<T>::type is bool if T is anything but SIMD type in which case it is the SIMD type itself
  // The rationale is to provide an easy way to write common code for SIMD and scalar in various
  // situations of selection or test.
  namespace details
  {
    template<class T,class C> struct logical_impl  { typedef bool type; };
  }

  namespace meta
  {
    template<class T>
    struct  logical
          : details::logical_impl<T, typename category_of<T>::type> {};
  }
}


#endif

// /////////////////////////////////////////////////////////////////////////////
// End of logical.hpp
// /////////////////////////////////////////////////////////////////////////////
