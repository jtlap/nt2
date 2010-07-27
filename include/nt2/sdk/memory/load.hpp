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
//* TODO: Documentation: http://nt2.lri.fr/sdk/memory/load.html
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/functor/functor.hpp>
#include <boost/type_traits/is_pointer.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <nt2/sdk/functor/preprocessor/function.hpp>

namespace nt2 { namespace functors
{
  //////////////////////////////////////////////////////////////////////////////
  // load tag with type and offset info
  //////////////////////////////////////////////////////////////////////////////
  template<class T, int Offset=0> struct load_ {};

  ////////////////////////////////////////////////////////////////////////////
  // load perform type dispatching based on the category of its target type
  // Hence, we need a specialized functor all together.
  ////////////////////////////////////////////////////////////////////////////
  template<class T, int Offset, class Info>
  struct functor< load_<T,Offset>, Info >
  {
    struct validate
    {
	  typedef boost::mpl::true_ result_type;
    };

    template<class Sig> struct result;
    template<class This,class A0,class A1> struct result<This(A0,A1)>
    {
      typedef typename meta::category_of<T>::type::tag        dominant;
      typedef functors::call<load_<T,Offset>,dominant,Info>   callee;
      typedef typename std::tr1::result_of<callee(A0,A1)>::type  type;
    };

    template<class A0,class A1> inline
    typename meta::enable_call<load_<T,Offset>(A0,A1)>::type
    operator()(A0* const& a0, A1 const& a1) const
    {
      typedef typename meta::category_of<T>::type::tag  dominant;
      functors::call<load_<T,Offset>,dominant,Info>     callee;
      return callee(a0,a1);
    }
  };
} }

namespace nt2
{
  template<class T, class A0,class A1> inline
  typename nt2::meta::enable_call<functors::load_<T>(A0,A1)>::type
  load(A0* const& a0,A1 const& a1 )
  {
    nt2::functors::functor< nt2::functors::load_<T> > callee;
    return callee(a0,a1);
  }

  template<class T, int Offset, class A0,class A1> inline
  typename nt2::meta::enable_call<functors::load_<T,Offset>(A0,A1)>::type
  load(A0* const& a0,A1 const& a1 )
  {
    nt2::functors::functor< nt2::functors::load_<T,Offset> > callee;
    return callee(a0,a1);
  }
}

#include <nt2/sdk/memory/details/load.hpp>

#endif
