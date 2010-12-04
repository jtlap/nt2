/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_FUNCTOR_FORWARD_HPP_INCLUDED
#define NT2_SDK_FUNCTOR_FORWARD_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Forward declaration for functor elements
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace tag { struct cpu_ {}; } } // To do put elsewhere in config

namespace nt2
{
  template< class Function, class Site = tag::cpu_> struct functor;
}

namespace nt2 { namespace ext
{
  template< class Signature , class Site, class Dummy = void> struct call;
  template< class Signature , class Site, class Dummy = void> struct validate;
} }

#endif
