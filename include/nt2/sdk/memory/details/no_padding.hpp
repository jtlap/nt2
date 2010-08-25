/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_MEMORY_NO_PADDING_HPP_INCLUDED
#define NT2_SDK_MEMORY_NO_PADDING_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Padding strategies for memory allocation
////////////////////////////////////////////////////////////////////////////////
#include <boost/mpl/pair.hpp>
#include <nt2/sdk/memory/slice.hpp>
#include <boost/tr1/functional.hpp>
#include <nt2/sdk/memory/stride.hpp>
#include <boost/fusion/include/at.hpp>
#include <nt2/sdk/memory/details/times.hpp>
#include <nt2/sdk/functor/preprocessor/call.hpp>

////////////////////////////////////////////////////////////////////////////////
// Various pre-made padding strategies
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace memory
{
  //////////////////////////////////////////////////////////////////////////////
  // No padding: all data are allocated as specified
  //////////////////////////////////////////////////////////////////////////////
  struct no_padding
  {
    typedef boost::mpl::pair<tag::padding,no_padding> nt2_settings_type;
  };
} }

////////////////////////////////////////////////////////////////////////////////
// slice Functor implementation
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace functors
{
  template<class Info>
  struct call<slice_<memory::no_padding>,tag::fusion_,Info>
  {
    template<class Sig> struct result;

    template<class This,class Seq,int N,int S>
    struct  result<This(Seq,boost::mpl::int_<N>,boost::mpl::int_<S>)>
          : std::tr1
            ::result_of < details::times( typename  boost::fusion
                                                    ::result_of::at_c < Seq const
                                                                      , N-1
                                                                      >::type
                                        , typename result < This( Seq
                                                                , boost::mpl::int_<N+1>
                                                                , boost::mpl::int_<S>
                                                                )
                                                          >::type
                                        )
                                >
    {};

    template<class This,class Seq, int N>
    struct  result< This(Seq,boost::mpl::int_<N>,boost::mpl::int_<N>)>
          : boost::fusion::result_of::at_c<Seq const, N-1>
    {};

    template<class Seq,int N, int S>
    typename result<call(Seq,boost::mpl::int_<N>,boost::mpl::int_<S>)>::type
    operator()( Seq const& s
              , boost::mpl::int_<N> const&
              , boost::mpl::int_<S> const&
              ) const
    {
      details::times callee;
      return callee ( slice<memory::no_padding,N+1>(s)
                    , boost::fusion::at_c<N-1>(s)
                    );
    }

    template<class S,int N>
    typename result<call(S, boost::mpl::int_<N>, boost::mpl::int_<N>)>::type
    operator()( S const& s
              , boost::mpl::int_<N> const&
              , boost::mpl::int_<N> const&
              ) const
    {
      return boost::fusion::at_c<N-1>(s);
    }
  };
} }

////////////////////////////////////////////////////////////////////////////////
// stride Functor implementation
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace functors
{
  template<class Info>
  struct call<stride_<memory::no_padding>,tag::fusion_,Info>
  {
    template<class Sig> struct result;

    template<class This,class Seq,int N>
    struct  result<This(Seq,boost::mpl::int_<N>)>
          : boost::fusion::result_of::at_c<Seq const,N-1>
    {};

    template<class Seq,int N>
    typename result<call(Seq,boost::mpl::int_<N>)>::type
    operator()( Seq const& s, boost::mpl::int_<N> const& ) const
    {
      return boost::fusion::at_c<N-1>(s);
    }
  };
} }


#endif
