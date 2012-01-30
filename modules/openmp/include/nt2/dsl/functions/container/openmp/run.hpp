//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_DSL_FUNCTIONS_CONTAINER_OPENMP_RUN_HPP_INCLUDED
#define NT2_DSL_FUNCTIONS_CONTAINER_OPENMP_RUN_HPP_INCLUDED
#ifdef _OPENMP

#include <nt2/dsl/functions/run.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/sdk/meta/runner.hpp>
#include <nt2/sdk/openmp/openmp.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/fusion/include/value_at.hpp>
#include <boost/fusion/include/at.hpp>
#include <boost/fusion/include/size.hpp>
#include <boost/fusion/include/vector_tie.hpp>
#include <boost/mpl/int.hpp>
#include <cstddef>

namespace nt2 { namespace openmp
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

        std::ptrdiff_t obound = olow + nt2::numel(boost::fusion::pop_front(sz));

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

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_, nt2::tag::openmp_<Site>
                            , (A0)(S0)(Site)
                            , ((expr_< table_< unspecified_<A0>, S0 >
                                     , nt2::container::domain
                                     , nt2::tag::assign_
                                     >
                              ))
                            )
  {
    typedef typename boost::proto::result_of::
    child_c<A0 const&, 0>::type                             result_type;

    typedef typename meta::
            strip< typename meta::
                   scalar_of<result_type>::type
                 >::type                                    stype;

#if !defined(BOOST_SIMD_NO_SIMD)
    //==========================================================================
    // If some SIMD is detected, then return a native
    //==========================================================================
    typedef boost::simd::native<stype, BOOST_SIMD_DEFAULT_EXTENSION>
                                                            target_type;
#else
    //==========================================================================
    // If no SIMD is detected, stay in scalar mode
    //==========================================================================
    typedef stype                                           target_type;
#endif

    BOOST_FORCEINLINE result_type
    operator()(A0 const& a0) const
    {
      boost::proto::child_c<0>(a0).resize(a0.extent());

      //==========================================================================
      // Generate a loop nest of proper depth running the expression evaluator
      // as its body and using indices/extent as loop bounds
      //==========================================================================
      openmp::for_each( typename A0::index_type::type()
                      , nt2::extent(a0)
                      , typename boost::simd::meta::cardinal_of<target_type>::type()
                      , meta::runner<A0, stype>(a0)
                      );

      return boost::proto::child_c<0>(a0);
    }
  };

} }

#endif
#endif
