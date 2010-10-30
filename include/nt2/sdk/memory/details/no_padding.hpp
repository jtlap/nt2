//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_SDK_MEMORY_DETAILS_NO_PADDING_HPP_INCLUDED
#define NT2_SDK_MEMORY_DETAILS_NO_PADDING_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Padding strategies for memory allocation
////////////////////////////////////////////////////////////////////////////////
#include <boost/mpl/pair.hpp>
#include <boost/typeof/typeof.hpp>
#include <nt2/sdk/memory/slice.hpp>
#include <nt2/sdk/memory/stride.hpp>
#include <boost/fusion/include/at.hpp>
#include <boost/fusion/include/size.hpp>
#include <nt2/sdk/memory/details/times.hpp>
#include <nt2/sdk/functor/preprocessor/call.hpp>

////////////////////////////////////////////////////////////////////////////////
// slice Functor implementation
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace functors
{
  //////////////////////////////////////////////////////////////////////////////
  // For no_padding stride, we dispatch on the fact the Level is the last one
  //////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct dispatch<slice_,tag::fusion_(memory::no_padding),Info>
  {
    template<class A0,class A1,class A2> struct apply
    {
      typedef boost::mpl::bool_ <   A2::value
                                ==  boost::fusion::result_of::size<A0>::value
                                >                     type;
    };
  };

  template<class Info>
  struct  call<slice_,tag::fusion_(memory::no_padding),boost::mpl::true_,Info>
        : callable
  {
    template<class Sig> struct result;

    template<class This,class A0, class A1, class A2>
    struct  result<This(A0,A1,A2)>
          : boost::fusion::result_of::at_c< typename meta::strip<A0>::type const
                                          , meta::strip<A2>::type::value-1>
    {};

    NT2_FUNCTOR_CALL(3)
    {
      return boost::fusion::at_c<A2::value-1>(a0);
    }
  };

  template<class Info>
  struct  call<slice_,tag::fusion_(memory::no_padding),boost::mpl::false_,Info>
        : callable
  {
    template<class Sig> struct result;

    template<class This,class A0, class A1, class A2>
    struct  result<This(A0,A1,A2)>
    {
      static typename meta::strip<A0>::type const&  s;
      static typename meta::strip<A1>::type const&  p;
      static details::times callee;

      BOOST_TYPEOF_NESTED_TYPEDEF_TPL
      ( nested
      , callee( slice<meta::strip<A2>::type::value+1>(s,p)
              , boost::fusion::at_c<meta::strip<A2>::type::value-1>(s)
              )
      );

      typedef typename nested::type type;
    };

    NT2_FUNCTOR_CALL(3)
    {
      details::times callee;
      return callee ( slice<A2::value+1>(a0,a1)
                    , boost::fusion::at_c<A2::value-1>(a0)
                    );
    }
  };
} }

////////////////////////////////////////////////////////////////////////////////
// stride Functor implementation
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace functors
{
  //////////////////////////////////////////////////////////////////////////////
  // For no_padding stride, we just don't care about the dispatching
  //////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct dispatch<stride_,tag::fusion_(memory::no_padding),Info>
  {
    template<class A0,class A1,class A2> struct apply
    {
      typedef fundamental_ type;
    };
  };

  template<class Hierarchy, class Info>
  struct call<stride_,tag::fusion_(memory::no_padding),Hierarchy,Info>
        : callable
  {
    template<class Sig> struct result;

    template<class This,class A0, class A1, class A2>
    struct  result<This(A0,A1,A2)>
          : boost::fusion::result_of::at_c< typename meta::strip<A0>::type const
                                          , meta::strip<A2>::type::value-1
                                          >
    {};

    NT2_FUNCTOR_CALL(3)
    {
      return boost::fusion::at_c<A2::value-1>(a0);
    }
  };
} }

#endif
