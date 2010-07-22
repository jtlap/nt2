/******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_CORE_NUMERIC_FUNCTION_SPLAT_HPP_INCLUDED
#define NT2_CORE_NUMERIC_FUNCTION_SPLAT_HPP_INCLUDED

#include <nt2/include/functor.hpp>
//#include <nt2/sdk/functor/meta/is_scalar.hpp>

namespace nt2 { namespace functors
{
  template<class T> struct splat_ {};

  ////////////////////////////////////////////////////////////////////////////
  // splat_ perform type dispatching based on the category of its target type
  // Hence, we need a specialized functor all together.
  ////////////////////////////////////////////////////////////////////////////
  template<class T,class Info> struct functor< splat_<T>, Info >
  {
    struct validate
    {
      /*
      template<class Sig> struct result;
      template<class This,class A0>
      struct  result<This(A0)> : meta::is_scalar<A0> {};
      */
      typedef boost::mpl::true_ result_type;
    };

    template<class Sig> struct result;
    template<class This,class A0> struct result<This(A0)>
    {
      typedef typename meta::category_of<T>::type::tag    dominant;
      typedef functors::call<splat_<T>,dominant,Info>     callee;
      typedef typename boost::result_of<callee(A0)>::type type;
    };

      template<class A0> inline
      typename meta::enable_call<splat_<T>(A0)>::type
      operator()(A0 const& a0) const
      {
        typedef typename meta::category_of<T>::type::tag    dominant;
        functors::call<splat_<T>,dominant,Info>     callee;
        return callee(a0);
      }
    };
} }

namespace nt2
{
  template<class T, class A0> inline
  typename meta::enable_call<functors::splat_<T>(A0)>::type
  splat(A0 const& a0)
  {
    NT2_FUNCTION_BODY(functors::splat_<T>,1)
  }
}

#include <nt2/sdk/constant/details/splat.hpp>

#endif
