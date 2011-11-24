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

  struct storage_order_;

  typedef storage_order_ matlab_storage_order_;

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
    template<class Default>
    struct option < storage_order_
                  , tag::storage_order_, Default
                  >
    {    
      typedef storage_order_  type;
    };
  }

}


#endif
