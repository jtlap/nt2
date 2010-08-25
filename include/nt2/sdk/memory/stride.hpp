/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_MEMORY_STRIDE_HPP_INCLUDED
#define NT2_SDK_MEMORY_STRIDE_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Padding strategies and related functors
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/memory/padding.hpp>
#include <nt2/sdk/functor/functor.hpp>
#include <boost/fusion/include/size.hpp>
#include <nt2/sdk/functor/preprocessor/function.hpp>

////////////////////////////////////////////////////////////////////////////////
// Functor tags
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace functors
{
  template<class Strategy> struct stride_ {};

  //////////////////////////////////////////////////////////////////////////////
  // stride<Padding,Level>(sz) computes the nbr of elements between two index
  // at level Level
  //////////////////////////////////////////////////////////////////////////////
  template<class Strategy,class Info>
  struct functor< stride_<Strategy>, Info >
  {
    struct validate { typedef boost::mpl::true_ result_type; };

    template<class Sig> struct result;

    template<class This,class Seq,int N>
    struct result<This(Seq,boost::mpl::int_<N>)>
    {
      typedef call<stride_<Strategy>,tag::fusion_,Info>          callee;
      typedef typename  std::tr1
                      ::result_of<callee(Seq,boost::mpl::int_<N>)>::type  type;
    };

    template<class A0,class A1> inline
    typename meta::enable_call<stride_<Strategy>(A0,A1)>::type
    operator()(A0 const& a0, A1 const& a1) const
    {
      functors::call<stride_<Strategy>,tag::fusion_,Info>  callee;
      return callee(a0,a1);
    }
  };
} }

namespace nt2
{
  template<class P, int N, class Seq> inline
  typename nt2::meta::enable_call<functors::stride_<P> ( Seq
                                                      , boost::mpl::int_<N>
                                                      )
                                  >::type
  stride(Seq const& s)
  {
    functors::functor< functors::stride_<P> > callee;
    return callee(s,boost::mpl::int_<N>());
  }
}

#endif
