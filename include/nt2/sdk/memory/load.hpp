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
#include <nt2/sdk/functor/functor.hpp>
#include <nt2/sdk/functor/preprocessor/function.hpp>

namespace nt2 { namespace functors
{
  //////////////////////////////////////////////////////////////////////////////
  // load tag with type and offset info
  //////////////////////////////////////////////////////////////////////////////
  template<class T, int Offset=0> struct load_ {};

  //////////////////////////////////////////////////////////////////////////////
  // We only load from a pointer + an integral offset
  //////////////////////////////////////////////////////////////////////////////
  template<class T,int Offset,class Category, class Info>
  struct  validate< load_<T,Offset>, Category, Info>
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct  result<This(A0,A1)>     // make it check for iterator
      : boost::mpl::and_< boost::is_pointer<typename meta::strip<A0>::type>
                        , boost::is_integral<typename meta::strip<A1>::type>
                        >
    {};
  };
} }

namespace nt2 { namespace meta
{
  //////////////////////////////////////////////////////////////////////////////
  // load category is given by T
  //////////////////////////////////////////////////////////////////////////////
  template<class T,int Offset, class Info, class A0,class A1>
  struct  categorize<functors::load_<T,Offset>,Info,A0,A1>
  {
    typedef typename meta::category_of<T>::type::tag type;
  };
} }

namespace nt2
{
  //////////////////////////////////////////////////////////////////////////////
  // Load a data of type T from the memory zone given by (a0,a1)
  //////////////////////////////////////////////////////////////////////////////
  template<class T,class A0,class A1> inline
  typename nt2::meta::enable_call<functors::load_<T>(A0 const&,A1 const&)>::type
  load(A0 const& a0,A1 const& a1 )
  {
    NT2_FUNCTION_BODY(functors::load_<T>,2)
  }

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
}

#include <nt2/sdk/memory/details/load.hpp>

#endif
