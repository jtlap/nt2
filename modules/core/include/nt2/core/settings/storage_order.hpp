//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_SETTINGS_STORAGE_ORDER_HPP_INCLUDED
#define NT2_CORE_SETTINGS_STORAGE_ORDER_HPP_INCLUDED

#include <nt2/core/settings/option.hpp>

namespace nt2 
{ 


  template <class SO, class S, class D>
    struct storage_order_: SO::template apply<S, D> {};


  struct matlab_so_
  {
    template <typename S, typename D>
    struct apply : boost::mpl::int_<S::value - 1 - D::value>  {};
  };

  struct c_so_
  {
    template <typename S, typename D>
    struct apply : D  {};
  };


  namespace tag
  {
    //==========================================================================
    /*!
     * Option tag for the storage order options
     **/
    //==========================================================================
    struct storage_order_ {};
  }

  namespace meta
  {
    template<class SO, class S, class D, class Default>
    struct option < storage_order_<SO,S,D>
                  , tag::storage_order_, Default
                  >
    {    
       typedef storage_order_<SO,S,D>  type;
    };
  }

}


#endif
