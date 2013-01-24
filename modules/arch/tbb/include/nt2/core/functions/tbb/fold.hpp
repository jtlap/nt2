//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_TBB_FOLD_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_TBB_FOLD_HPP_INCLUDED
#if defined(NT2_USE_TBB)

#include <nt2/core/functions/fold.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/meta/is_vectorizable.hpp>
#include <nt2/include/functions/run.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <nt2/sdk/config/cache.hpp>
#include <nt2/sdk/tbb/tbb.hpp>

#ifndef BOOST_NO_EXCEPTIONS
#include <boost/exception_ptr.hpp>
#endif

#ifndef BOOST_SIMD_NO_SIMD
//==============================================================================
// tbb + SIMD
//==============================================================================
namespace nt2 {

  namespace details
  {
    // Create the correct functor for tbb::parallel reduce according to the
    // requested Site.
    template<class A1, class A3, class Target>
    struct apply_bop
    {
      typedef Target target_type;

      apply_bop(target_type const& n, A1 & in, A3 const& bop)
      : vec_out_(n), neutral_(n), in_(in), bop_(bop)
      {}

      apply_bop(apply_bop& src, tbb::split)
      : vec_out_(src.neutral_), neutral_(src.neutral_), in_(in_), bop_(src.bop_)
      {}

      void operator()(tbb::blocked_range<std::size_t> const& r) const
      {
        static const std::size_t N = boost::simd::meta::cardinal_of<target_type>::value;
        for(std::size_t i=r.begin(); i<r.end(); i+=N)
        {
          vec_out_ = bop_(vec_out_, nt2::run(in_, i, meta::as_<target_type>()));
        }
      }

      void join(apply_bop& rhs) { vec_out_ = bop_(vec_out_,rhs.vec_out_); }

      mutable target_type vec_out_;
      target_type         neutral_;
      A1&                      in_;
      A3                      bop_;
    };
  }

  namespace ext
  {
    //============================================================================
    // Generates fold
    //============================================================================
    NT2_FUNCTOR_IMPLEMENTATION_IF( nt2::tag::fold_, nt2::tag::tbb_<Site>
                                 , (A1)(A2)(A3)(A4)(Site)
                                 , (boost::simd::meta::is_vectorizable<typename boost::dispatch::meta::result_of<A4 const(typename A1::value_type)>::type, BOOST_SIMD_DEFAULT_EXTENSION>)
                                 , ((ast_< A1, nt2::container::domain>))
                                   (unspecified_<A2>)
                                   (unspecified_<A3>)
                                   (unspecified_<A4>)
                                 )
    {
      typedef typename A1::extent_type                                           extent_type;
      typedef typename A1::value_type                                            stype;
      typedef typename boost::dispatch::meta::result_of<A4 const(stype)>::type   result_type;
      typedef boost::simd::native<result_type,BOOST_SIMD_DEFAULT_EXTENSION>      target_type;



      BOOST_FORCEINLINE result_type operator()(A1& in, A2 const& neutral, A3 const& bop, A4 const& uop) const
      {
        extent_type ext = in.extent();
        std::size_t bound = boost::fusion::at_c<0>(ext);
        static const std::size_t N   = boost::simd::meta::cardinal_of<target_type>::value;
        std::ptrdiff_t aligned_bound = (boost::fusion::at_c<0>(ext)/N) * N;
        aligned_bound    -= aligned_bound%tbb::task_scheduler_init::default_num_threads();
        std::size_t grain = aligned_bound/tbb::task_scheduler_init::default_num_threads();

        result_type out = neutral(nt2::meta::as_<result_type>());
        details::apply_bop<A1,A3,target_type> abop(neutral(nt2::meta::as_<target_type>()),in,bop);

  #ifndef BOOST_NO_EXCEPTIONS
        boost::exception_ptr exception;
        try
        {
  #endif
          tbb::parallel_reduce( tbb::blocked_range<std::size_t>(0,aligned_bound,grain)
                              , abop
                              );

  #ifndef BOOST_NO_EXCEPTIONS
        }
        catch(...)
        {
          // Store exception for late rethrow
          exception = boost::current_exception();
        }
  #endif


  #ifndef BOOST_NO_EXCEPTIONS
        if(exception)
          boost::rethrow_exception(exception);
  #endif
        out = uop(abop.vec_out_);

        // Process the scalar epilogue
        for(std::size_t i = aligned_bound; i < bound; ++i)
          out = bop(out, nt2::run(in, i, meta::as_<result_type>()));

        return out;

      }
    };

} }

#else
//==============================================================================
// tbb + no SIMD
//==============================================================================

namespace nt2 { namespace ext
{
  //============================================================================
  // Generates fold
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::fold_, nt2::tag::tbb_<Site>
                            , (A1)(A2)(A3)(A4)(Site)
                            , ((ast_< A1, nt2::container::domain>))
                              (unspecified_<A2>)
                              (unspecified_<A3>)
                              (unspecified_<A4>)
                            )
  {
    typedef typename boost::remove_reference<A1>::type::extent_type            extent_type;
    typedef typename boost::remove_reference<A1>::type::value_type             stype;
    typedef typename boost::dispatch::meta::result_of<A4 const(stype)>::type   result_type;

    BOOST_FORCEINLINE result_type operator()(A1& in, A2 const& neutral, A3 const& bop, A4 const& uop) const
    {
      extent_type ext = in.extent();
        std::size_t bound = boost::fusion::at_c<0>(ext);
        std::size_t grain = bound/tbb::task_scheduler_init::default_num_threads();
        details::apply_bop<A1,A3,stype> abop(neutral(nt2::meta::as_<stype>()),in,bop);

  #ifndef BOOST_NO_EXCEPTIONS
        boost::exception_ptr exception;
        try
        {
  #endif
          tbb::parallel_reduce( tbb::blocked_range<std::size_t>(0,bound,grain)
                              , abop
                              );

  #ifndef BOOST_NO_EXCEPTIONS
        }
        catch(...)
        {
          // Store exception for late rethrow
          exception = boost::current_exception();
        }
  #endif


  #ifndef BOOST_NO_EXCEPTIONS
        if(exception)
          boost::rethrow_exception(exception);
  #endif
        return abop.vec_out_;
      }
  };

} }

#endif
#endif
#endif
