//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_SIMD_TOOLBOX_PREDICATES_FUNCTIONS_IS_NOT_EQUAL_WITH_EQUAL_NANS_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_PREDICATES_FUNCTIONS_IS_NOT_EQUAL_WITH_EQUAL_NANS_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>


namespace boost { namespace simd { namespace tag
  {         
    struct is_not_equal_with_equal_nans_ {};
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::is_not_equal_with_equal_nans_, is_not_equal_with_equal_nans, 2)
} }
 
#endif

// modified by jt the 25/12/2010
