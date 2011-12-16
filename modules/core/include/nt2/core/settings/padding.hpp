//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_SETTINGS_PADDING_HPP_INCLUDED
#define NT2_CORE_SETTINGS_PADDING_HPP_INCLUDED

#include <boost/mpl/int.hpp>
#include <nt2/core/settings/option.hpp>
#include <nt2/core/settings/misc.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/simd/sdk/memory/parameters.hpp>

namespace nt2 
{ 

  template<typename Strat, typename Value>
  struct padding_strategy_ {};

  //===========================================================================
  /*! 
   * Composite settings for container memory padding strategies.
   **/
  //============================================================================
  struct padding_ {};

  //============================================================================
  /*! Specify that current container doesn't pad its memory. 
   *  Equivalent to padding_(none_).
   **/
  //============================================================================
  struct no_padding_ {};

  //============================================================================
  /*! Specify a global padding strategy will be used. 
   *  Equivalent to padding_(global_). 
   *  The padding value will have to be specified at runtime using 
   *  the appropriate container constructor.
   **/
  //============================================================================
  struct global_padding_{};

  //============================================================================
  /*! Specify a lead dimension padding strategy will be used. 
   *  Equivalent to padding_(lead_). 
   *  The padding value will have to be specified at runtime using 
   *  the appropriate container constructor.
   **/
  //============================================================================
  struct lead_padding_{};

  //============================================================================
  /*! Specify a global padding strategy will be used. 
   *  The padding value can either be specified at runtime 
   *  (see nt2::global_padding_) or using nt2::with_
   **/
  //============================================================================
  struct global_{};

  //============================================================================
  /*! Specify a lead dimension padding strategy will be used. 
   *  The padding value can either be specified at runtime 
   *  (see nt2::lead_padding_) or using nt2::with_
   **/
  //============================================================================
  struct lead_{};


  namespace tag 
  { 
    //==========================================================================
    /*!
     * Option tag for padding options
     **/
    //==========================================================================
    struct padding_ {}; 
  }


}

namespace nt2 { namespace meta
{
  //============================================================================
  // padding list of one argument return the argument option value
  //============================================================================
  template<class S0, class Default>
  struct  option< padding_(S0), tag::padding_, Default >
  {
    typedef padding_strategy_<S0, boost::mpl::int_<-1> > type;
  };

  //============================================================================
  // padding list of one argument return the argument option value
  //============================================================================
  template<class Default>
  struct  option< global_padding_, tag::padding_, Default >
  {
    typedef padding_strategy_<global_, boost::mpl::int_<-1> > type;
  };

  //============================================================================
  // padding list of one argument return the argument option value
  //============================================================================
  template<class Default>
  struct  option< lead_padding_, tag::padding_, Default >
  {
    typedef padding_strategy_<lead_, boost::mpl::int_<-1> > type;
  };



  //============================================================================
  // padding list of one argument return the argument option value
  //============================================================================
  template<class Default, std::ptrdiff_t N>
  struct  option< global_padding_(with_<N>), tag::padding_, Default >
  {
    typedef padding_strategy_<global_, boost::mpl::int_<-1> > type;
  };

  //============================================================================
  // padding list of one argument return the argument option value
  //============================================================================
  template<class Default, std::ptrdiff_t N>
  struct  option< lead_padding_(with_<N>), tag::padding_, Default >
  {
    typedef padding_strategy_<lead_, boost::mpl::int_<N> > type;
  };


  template<class Default>
  struct  option< no_padding_, tag::padding_, Default >
  {
    typedef padding_strategy_<none_, boost::mpl::int_<-1> > type;
  };

  template<std::ptrdiff_t N, class Default>
  struct  option< padding_(with_<N>), tag::padding_, Default >
  {
    typedef padding_strategy_<lead_, boost::mpl::int_<N> > type;
  };


  template<class S0, std::ptrdiff_t N, class Default>
  struct  option< padding_(with_<N>, S0),tag::padding_, Default >
  {
    typedef padding_strategy_<S0, boost::mpl::int_<N> > type;
  };

  template<class S0, std::ptrdiff_t N, class Default>
  struct  option< padding_(S0, with_<N>), tag::padding_, Default >
  {
    typedef padding_strategy_<S0, boost::mpl::int_<N> > type;
  };
} }

#endif
