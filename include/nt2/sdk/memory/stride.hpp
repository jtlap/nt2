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
  struct stride_  {};

  //////////////////////////////////////////////////////////////////////////////
  // slice<Level>(sz,padder) computes the nbr of element between the Level and
  // size(sz)th index level of a dimension sets
  //////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct functor< stride_, Info >
  {
    struct validate { typedef boost::mpl::true_ result_type; };

    template<class Sig> struct result;

    template<class This,class Seq,class N,class Padder>
    struct result<This(Seq const&,Padder const&,N const&)>
    {
      typedef call<stride_,tag::fusion_(Padder),Info>       callee;
      typedef typename  std::tr1
                      ::result_of < callee( Seq const&
                                          , Padder const&
                                          , N const&
                                          )
                                  >::type                   type;
    };

    template<class Seq,class N,class Padder> inline
    typename meta::enable_call<stride_(Seq const&,Padder const&,N const&)>::type
    operator()(Seq const& a0, Padder const& a1, N const& a2) const
    {
      functors::call<stride_,tag::fusion_(Padder),Info>  callee;
      return callee(a0,a1,a2);
    }
  };
} }

namespace nt2
{
  template<int N, class S,class P> inline
  typename  nt2::meta
          ::enable_call < functors::stride_ ( S const&
                                            , P const&
                                            , boost::mpl::long_<N> const&
                                            )
                        >::type
  stride(S const& s, P const& p)
  {
    functors::functor<functors::stride_> callee;
    return callee(s,p,boost::mpl::long_<N>());
  }
}

#endif
