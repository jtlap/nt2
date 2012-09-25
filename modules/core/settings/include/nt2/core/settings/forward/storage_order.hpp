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

#include <boost/mpl/size_t.hpp>

namespace nt2
{
  //============================================================================
  /**!
   * Specify the SO meta-function as the current container storage order
   * permutation.
  **/
  //============================================================================
  template <class SO> struct storage_order_ : SO {};

  namespace details
  {
    namespace adl_barrier
    {
      struct matlab_storage_
      {
        template<class S, class D> struct apply : D {};
      };

      struct C_storage_
      {
        template<class S, class D>
        struct apply : boost::mpl::size_t<S::value - 1 - D::value> {};
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
  typedef storage_order_<details::matlab_storage_>  column_major_;

  //==========================================================================
  /**!
   * Predefined settings for C style (row major) storage order.
   **/
  //==========================================================================
  typedef storage_order_<details::C_storage_>       C_order_;
  typedef storage_order_<details::C_storage_>       row_major_;

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
