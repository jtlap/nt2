//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_META_LOOP_NEST_HPP_INCLUDED
#define NT2_SDK_META_LOOP_NEST_HPP_INCLUDED

#include <boost/mpl/int.hpp>
#include <nt2/sdk/meta/view_at.hpp>
#include <boost/fusion/include/at.hpp>
#include <boost/fusion/include/size.hpp>
#include <boost/fusion/include/fold.hpp>
#include <boost/fusion/include/value_at.hpp>
#include <boost/fusion/include/pop_front.hpp>
#include <boost/fusion/include/vector_tie.hpp>
#include <nt2/include/functions/multiplies.hpp>

// TODO: Move to modules/openmp
#if defined(_OPENMP)
#include <omp.h>
#endif

namespace nt2 { namespace meta
{
  //============================================================================
  // Loop nest generator
  // Handle unaligned bits if needed, OpenMP the outermost loop
  //============================================================================
  template<std::size_t N> struct for_each_impl
  {
    template<class Bases, class Sizes, class Step, class F>
    static BOOST_DISPATCH_FORCE_INLINE
    void call(Bases const& bs, Sizes const& sz, Step const& s, F const& f)
    {
      typedef typename boost::fusion::result_of::
              value_at<Sizes,boost::mpl::int_<0> >::type value_type;

      #pragma omp parallel
      {
        std::ptrdiff_t ilow   = boost::fusion::at_c<0>(bs);
        std::ptrdiff_t olow   = boost::fusion::at_c<1>(bs);
        std::ptrdiff_t bound  = boost::fusion::at_c<0>(sz) + ilow;
        std::ptrdiff_t ibound = ilow
                              + (boost::fusion::at_c<0>(sz)/Step::value)
                              * Step::value;

        std::ptrdiff_t obound = olow
                              + boost::fusion::fold
                                ( boost::fusion::pop_front(sz)
                                , value_type(1)
                                , functor<tag::multiplies_>()
                                );

        #pragma omp for
        for(std::ptrdiff_t j=olow;j < obound;++j)
        {
          for(std::ptrdiff_t i=ilow;i < ibound;i += s)
          {
            f( boost::fusion::vector_tie(i,j), s);
          }

          for(std::ptrdiff_t i=ibound;i < bound;++i)
          {
            f( boost::fusion::vector_tie(i,j), boost::mpl::int_<1>());
          }
        }
      }
    }
  };

  //============================================================================
  // 1D Loop nest generator
  // Handle unaligned bits if needed, OpenMP the largest part
  //============================================================================
  template<> struct for_each_impl<1>
  {
    template<class Bases, class Sizes, class Step, class F>
    static BOOST_DISPATCH_FORCE_INLINE
    void call(Bases const& bs, Sizes const& sz, Step const& s, F const& f)
    {
      std::ptrdiff_t low   = boost::fusion::at_c<0>(bs);
      std::ptrdiff_t bound = boost::fusion::at_c<0>(sz) + low;
      std::ptrdiff_t aligned_bound  = low
                                    + (boost::fusion::at_c<0>(sz)/Step::value)
                                    * Step::value;

      #pragma omp parallel for
      for(std::ptrdiff_t i=low;i < aligned_bound;i += s)
      {
        f( boost::fusion::vector_tie(i), s);
      }

      for(std::ptrdiff_t i=aligned_bound;i < bound;++i)
      {
        f( boost::fusion::vector_tie(i), boost::mpl::int_<1>());
      }
    }
  };

  //==============================================================================
  // Loop nest generator - Special scalar case
  //==============================================================================
  template<> struct for_each_impl<0>
  {
    template<class Bases, class Sizes, class Step, class F>
    static BOOST_DISPATCH_FORCE_INLINE
    void call(Bases const& bs, Sizes const&, Step const&, F const& f)
    {
      f( meta::view_at<0>(bs), boost::mpl::int_<1>() );
    }
  };

  //============================================================================
  /*!
   * for_each generates a loop nest from a dimensions set. This
   * loop nest will take care of calling a custom functor on every position of
   * the iteration space.
   */
  //============================================================================
  template<class Bases, class Sizes, class Step, class F>
  BOOST_DISPATCH_FORCE_INLINE
  void for_each(Bases const& bases, Sizes const& sz, Step const & st, F const& f)
  {
    for_each_impl<boost::fusion::result_of::size<Sizes>::value>
                 ::call(bases, sz, st, f);
  }
} }

#endif
