//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_META_LOOP_NEST_HPP_INCLUDED
#define NT2_CORE_CONTAINER_META_LOOP_NEST_HPP_INCLUDED

#include <boost/fusion/include/at.hpp>
#include <boost/fusion/include/size.hpp>
#include <boost/fusion/include/array.hpp>
#include <boost/fusion/include/io.hpp>
#include <boost/fusion/include/as_vector.hpp>

// Experimental OpenMP support
#if defined(_OPENMP)
#include <omp.h>
#endif

namespace nt2 { namespace meta
{
  //==============================================================================
  // Loop nest generator 
  // Main case : generate loops over the Nth dimensions set and forward to next
  // level as usual
  //==============================================================================
  template<std::size_t N,std::size_t MaxIter>
  struct for_each_impl
  {
    template<class Bases, class Sizes, class Position, class F>
    BOOST_DISPATCH_FORCE_INLINE
    static void call(Bases const& bases, Sizes const& sz, Position& pos, F const& f)
    {
      using boost::fusion::at_c;

      std::size_t bound = at_c<N-1>(bases) + at_c<N-1>(sz); 

      for ( at_c<N-1>(pos)  = at_c<N-1>(bases); 
            at_c<N-1>(pos) != bound; 
            ++at_c<N-1>(pos)
          )
        for_each_impl<N-1,MaxIter>::call(bases, sz, pos, f);
    }
  };
  
  //==============================================================================
  // Loop nest generator 
  // Outermost loop needs special care due to potential OpenMP support.
  // To satisfy less-than-stellar C++ compliance, the loop and the index support
  // are broken down to pieces then reconstructed under a classical for() loop
  //==============================================================================
  template<std::size_t N> struct for_each_impl<N,N>
  {
    template<class Bases, class Sizes, class Position, class F>
    BOOST_DISPATCH_FORCE_INLINE
    static void call(Bases const& bases, Sizes const& sz, Position& pos, F const& f)
    {
      using boost::fusion::at_c;

      std::size_t bound  = at_c<N-1>(sz); 
      std::size_t low    = at_c<N-1>(bases);

      #pragma omp for
      for(std::size_t i=0;i<bound;++i)
      {
        at_c<N-1>(pos) = i + low;
        for_each_impl<N-1,N>::call(bases, sz, pos, f);           
      }
    }
  };
  
  //==============================================================================
  // Loop nest generator 
  // Innermost loop finally calls our functor taking care of the expression
  // evaluation
  //==============================================================================
  // handle inner loop to call the actual functor
  template<std::size_t MaxIter> struct for_each_impl<1,MaxIter>
  {
    template<class Bases, class Sizes, class Position, class F>
    BOOST_DISPATCH_FORCE_INLINE
    static void call(Bases const& bases, Sizes const& sz, Position& pos, F const& f)
    {
      using boost::fusion::at_c;

      std::size_t bound = at_c<0>(bases) + at_c<0>(sz); 

      for ( at_c<0>(pos)  = at_c<0>(bases); 
            at_c<0>(pos) != bound; 
            ++at_c<0>(pos)
          )
      {
        f(pos);
      }
    }
  };
  
  //==============================================================================
  // Loop nest generator
  // Special scalar case, needed to remove ambiguity
  //==============================================================================
  template<> struct for_each_impl<1,1>
  {
    template<class Bases, class Sizes, class Position, class F>
    BOOST_DISPATCH_FORCE_INLINE
    static void call(Bases const& bases, Sizes const& sz, Position& pos, F const& f)
    {
      using boost::fusion::at_c;
      
      at_c<0>(pos) = at_c<0>(bases);
      f(pos);
    }
  };

  //============================================================================
  /*!
   * for_each generates a N dimensions loop nest from a dimensions set. This
   * loop nest will take care of calling a custom functor on every position of
   * the iteration space.
   */
  //============================================================================
  template<class Bases, class Sizes, class F>
  BOOST_DISPATCH_FORCE_INLINE
  void for_each(Bases const& bases, Sizes const& sz, F const& f)
  {
    static const std::size_t nb_dims = boost::fusion::result_of::size<Sizes>::value;

    #pragma omp parallel
    {
      boost::array<std::size_t, nb_dims> position;
      for_each_impl<nb_dims,nb_dims>::call(bases, sz, position, f);
    }
  }
} }

#endif
