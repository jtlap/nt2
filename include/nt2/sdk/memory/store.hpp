/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_MEMORY_STORE_HPP_INCLUDED
#define NT2_SDK_MEMORY_STORE_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Store a value in memory functor and function
// Documentation: http://nt2.lri.fr/sdk/memory/function/store.html
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace functors
{
  struct store_ {};

  ////////////////////////////////////////////////////////////////////////////
  // store perform type dispatching based on the category of its 1st type
  // Hence, we need a specialized functor all together.
  ////////////////////////////////////////////////////////////////////////////
  template<class Info> struct functor<store_, Info>
  {
    struct validate
    {
      template<class Sig> struct result;
      template<class This,class A0,class A1,class A2>
      struct  result<This(A0,A1,A2)>
            : boost::mpl::and_< boost::is_pointer<A1>
                              , boost::is_integral<A2>
                              >
            {};
    };

    template<class Sig> struct result;
    template<class This,class A0,class A1,class A2>
    struct result<This(A0,A1,A2)>
    {
      typedef typename meta::category_of<A0>::type::tag         dominant;
      typedef functors::call<store_,dominant,Info>              callee;
      typedef typename std::tr1::result_of<callee(A0,A1,A2)>::type type;
    };

    template<class A0,class A1,class A2> inline
    typename meta::enable_call<store_(A0,A1,A2)>::type
    operator()(A0 const& a0, A1 const& a1, A2 const& a2) const
    {
      typedef typename meta::category_of<A0>::type::tag dominant;
      functors::call<store_,dominant,Info>              callee;
      return callee(a0,a1,a2);
    }
  };
} }

namespace nt2
{
  template<class A0,class A1,class A2>
  typename nt2::meta::enable_call<functors::store_(A0,A1,A2)>::type
  store(A0 const& a0,A1 const& a1,A2 const& a2)
  {
    NT2_FUNCTION_BODY(functors::store_,3)
  }
}

#include <nt2/sdk/memory/details/store.hpp>

#endif
