//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_BLAS_DETAILS_WRAPPER_HPP_INCLUDED
#define NT2_BLAS_DETAILS_WRAPPER_HPP_INCLUDED

#include <nt2/sdk/config/types.hpp>
#include <boost/preprocessor/cat.hpp>

// INTERNAL ONLY
// This macro can be ifdef'ed to produce the correct symbol output for the
// FORTRAN library in use, adding or not the underscore to FORTRAN routine names
// By default we generate Name_
#ifndef NT2_F77NAME
#ifdef NT2_F77NAME_NO_UNDERSCORE
#define NT2_F77NAME(NAME) NAME
#else
#define NT2_F77NAME(NAME) BOOST_PP_CAT(NAME,_)
#endif
#endif

// INTERNAL ONLY
// This macro can be ifdef'ed to produce the correct symbol output for the
// FORTRAN library in use, setting the proper type to use integer type for
// BLAS
#ifndef NT2_F77INT
#define NT2_F77INT nt2::int32_t
// INTERNAL ONLY
// Type of long int required by BLAS
typedef NT2_F77INT      nt2_la_int;
#endif

// INTERNAL ONLY
// This macro can be ifdef'ed to produce the correct symbol output for the
// FORTRAN library in use, setting the proper type to use complex type for
// BLAS
#ifndef NT2_F77COMPLEX
#define NT2_F77COMPLEX void
// INTERNAL ONLY
// Type used by BLAS/LAPACK to pass array of complex
typedef NT2_F77COMPLEX  nt2_la_complex;
#endif

#endif

