/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_MEMORY_DETAILS_LEAD_PADDING_HPP_INCLUDED
#define NT2_SDK_MEMORY_DETAILS_LEAD_PADDING_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Padding strategies for memory allocation
////////////////////////////////////////////////////////////////////////////////
#include <boost/mpl/pair.hpp>
#include <boost/typeof/typeof.hpp>
#include <nt2/sdk/memory/slice.hpp>
#include <nt2/sdk/memory/stride.hpp>
#include <nt2/sdk/memory/align_on.hpp>
#include <boost/fusion/include/at.hpp>
#include <nt2/sdk/memory/details/times.hpp>
#include <boost/fusion/include/value_at.hpp>
#include <nt2/sdk/functor/preprocessor/call.hpp>
#include <nt2/sdk/memory/no_padding.hpp>
#include <nt2/sdk/memory/global_padding.hpp>

////////////////////////////////////////////////////////////////////////////////
// slice Functor implementation
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace functors
{
  //////////////////////////////////////////////////////////////////////////////
  // For lead_padding slice, dispacth on the relative positino of the Level
  //////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  dispatch<slice_,tag::fusion_(memory::lead_padding),Info>
        : dispatch<slice_,tag::fusion_(memory::global_padding),Info>
  {};

  template<class Info>
  struct  call< slice_,tag::fusion_(memory::lead_padding)
              , boost::mpl::pair<boost::mpl::true_,boost::mpl::true_>
              , Info
              >
        : callable
  {
    template<class Sig> struct result;

    template<class This,class Seq,class Padder,class N>
    struct  result<This(Seq const&,Padder const&,N const&)>
    {
      static Seq const& s;
      BOOST_TYPEOF_NESTED_TYPEDEF_TPL
      ( nested
      , memory::align_on( boost::fusion::at_c<0>(s) )
      );
      typedef typename nested::type type;
    };

    NT2_FUNCTOR_CALL(3)
    {
      return memory::align_on(boost::fusion::at_c<0>(a0));
    }
  };

  template<class Info>
  struct  call< slice_,tag::fusion_(memory::lead_padding)
              , boost::mpl::pair<boost::mpl::true_,boost::mpl::false_>
              , Info
              >
        : callable
  {
    template<class Sig> struct result;

    template<class This,class Seq,class Padder,class N>
    struct  result<This(Seq const&,Padder const&,N const&)>
            : boost::fusion::result_of::at_c<Seq const,N::value-1>
    {};

    NT2_FUNCTOR_CALL(3)
    {
      return boost::fusion::at_c<A2::value-1>(a0);
    }
  };

  template<class Info>
  struct  call< slice_,tag::fusion_(memory::lead_padding)
              , boost::mpl::pair<boost::mpl::false_,boost::mpl::true_>
              , Info
              >
        : callable
  {
    template<class Sig> struct result;

    template<class This,class Seq,class Padder,class N>
    struct  result<This(Seq const&,Padder const&,N const&)>
    {
      static Seq const& s;
      static details::times callee;
      BOOST_TYPEOF_NESTED_TYPEDEF_TPL
      ( nested
      , callee( memory::align_on( boost::fusion::at_c<0>(s) )
              , slice<2>(s,memory::lead_padding())
              )
      );
      typedef typename nested::type type;
    };

    NT2_FUNCTOR_CALL(3)
    {
      details::times callee;
      return callee ( memory::align_on( boost::fusion::at_c<0>(a0) )
                    , slice<2>(a0,memory::lead_padding())
                    );
    }
  };

  template<class Info>
  struct  call< slice_,tag::fusion_(memory::lead_padding)
              , boost::mpl::pair<boost::mpl::false_,boost::mpl::false_>
              , Info
              >
        : callable
  {
    template<class Sig> struct result;

    template<class This,class Seq,class Padder,class N>
    struct  result<This(Seq const&,Padder const&,N const&)>
    {
      static Seq const& s;
      static details::times callee;
      BOOST_TYPEOF_NESTED_TYPEDEF_TPL
      ( nested
      , callee( slice<N::value+1>(s,memory::lead_padding())
              , boost::fusion::at_c<N::value-1>(s)
              )
      );
      typedef typename nested::type type;
    };

    NT2_FUNCTOR_CALL(3)
    {
      details::times callee;
      return callee ( slice<A2::value+1>(a0,memory::lead_padding())
                    , boost::fusion::at_c<A2::value-1>(a0)
                    );
    }
  };
} }

////////////////////////////////////////////////////////////////////////////////
// stride Functor implementation
// Nothing special as the padding is after all the meaningful data
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace functors
{
  //////////////////////////////////////////////////////////////////////////////
  // For lead_padding stride, we care of the leading dimension
  //////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct dispatch<stride_,tag::fusion_(memory::lead_padding),Info>
  {
    template<class A0,class A1,class A2> struct apply
    {
      typedef boost::mpl::bool_<A2::value==1> type;
    };
  };

  template<class Info>
  struct  call<stride_,tag::fusion_(memory::lead_padding),boost::mpl::true_,Info>
        : callable
  {
    template<class Sig> struct result;

    template<class This,class Seq,class Padder, class N>
    struct  result<This(Seq const&,Padder const&,N const&)>
    {
      static Seq const& s;
      BOOST_TYPEOF_NESTED_TYPEDEF_TPL
      ( nested, memory::align_on( boost::fusion::at_c<0>(s) )  );

      typedef typename  nested::type type;
    };

    NT2_FUNCTOR_CALL(3)
    {
      return memory::align_on( boost::fusion::at_c<0>(a0) );
    }
  };

  template<class Info>
  struct  call<stride_,tag::fusion_(memory::lead_padding),boost::mpl::false_,Info>
        : callable
  {
    template<class Sig> struct result;

    template<class This,class Seq,class Padder, class N>
    struct  result<This(Seq const&,Padder const&,N const&)>
    {
      typedef typename
              boost::fusion::result_of::at_c<Seq const,N::value-1>::type  type;
    };

    NT2_FUNCTOR_CALL(3)
    {
      return boost::fusion::at_c<A2::value-1>(a0);
    }
  };
} }

#endif
