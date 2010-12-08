/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_MEMORY_LOAD_HPP_INCLUDED
#define NT2_SDK_MEMORY_LOAD_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Load from memory functor and function
// Documentation: http://nt2.lri.fr/sdk/memory/function/load.html
////////////////////////////////////////////////////////////////////////////////
#include <boost/mpl/always.hpp>
#include <nt2/sdk/functor/functor.hpp>
#include <nt2/sdk/meta/is_iterator.hpp>
#include <nt2/sdk/functor/preprocessor/function.hpp>

////////////////////////////////////////////////////////////////////////////////
// load_ tag
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace tag { struct load_ {}; } }

namespace nt2
{
  //////////////////////////////////////////////////////////////////////////////
  // Load a data of type T from the memory zone given by (a0,a1)
  //////////////////////////////////////////////////////////////////////////////
  template<class T,class A0,class A1> inline
  typename boost::lazy_enable_if_type
          < meta::is_iterator<A0>
          , meta::enable_call<tag::load_(A0,A1,meta::as_<T>,boost::mpl::int_<0>)>
          >::type
  load(A0 const& a0,A1 const& a1 )
  {
    functor<load_> callee;
    return callee(a0,a1,meta::as_<T>(),boost::mpl::int_<0>());
  }
/*
  //////////////////////////////////////////////////////////////////////////////
  // Load a data of type T from the memory zone given by (a0,a1) and a sub-type
  // level offset
  //////////////////////////////////////////////////////////////////////////////
  template<class T, int Offset, class A0,class A1> inline
  typename
  nt2::meta::enable_call<functors::load_<T,Offset>(A0 const&,A1 const&)>::type
  load(A0 const& a0,A1 const& a1 )
  {
    typedef nt2::functors::load_<T,Offset> tag_;
    NT2_FUNCTION_BODY(tag_,2)
  }
*/
}

#include <nt2/sdk/memory/details/load.hpp>

#endif
