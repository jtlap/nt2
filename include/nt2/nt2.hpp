/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_NT2_HPP_INCLUDED
#define NT2_NT2_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
/*!
  Provides direct access to all the base components of nt2 that makes it
  behaves like Matlab. Note that it also greatly increases compilation times.
  If you need to compile faster, you can decide to include the smallest set of
  components your code requires by using the files in the nt2/include/ directory.
 **/
////////////////////////////////////////////////////////////////////////////////
#include <nt2/include/config.hpp>
#include <nt2/include/error.hpp>
#include <nt2/include/timing.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/include/simd.hpp>

#endif
