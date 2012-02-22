//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_SETTINGS_FORWARD_STORAGE_ORDER_HPP_INCLUDED
#define NT2_CORE_SETTINGS_FORWARD_STORAGE_ORDER_HPP_INCLUDED

#include <boost/mpl/apply.hpp>

namespace nt2 
{ 

  //============================================================================
   /*! Specify the SO meta-function as the current container storage order 
    *  permutation.
   **/
  //============================================================================

  template <class SO>
  struct storage_order_
  {
    template <typename S, typename D>
    struct apply : boost::mpl::apply<SO,S,D> 
    {};
  };

  namespace details
  {
    namespace adl_barrier
    {
      struct matlab_storage_
      {
        template <typename S, typename D>
        struct apply : boost::mpl::int_<S::value - 1 - D::value>  {};
      };
    
      struct C_storage_
      {
        template <typename S, typename D>
        struct apply : D  {};
      };
    }

   using adl_barrier::matlab_storage_;
   using adl_barrier::C_storage_;
  }

  //==========================================================================
  /*! Predefined settings for Matlab style (column major) storage order.
  **/
  //==========================================================================
  typedef storage_order_<details::matlab_storage_>  matlab_order_;
  typedef storage_order_<details::matlab_storage_>  fortran_order_;

  //==========================================================================
  /*! Predefined settings for C style (row major) storage order.
  **/
  //==========================================================================
  typedef storage_order_<details::C_storage_>       C_order_;



  namespace tag
  {
    //==========================================================================
    /*!
     * Option tag for the storage order options
     **/
    //==========================================================================
    struct storage_order_ {};
  }



}


#endif
