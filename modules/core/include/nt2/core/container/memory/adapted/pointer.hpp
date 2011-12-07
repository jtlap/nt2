//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_MEMORY_ADAPTED_POINTER_HPP_INCLUDED
#define NT2_CORE_CONTAINER_MEMORY_ADAPTED_POINTER_HPP_INCLUDED

#include <boost/mpl/apply.hpp>
#include <nt2/sdk/meta/remove_pointers.hpp>
#include <boost/type_traits/add_pointer.hpp>
#include <boost/dispatch/meta/model_of.hpp>
#include <nt2/core/container/meta/dereference.hpp>
#include <nt2/core/settings/sharing.hpp>
#include <nt2/core/container/meta/dimensions_of.hpp>
#include <boost/simd/sdk/memory/details/category.hpp>
#include <nt2/core/container/memory/buffer_adaptor.hpp>

//==============================================================================
// Fill out the Buffer concepts for boost::array
//==============================================================================
namespace nt2 { namespace meta
{


  // //============================================================================
  // // reference_ specialization
  // //============================================================================
  // template<typename T, std::size_t Level>
  // struct dereference_<T*&,Level>
  // {
  //   typedef typename meta::remove_pointers<T*,Level>::type& type;
  // };

  // template<typename T, std::size_t Level>
  // struct dereference_<T* const&,Level>
  // {
  //   typedef typename meta::remove_pointers<T*,Level>::type const& type;
  // };

  // template<typename T, std::size_t Level>
  // struct dereference_<T*,Level>
  // {
  //   typedef typename meta::remove_pointers<T*,Level>::type type;
  // };
} }

namespace boost { namespace dispatch { namespace meta
{

  //============================================================================
  // model_of specialization
  //============================================================================
  // template<typename T>
  // struct model_of< T* >
  // {
  //   struct type
  //   {
  //     template<class X> struct apply
  //     {
  //       typedef typename  boost::mpl::
  //                         apply<typename model_of<T>::type,X>::type base;
  //       typedef typename boost::add_pointer<base>::type             type;
  //     };
  //   };
  // };


  template<  class Type,
             class Sizes ,
             class Bases ,
             class Padding ,
             class Shared
          >
  struct model_of< nt2::memory::buffer_adaptor<Type*, Sizes, Bases, Padding, Shared> > 
  {
    struct type
    {
      template<class X> struct apply
      {
        typedef typename  boost::mpl::
                          apply<typename model_of<Type>::type,X>::type base;
        typedef typename boost::add_pointer<base>::type             type;
      };
    };
  };


} } }

namespace nt2 { namespace memory
{
  //============================================================================
  // T* initialize - Part of Buffer Concept
  //============================================================================
  // template<typename T, typename Sizes, typename Bases, typename Padding>
  // inline void initialize( T*& , Sizes const&, Bases const&, Padding const& ) {}
  // template<typename T, typename Sizes, typename Bases, typename Padding>
  // inline void resize( T*&, Sizes const&, Padding const& ) {}

  // template<typename T, typename Sizes, typename Bases, typename Padding>
  // inline void rebase( T*& p, Bases const& b) {
  //   //TODO: Check if size of b ==1 
  //   return p - boost::fusion::at_c<0>(b);
  // }

  // template<typename T, typename Sizes, typename Bases, typename Padding>
  // inline void restructure( T*& p, Sizes const& s, Bases const& b, Padding const& pad) {
  //   resize(p,s,pad);
  //   rebase(p,b);
  // }



  template< typename Type
            , typename Sizes, typename Bases, typename Padding, typename Shared
            >
  inline void resize( nt2::memory::buffer_adaptor<Type*, Sizes, Bases, Padding, Shared>& b
                      , Sizes const& s
                      )
  {
    b.resize(boost::fusion::at_c<0>(s));
  }



  template< typename Type
            , typename Sizes, typename Bases, typename Padding, typename Shared
            >
  inline void rebase( nt2::memory::buffer_adaptor<Type*, Sizes, Bases, Padding, Shared>& b 
                      , Bases const& bs
                      )
  {
    b.rebase(bs);
  }


  template< typename Type
            , typename Sizes, typename Bases, typename Padding, typename Shared
            >
  inline void restructure( nt2::memory::buffer_adaptor<Type*, Sizes, Bases, Padding, Shared>& b
                           , Sizes const& sz, Bases const& bs
                           )
  {
    b.restructure(bs,sz);
  }


  template<  class Type, 
             class Sizes ,
             class Bases ,
             class Padding 
          >
  class buffer_adaptor<Type*,Sizes, Bases, Padding, owned_>
  {
    public:

    ////////////////////////////////////////////////////////////////////////////
    // Forwarded types
    ////////////////////////////////////////////////////////////////////////////
    typedef Type            value_type;
    typedef Type*           pointer;
    typedef const Type*     const_pointer;
    typedef Type*           iterator;
    typedef const Type*     const_iterator;
    typedef Type&           reference;
    typedef const Type&     const_reference;
    typedef std::size_t     size_type;
    typedef std::ptrdiff_t  difference_type;
    typedef std::ptrdiff_t  index_type;

    ////////////////////////////////////////////////////////////////////////////
    // Constructor & destructor
    ////////////////////////////////////////////////////////////////////////////

    buffer_adaptor() {}

    template<class Base, class Size>
    buffer_adaptor(   Base const& bs
                    , Size const& sz
                    , Type* const& b
                    ) 
    {
      buffer_ = b;
      rebase(bs);
    }


    ~buffer_adaptor() {}

    ////////////////////////////////////////////////////////////////////////////
    // Assignment operator - SG version
    ////////////////////////////////////////////////////////////////////////////
    // buffer_adaptor& operator=(buffer_adaptor const& src)
    // {
    //   // we want to have a Strong Garantee and yet be performant
    //   // so we check if we need some resizing
    //   if(src.size() > this->size())
    //   {
    //     // If we do, use the SG copy+swap method
    //     buffer_adaptor that(src);
    //     swap(that);
    //   }
    //   else
    //   {
    //     // If not we just need to resize/rebase and copy which is SG here
    //     restructure(src.lower(),src.size());
    //     std::copy(src.begin(),src.end(),begin());
    //   }
    //   return *this;
    // }

    ////////////////////////////////////////////////////////////////////////////
    // Iterator related methods
    ////////////////////////////////////////////////////////////////////////////
    // using parent_data::begin;
    // using parent_data::end;
    // using parent_data::first;
    // using parent_data::last;

    ////////////////////////////////////////////////////////////////////////////
    // Forward size related methods
    ////////////////////////////////////////////////////////////////////////////
    // using parent_data::lower;
    // using parent_data::upper;
    // using parent_data::size;

    ////////////////////////////////////////////////////////////////////////////
    // RandomAccessContainer Interface
    ////////////////////////////////////////////////////////////////////////////

    template <typename Position>
    reference
    operator[](Position const& i)
    {
      return buffer_[i - bss_];
    }

    template <typename Position>
    const_reference
    operator[](Position const& i) const
    {
      return buffer_[i - bss_];
    }

    ////////////////////////////////////////////////////////////////////////////
    // Swapping
    ////////////////////////////////////////////////////////////////////////////
    // void swap( buffer_adaptor& src )
    // {
    //   parent_data::swap(src);
    //   boost::swap(allocator(),src.allocator());
    // }

    ////////////////////////////////////////////////////////////////////////////
    // resize/rebase/restructure buffer
    ////////////////////////////////////////////////////////////////////////////
    //    using parent_data::rebase;

    template<class Size>
    void resize(Size s) { 
      // parent_data::resize(boost::fusion::at_c<0>(s)); 
    }

    template<class Base>
    void rebase(Base b) { bss_ = boost::fusion::at_c<0>(b); }

    template<class Base,class Size>
    void restructure( Base const& b, Size const& s )
    {
      resize(s);
      rebase(b);
    }

    protected:
    ////////////////////////////////////////////////////////////////////////////
    // Allocator access
    ////////////////////////////////////////////////////////////////////////////
    //    using parent_data::allocator;
    difference_type bss_;
    Type* buffer_;
 
  };
} } 


#endif
