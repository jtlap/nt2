//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_SDK_MEMORY_COMPOSITE_REFERENCE_HPP_INCLUDED
#define NT2_CORE_SDK_MEMORY_COMPOSITE_REFERENCE_HPP_INCLUDED

#include <boost/mpl/transform.hpp>
#include <boost/fusion/include/io.hpp>
#include <boost/fusion/include/copy.hpp>
#include <boost/fusion/include/as_vector.hpp>
#include <boost/simd/sdk/functor/proxy.hpp>
#include <boost/dispatch/meta/value_of.hpp>
#include <boost/dispatch/meta/scalar_of.hpp>
#include <nt2/sdk/meta/container_traits.hpp>

//==============================================================================
/**
  * \file
  * \brief Defines and implements the \c nt2::memory::composite_reference class
  **/
//==============================================================================
namespace nt2 { namespace container
{
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
    typedef typename boost::remove_const<T>::type                   value_type;
    typedef typename  boost::mpl::
            transform < typename boost::fusion::result_of::as_vector<T>::type
                      , boost::mpl::if_ < boost::is_const<T>
                                        , meta::const_reference_<boost::mpl::_>
                                        , meta::reference_<boost::mpl::_>
                                        >
                      >::type                 parent;

    composite_reference(T& src) : parent( src )     {}
    composite_reference(parent& src) : parent(src)  {}

    template<class U>
    composite_reference ( U& src
                        , typename boost
                          ::enable_if< boost::is_convertible<U,parent> >::type* = 0
                        ) : parent( src )
    {}

    composite_reference& operator=(T const& src)
    {
      boost::fusion::copy(src,*this);
      return *this;
    }

    composite_reference& operator=(composite_reference const& src)
    {
      boost::fusion::copy(src,*this);
      return *this;
    }

    composite_reference& operator=(parent const& src)
    {
      boost::fusion::copy(src,*this);
      return *this;
    }

    operator value_type() const
    {
      value_type that;
      boost::fusion::copy(*this,that);
      return that;
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
  template<class T,class Origin>
  struct  hierarchy_of< nt2::container::composite_reference<T>
                      , Origin
                      >
  {
    typedef meta::proxy_<Origin>       type;
  };
} } }

namespace boost { namespace fusion { namespace traits
{
  template<typename T>
  struct  enable_equality < nt2::container::composite_reference<T>
                          , nt2::container::composite_reference<T>
                          >
        : mpl::false_
  {};

  template<typename T>
  struct  enable_equality < nt2::container::composite_reference<T>
                          , T
                          >
        : mpl::false_
  {};

  template<typename T>
  struct  enable_equality < T
                          , nt2::container::composite_reference<T>
                          >
        : mpl::false_
  {};

  template<typename T>
  struct  enable_comparison < nt2::container::composite_reference<T>
                            , nt2::container::composite_reference<T>
                            >
        : mpl::false_
  {};

  template<typename T>
  struct  enable_comparison < nt2::container::composite_reference<T>
                            , T
                            >
        : mpl::false_
  {};

  template<typename T>
  struct  enable_comparison < T
                            , nt2::container::composite_reference<T>
                            >
        : mpl::false_
  {};
} } }

#endif
