//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_FUNCTIONS_DETAILS_STORE_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_FUNCTIONS_DETAILS_STORE_HPP_INCLUDED

#include <boost/dispatch/functor/meta/make_functor.hpp>
#include <boost/dispatch/attributes.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/simd/memory/functions/extract.hpp>
#include <boost/fusion/include/at_c.hpp>

// Helper for store over a fusion sequence.
namespace boost { namespace simd { namespace details
{
  template<typename Call> struct storer;

  template<typename Tag, typename A0, typename A1, typename A2>
  struct storer<Tag(A0,A1,A2)>
  {
    storer( A0 const& a0_, A1 const& a1_, A2 a2_) : a0(a0_), a1(a1_), a2(a2_) {}

    template<int I> BOOST_FORCEINLINE void operator()() const
    {
      typename dispatch::make_functor<Tag,A0>::type callee;
      callee(fusion::at_c<I>(a0), fusion::at_c<I>(a1), a2);
    }

    A0 const& a0;
    A1 const& a1;
    A2 a2;

    private:
    storer& operator=(storer const&);
  };

  template<typename Tag, typename A0, typename A1>
  struct storer<Tag(A0,A1)>
  {
    storer( A0 const& a0_, A1 const& a1_) : a0(a0_), a1(a1_) {}

    template<int I> BOOST_FORCEINLINE void operator()() const
    {
      typename dispatch::make_functor<Tag,A0>::type callee;
      callee(fusion::at_c<I>(a0), fusion::at_c<I>(a1) );
    }

    A0 const& a0;
    A1 const& a1;

    private:
    storer& operator=(storer const&);
  };

  template<typename A0, typename A1, typename A2 = int> struct extractor
  {
    extractor (A0 const& a0_, A1 a1_, A2 a2_ = 0)
              : a0(a0_), a1(a1_), a2(a2_)
    {}

    template<int I> void operator()() const
    {
      A1 p = a1;
      typedef typename fusion::result_of::at_c<A0,I>::type type;
      for(std::size_t i=0;i<meta::cardinal_of<type>::value;++i)
        fusion::at_c<I>(*(p++ + a2)) = extract(fusion::at_c<I>(a0), i);
    }

    A0 const& a0;
    A1        a1;
    A2        a2;

    private:
    extractor& operator=(extractor const&);
  };
} } }

#endif
