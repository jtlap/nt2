/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_MEMORY_DETAILS_GLOBAL_PADDING_HPP_INCLUDED
#define NT2_SDK_MEMORY_DETAILS_GLOBAL_PADDING_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Padding strategies for memory allocation
////////////////////////////////////////////////////////////////////////////////
#include <boost/mpl/pair.hpp>
#include <boost/typeof/typeof.hpp>
#include <nt2/sdk/memory/slice.hpp>
#include <nt2/sdk/memory/stride.hpp>
#include <nt2/sdk/memory/align_on.hpp>
#include <boost/fusion/include/at.hpp>
#include <boost/fusion/include/size.hpp>
#include <nt2/sdk/memory/details/times.hpp>
#include <boost/fusion/include/value_at.hpp>
#include <nt2/sdk/functor/preprocessor/call.hpp>
#include <nt2/sdk/memory/details/no_padding.hpp>

////////////////////////////////////////////////////////////////////////////////
// slice Functor implementation
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace functors
{
  //////////////////////////////////////////////////////////////////////////////
  // For global_padding slice, dispacth on the relative positino of the Level
  //////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct dispatch<slice_,tag::fusion_(memory::global_padding),Info>
  {
    template<class A0,class A1,class A2> struct apply
    {
      typedef boost::mpl
            ::pair< boost::mpl::bool_ <   A2::value
                                      ==  boost::fusion::result_of
                                          ::size<A0>::value
                                      >
                  , boost::mpl::bool_ <A2::value == 1>
                  >
                                                                    type;
    };
  };

  template<class Info>
  struct  call< slice_,tag::fusion_(memory::global_padding)
              , boost::mpl::pair<boost::mpl::true_,boost::mpl::true_>
              , Info
              >
        : callable
  {
    template<class Sig> struct result;

    template<class This,class A0, class A1, class A2>
    struct  result<This(A0,A1,A2)>
    {
      static typename meta::strip<A0>::type const& s;
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
  struct  call< slice_,tag::fusion_(memory::global_padding)
              , boost::mpl::pair<boost::mpl::true_,boost::mpl::false_>
              , Info
              >
        : callable
  {
    template<class Sig> struct result;

    template<class This,class A0, class A1, class A2>
    struct  result<This(A0,A1,A2)>
            : boost::fusion::result_of::at_c<typename meta::strip<A0>::type const
                                            , meta::strip<A2>::type::value-1
                                            >
    {};

    NT2_FUNCTOR_CALL(3)
    {
      return boost::fusion::at_c<A2::value-1>(a0);
    }
  };

  template<class Info>
  struct  call< slice_,tag::fusion_(memory::global_padding)
              , boost::mpl::pair<boost::mpl::false_,boost::mpl::true_>
              , Info
              >
        : callable
  {
    template<class Sig> struct result;

    template<class This,class A0, class A1, class A2>
    struct  result<This(A0,A1,A2)>
    {
      static typename meta::strip<A0>::type const& s;
      BOOST_TYPEOF_NESTED_TYPEDEF_TPL
      ( nested
      , memory::align_on( slice<1>(s,memory::no_padding()) )
      );
      typedef typename nested::type type;
    };

    NT2_FUNCTOR_CALL(3)
    {
      return memory::align_on( slice<1>(a0,memory::no_padding()) );
    }
  };

  template<class Info>
  struct  call< slice_,tag::fusion_(memory::global_padding)
              , boost::mpl::pair<boost::mpl::false_,boost::mpl::false_>
              , Info
              >
        : callable
  {
    template<class Sig> struct result;

    template<class This,class A0, class A1, class A2>
    struct  result<This(A0,A1,A2)>
    {
      static typename meta::strip<A0>::type const& s;
      BOOST_TYPEOF_NESTED_TYPEDEF_TPL
      ( nested
      , slice<meta::strip<A2>::type::value>(s,memory::no_padding())
      );
      typedef typename nested::type type;
    };

    NT2_FUNCTOR_CALL(3)
    {
      return slice<A2::value>(a0,memory::no_padding());
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
  // For global_padding stride, we just don't care about the dispatching
  //////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct dispatch<stride_,tag::fusion_(memory::global_padding),Info>
  {
    template<class A0,class A1,class A2> struct apply
    {
      typedef fundamental_ type;
    };
  };

  template<class Hierarchy, class Info>
  struct  call<stride_,tag::fusion_(memory::global_padding),Hierarchy,Info>
        : call<stride_,tag::fusion_(memory::no_padding),Hierarchy,Info>
  {};
} }

#endif
