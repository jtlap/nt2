/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_MEMORY_SLICE_HPP_INCLUDED
#define NT2_SDK_MEMORY_SLICE_HPP_INCLUDED

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
  template<class Strategy> struct slice_  {};

  //////////////////////////////////////////////////////////////////////////////
  // slice<Padding,Level>(sz) computes the nbr of element between the Level and
  // size(sz)th index level of a dimension sets
  //////////////////////////////////////////////////////////////////////////////
  template<class Strategy,class Info>
  struct functor< slice_<Strategy>, Info >
  {
    struct validate { typedef boost::mpl::true_ result_type; };

    template<class Sig> struct result;

    template<class This,class Seq,int N,int S>
    struct result<This(Seq,boost::mpl::int_<N>,boost::mpl::int_<S>)>
    {
      typedef call<slice_<Strategy>,tag::fusion_,Info>          callee;
      typedef typename  std::tr1
                      ::result_of<callee(Seq
                                        ,boost::mpl::int_<N>
                                        ,boost::mpl::int_<S>
                                        )>::type                type;
    };

    template<class A0,class A1,class A2> inline
    typename meta::enable_call<slice_<Strategy>(A0,A1,A2)>::type
    operator()(A0 const& a0, A1 const& a1, A2 const& a2) const
    {
      functors::call<slice_<Strategy>,tag::fusion_,Info>  callee;
      return callee(a0,a1,a2);
    }
  };
} }

namespace nt2
{
  template<class P, int N, class S> inline
  typename  nt2::meta
          ::enable_call<functors::slice_<P> ( S
                                            , boost::mpl::int_<N>
                                            , boost::mpl
                                              ::int_< boost::fusion
                                                      ::result_of::size<S>::value>
                                            )
                                  >::type
  slice(S const& s)
  {
    typedef boost::fusion::result_of::size<S> sz;
    functors::functor< functors::slice_<P> > callee;
    return callee(s,boost::mpl::int_<N>(),boost::mpl::int_<sz::type::value>());
  }
}

#endif
