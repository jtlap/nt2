//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_SIMD_TOOLBOX_IEEE_INCLUDE_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_IEEE_INCLUDE_HPP_INCLUDED
#include <boost/simd/sdk/simd/preprocessor/include.hpp>

#define BOOST_SIMD_IEEE_BASE() boost/simd/toolbox/ieee/functions/scalar/
#define BOOST_SIMD_IEEE_RELATIVE() boost/simd/toolbox/ieee/functions/

#define BOOST_SIMD_IEEE_INCLUDE(F) BOOST_SIMD_RELATIVE_INCLUDE(BOOST_SIMD_IEEE_RELATIVE, F)


#include <boost/simd/toolbox/constant/include/constants/true_false.hpp>

#endif
