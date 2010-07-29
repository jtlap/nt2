/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_MEMORY_POINTER_HPP_INCLUDED
#define NT2_SDK_MEMORY_POINTER_HPP_INCLUDED

#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <nt2/sdk/errors/assert.hpp>
#include <boost/utility/enable_if.hpp>
#include <nt2/sdk/config/bootstrap.hpp>
#include <nt2/sdk/memory/is_aligned.hpp>
#include <boost/type_traits/is_void.hpp>
#include <nt2/sdk/errors/static_assert.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/type_traits/is_convertible.hpp>

namespace nt2 {  namespace memory
{
  template<class T> struct pointer_
  {
    typedef pointer_<T> this_type;
    typedef T           element_type;
    typedef T*          pointer;

    typedef typename boost::mpl::eval_if_c< boost::is_void<T>::value
                                          , boost::mpl::identity<void>
                                          , boost::add_reference<T>
                                          >::type      reference;

    typedef typename boost::mpl::eval_if_c< boost::is_void<T>::value
                                          , boost::mpl::identity<void>
                                          , boost::add_reference<T const>
                                          >::type      const_reference;

    public:
    ////////////////////////////////////////////////////////////////////////////
    // Trivial constructor
    ////////////////////////////////////////////////////////////////////////////
    pointer_() : px(0) {}

    ////////////////////////////////////////////////////////////////////////////
    // Copy constructor
    ////////////////////////////////////////////////////////////////////////////
    template<class U>
    pointer_( pointer_<U> const& src
            , typename boost::enable_if_c <
                                          boost::is_convertible<U*,T*>::value
                                          >::type* = 0
               )
    : px(src.get()) {}

    pointer_( pointer_<void> const& src ) : px(static_cast<T*>(src.get())) {}

    ////////////////////////////////////////////////////////////////////////////
    // Explicit constructor from raw pointer
    ////////////////////////////////////////////////////////////////////////////
    template<class U> explicit
    pointer_( U* src
            , typename boost::enable_if_c <
                                          boost::is_convertible<U*,T*>::value
                                          >::type* = 0
            )
    {
      NT2_ASSERT(   is_aligned(src)
                &&  "pointer_ built from invalid raw pointer"
                );
      px = src;
    }

    explicit pointer_( void* src )
    {
      NT2_ASSERT(   is_aligned(src)
                &&  "pointer_ built from invalid raw pointer"
                );
      px = reinterpret_cast<T*>(src);
    }

    ////////////////////////////////////////////////////////////////////////////
    // Access to the pointee data with array-like syntax
    ////////////////////////////////////////////////////////////////////////////
    reference       operator[](int i)
    {
      NT2_STATIC_ASSERT ( (!boost::is_void<T>::value)
                        , DEREFENCING_VOID_POINTER
                        , (T)
                        );
      return px[i];
    }

    const_reference operator[](int i) const
    {
      NT2_STATIC_ASSERT ( (!boost::is_void<T>::value)
                        , DEREFENCING_VOID_POINTER
                        , (T)
                        );
      return px[i];
    }

    ////////////////////////////////////////////////////////////////////////////
    // Access to the pointee
    ////////////////////////////////////////////////////////////////////////////
    reference operator*  () const
    {
      NT2_STATIC_ASSERT ( (!boost::is_void<T>::value)
                        , DEREFENCING_VOID_POINTER
                        , (T)
                        );
      return *px;
    }

    ////////////////////////////////////////////////////////////////////////////
    // Shortcut for pointee members access
    ////////////////////////////////////////////////////////////////////////////
    pointer   operator-> () const
    {
      NT2_STATIC_ASSERT ( (!boost::is_void<T>::value)
                        , DEREFENCING_VOID_POINTER
                        , (T)
                        );
      return  px;
    }

    ////////////////////////////////////////////////////////////////////////////
    // Access to the raw address
    ////////////////////////////////////////////////////////////////////////////
    pointer   get()         const { return  px; }

    ////////////////////////////////////////////////////////////////////////////
    // Shamelessly reuse Boost::shared_ptr operator_bool file
    ////////////////////////////////////////////////////////////////////////////
    #include <boost/smart_ptr/detail/operator_bool.hpp>

    ////////////////////////////////////////////////////////////////////////////
    // When working with another pointer_<U>, everything is straightforward and
    // exception-safe as we statically know that everythign is right if T* and
    // U* are compatible
    ////////////////////////////////////////////////////////////////////////////
    template<class U>
    typename boost::enable_if_c< boost::is_convertible<U*,T*>::value >::type
    reset( pointer_<U> const& src )
    {
      px = src.px;
    }

    template<class U>
    typename boost::enable_if_c< boost::is_convertible<U*,T*>::value >::type
    swap( pointer_<U>& src )
    {
      std::swap(px,src.px);
    }

    template<class U>
    typename boost::enable_if_c < boost::is_convertible<U*,T*>::value
                                , pointer_&
                                >::type
    operator=( pointer_<U> const& src )
    {
      px = src.px;
      return *this;
    }

    ////////////////////////////////////////////////////////////////////////////
    // reset from a free pointer - the pointer must match current alignment
    ////////////////////////////////////////////////////////////////////////////
    template<class U>
    typename boost::enable_if_c< boost::is_convertible<U*,T*>::value >::type
    reset( U* src )
    {
      NT2_ASSERT(   is_aligned(src)
                &&  "pointer_ reset with invalid raw pointer"
                );
      px = src;
    }

    void reset( void* src )
    {
      NT2_ASSERT(   is_aligned(src)
                &&  "pointer_ reset with invalid raw pointer"
                );
      px = reinterpret_cast<T*>(src);
    }

    ////////////////////////////////////////////////////////////////////////////
    // pointee data
    ////////////////////////////////////////////////////////////////////////////
    private:
    pointer  px;
  };
} }

#endif
