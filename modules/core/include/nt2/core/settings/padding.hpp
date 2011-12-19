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

  template<  typename Strat, typename Value
           , typename Default = boost::mpl::int_<1> >
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
  /*! padding list of one argument return the padding strategy of 
   * the argument option with a default value
  **/
  //============================================================================
  template<class S0, class Default>
  struct  option< padding_(S0), tag::padding_, Default >
  {
    typedef padding_strategy_<S0, boost::mpl::int_<1> > type;
  };

  //============================================================================
  /*! global_padding_ option return padding_strategy of global 
   *  with a default value
  **/
  //============================================================================
  template<class Default>
  struct  option< global_padding_, tag::padding_, Default >
  {
    typedef padding_strategy_<global_, boost::mpl::int_<-1> > type;
  };

  //============================================================================
  /*! lead_padding_ option return padding_strategy of lead with a default value
  **/
  //============================================================================
  template<class Default>
  struct  option< lead_padding_, tag::padding_, Default >
  {
    typedef padding_strategy_<lead_, boost::mpl::int_<-1> > type;
  };

  //============================================================================
  /*! global_padding_ with alignment value 
   *  return padding_strategy of global_ with the alignment value
  **/
  //============================================================================
  template<class Default, std::ptrdiff_t N>
  struct  option< global_padding_(with_<N>), tag::padding_, Default >
  {
    typedef padding_strategy_<  global_
                              , boost::mpl::int_<-1>
                              , boost::mpl::int_<N> 
                              > type;
  };

  //============================================================================
  /*! lead_padding_ with alignment value 
   *  return padding_strategy of lead_ with the alignment value
  **/
  //============================================================================
  template<class Default, std::ptrdiff_t N>
  struct  option< lead_padding_(with_<N>), tag::padding_, Default >
  {
    typedef padding_strategy_<  lead_
                              , boost::mpl::int_<-1>
                              , boost::mpl::int_<N> 
                              > type;
  };

  //============================================================================
  /*! no_padding_ option 
   *  return padding_strategy of none_ with a default value
  **/
  //============================================================================
  template<class Default>
  struct  option< no_padding_, tag::padding_, Default >
  {
    typedef padding_strategy_<none_, boost::mpl::int_<1>  > type;
  };

  //============================================================================
  /*! padding_ option with alignement value
   *  return padding_strategy of lead_ with the alignement value
  **/
  //============================================================================
  template<std::ptrdiff_t N, class Default>
  struct  option< padding_(with_<N>), tag::padding_, Default >
  {
    typedef padding_strategy_<  lead_
                              , boost::mpl::int_<-1>
                              , boost::mpl::int_<N> 
                              > type;
  };

  //============================================================================
  /*! padding_ option with alignement value and padding type
   *  return padding_strategy of padding type with the alignement value
  **/
  //============================================================================
  template<class S0, std::ptrdiff_t N, class Default>
  struct  option< padding_(with_<N>, S0),tag::padding_, Default >
  {
    typedef padding_strategy_<  S0
                              , boost::mpl::int_<-1>
                              , boost::mpl::int_<N> 
                              > type;
  };

  //============================================================================
  /*! padding_ option with padding type and alignement value 
   *  return padding_strategy of padding type with the alignement value
  **/
  //============================================================================
  template<class S0, std::ptrdiff_t N, class Default>
  struct  option< padding_(S0, with_<N>), tag::padding_, Default >
  {
    typedef padding_strategy_<  S0
                              , boost::mpl::int_<-1>
                              , boost::mpl::int_<N> 
                              > type;
  };
} }

#endif
