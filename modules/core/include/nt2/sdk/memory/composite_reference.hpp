//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_MEMORY_COMPOSITE_REFERENCE_HPP_INCLUDED
#define NT2_CORE_CONTAINER_MEMORY_COMPOSITE_REFERENCE_HPP_INCLUDED

#include <boost/fusion/include/for_each.hpp>
#include <boost/fusion/include/comparison.hpp>
#include <boost/fusion/include/transform_view.hpp>
#include <boost/dispatch/meta/hierarchy_of.hpp>

//==============================================================================
/**
  * \file
  * \brief Defines and implements the \c nt2::memory::composite_reference class
  **/
//==============================================================================

namespace nt2 { namespace memory
{
  // T = complex<float>
  template<class T>
  class composite_reference
      : public  boost::mpl::
                transform < typename  boost::fusion::result_of::
                                      as_vector<T>::type
                          , boost::mpl::if_
                            < boost::is_const<T>
                            , meta::const_reference_<boost::mpl::_>
                            , meta::reference_<boost::mpl::_>
                            >
                          >::type
  {
    public:
    typedef typename  boost::mpl::
            transform < typename boost::fusion::result_of::as_vector<T>::type
                      , boost::mpl::if_ < boost::is_const<T>
                                        , meta::const_reference_<boost::mpl::_>
                                        , meta::reference_<boost::mpl::_>
                                        >
                      >::type                 parent;

    composite_reference(T& src) : parent( src )     {}
    composite_reference(parent& src) : parent(src)  {}

    composite_reference& operator=(T& src)
    {
      static_cast<parent&>(*this) = static_cast<parent&>(src);
      return *this;
    }

    composite_reference& operator=(parent const& src)
    {
      return *this;
    }
  };

  template<class T>
  std::ostream& operator<<(std::ostream& os,composite_reference<T> const& cr)
  {
    return boost::fusion::out(os, cr);
  }
} }

namespace boost { namespace dispatch { namespace meta
{
  //============================================================================
  // container hierarchy is given by its semantic_
  //============================================================================
  template<class T, class Origin>
  struct  hierarchy_of< nt2::memory::composite_reference<T>, Origin >
        : hierarchy_of< T, Origin>
  {};
} } }

#endif
