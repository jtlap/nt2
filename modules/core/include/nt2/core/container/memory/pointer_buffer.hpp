//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_MEMORY_POINTER_BUFFER_HPP_INCLUDED
#define NT2_CORE_CONTAINER_MEMORY_POINTER_BUFFER_HPP_INCLUDED

#include <boost/mpl/apply.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/mpl/size.hpp>
#include <boost/fusion/include/at_c.hpp>
#include <nt2/sdk/meta/remove_pointers.hpp>
#include <boost/type_traits/add_pointer.hpp>
#include <boost/simd/sdk/memory/details/category.hpp>
#include <nt2/core/container/memory/adapted/pointer_buffer.hpp>


namespace nt2 { namespace memory
{

  template<class Type>
  class pointer_buffer
  {
    public:
    //==========================================================================
    // Inheritance type definition
    //==========================================================================
    typedef typename std::allocator<Type>     allocator_type;


    //============================================================================
    // Buffer type interface
    //============================================================================
    typedef Type                              value_type;                  
    typedef Type*                             pointer;
    typedef const Type*                       const_pointer;
    typedef Type*                             iterator;
    typedef const Type*                       const_iterator;
    typedef Type&                             reference;
    typedef const Type&                       const_reference;
    typedef std::size_t                       size_type;
    typedef std::ptrdiff_t                    difference_type;
    typedef std::ptrdiff_t                    index_type;


    //==========================================================================
    /**!
     *
     *
     **/
    //==========================================================================
    pointer_buffer( allocator_type const& a =allocator_type() ) 
    {
      szs_ = 0;
      bss_ = 0;
      buffer_ = 0;
    }

    //==========================================================================
    /**!
     *
     *
     **/
    //==========================================================================

    template<typename Sizes, typename Bases>
    pointer_buffer( Sizes           const& sz
                  , Bases           const& bs
                  , allocator_type  const& alloc = allocator_type()
                  , typename  boost::enable_if<
                              boost::fusion::traits::is_sequence<Sizes>
                              >::type* = 0
                  , typename  boost::enable_if<
                              boost::fusion::traits::is_sequence<Bases>
                              >::type* = 0
                  )
   {
      BOOST_MPL_ASSERT_MSG
      ( (boost::mpl::size<Sizes>::value == 1)
      , SIZE_MISMATCH_IN_BUFFER_CONSTRUCTOR
      , (Sizes)
      );

      BOOST_MPL_ASSERT_MSG
      ( (boost::mpl::size<Bases>::value == 1)
      , BASE_MISMATCH_IN_BUFFER_CONSTRUCTOR
      , (Bases)
      );

      resize(sz);
      rebase(bs);
      buffer_ = 0;

    }

    //==========================================================================
    /**!
     *
     *
     **/
    //==========================================================================
    template<typename Sizes, typename Bases>
    pointer_buffer( pointer_buffer  const& src
                  , Sizes           const& sz
                  , Bases           const& bs
                  , allocator_type  const& alloc = allocator_type()
                  , typename  boost::enable_if<
                              boost::fusion::traits::is_sequence<Sizes>
                              >::type* = 0
                  , typename  boost::enable_if<
                              boost::fusion::traits::is_sequence<Bases>
                              >::type* = 0
                  )
    {
      BOOST_MPL_ASSERT_MSG
      ( (boost::mpl::size<Sizes>::value == 1)
      , SIZE_MISMATCH_IN_BUFFER_CONSTRUCTOR
      , (Sizes)
      );

      BOOST_MPL_ASSERT_MSG
      ( (boost::mpl::size<Bases>::value == 1)
      , BASE_MISMATCH_IN_BUFFER_CONSTRUCTOR
      , (Bases)
      );

      buffer_ = src.buffer_;
      rebase(bs);
      resize(sz);


    }

    pointer_buffer( pointer_buffer const& src )
    {
      buffer_ = src.buffer_;
      bss_ = src.bss_;
      szs_ = src.szs_;

    }


    //==========================================================================
    // Basic destructor 
    //==========================================================================

    ~pointer_buffer() {}

    //==========================================================================
    /**!
     * Assign a buffer to the current buffer 
     *
     * \param src buffer to assign
     * \return The now updated buffer
     **/
    //==========================================================================
    pointer_buffer& operator=(pointer_buffer const& src)
    {

      buffer_ = src.buffer_;
      bss_ = src.bss_;
      szs_ = src.szs_;

      return *this;
    }



    ////////////////////////////////////////////////////////////////////////////
    // Iterator related methods
    ////////////////////////////////////////////////////////////////////////////
    iterator
    begin()
    {
      return buffer_;      
    }

    iterator
    end()
    {
      return buffer_ + bss_ + szs_;
    }

    ////////////////////////////////////////////////////////////////////////////
    // Forward size related methods
    ////////////////////////////////////////////////////////////////////////////
    size_type
    size()
    {
      return szs_;
    }
    ////////////////////////////////////////////////////////////////////////////
    // RandomAccessContainer Interface
    ////////////////////////////////////////////////////////////////////////////

    reference
    operator[](difference_type const& i)
    {
      // BOOST_ASSERT_MSG( (i >= lower())
      //                 , "Position is below buffer bounds"
      //                 );
                      
      // BOOST_ASSERT_MSG( (i <= upper())
      //                 , "Position is out of buffer bounds"
      //                 );
      return buffer_[i];
    }

    const_reference
    operator[](difference_type const& i) const
    {
      // BOOST_ASSERT_MSG( (i >= lower())
      //                 , "Position is below buffer bounds"
      //                 );
                      
      // BOOST_ASSERT_MSG( (i <= upper())
      //                 , "Position is out of buffer bounds"
      //                 );
      return buffer_[i];
    }

    ////////////////////////////////////////////////////////////////////////////
    // Swapping
    ////////////////////////////////////////////////////////////////////////////
    void swap( pointer_buffer& src )
    {
      size_type       src_szs_    = src.szs_;
      difference_type src_bss_    = src.bss_;
      Type*           src_buffer_ = src.buffer_;

      src.szs_    = szs_;
      src.bss_    = bss_;
      src.buffer_ = buffer_;

      szs_    = src_szs_;
      bss_    = src_bss_;
      buffer_ = src_buffer_;

      // boost::swap(src.szs_,szs_);
      // boost::swap(src.bss_,bss_);
      // boost::swap(src.buffer_,buffer_);
    }

    ////////////////////////////////////////////////////////////////////////////
    // resize/rebase/restructure buffer
    ////////////////////////////////////////////////////////////////////////////
    //    using parent_data::rebase;

    template<class Bases>
    typename boost::enable_if< boost::fusion::traits::is_sequence<Bases> >::type
    rebase(Bases const & b) { 

      BOOST_MPL_ASSERT_MSG
      ( (boost::mpl::size<Bases>::value == 1)
      , BASE_MISMATCH_IN_POINTER_BUFFER_REBASE
      , (Bases)
      );

      if(buffer_){
        buffer_ += bss_;
      }

      bss_ = boost::fusion::at_c<0>(b); 

      if(buffer_){
        buffer_ -= bss_;
      }
    }

    template<class Sizes>
    typename boost::enable_if< boost::fusion::traits::is_sequence<Sizes> >::type
    resize(Sizes const& s) {
      BOOST_MPL_ASSERT_MSG
      ( (boost::mpl::size<Sizes>::value == 1)
      , SIZE_MISMATCH_IN_POINTER_BUFFER_RESIZE
      , (Sizes)
      );
      szs_ = boost::fusion::at_c<0>(s);
    }

   

    template<class Bases,class Sizes>
    typename boost::enable_if_c < boost::fusion::traits::is_sequence<Sizes>::value
                                  &&
                                  boost::fusion::traits::is_sequence<Bases>::value
                                >::type
    restructure( Sizes const& s, Bases const& b)
    {
      BOOST_MPL_ASSERT_MSG
      ( (boost::mpl::size<Bases>::value == 1)
      , BASE_MISMATCH_IN_POINTER_BUFFER_RESTRUCTURE
      , (Bases)
      );

      BOOST_MPL_ASSERT_MSG
      ( (boost::mpl::size<Sizes>::value == 1)
      , SIZE_MISMATCH_IN_POINTER_BUFFER_RESTRUCTURE
      , (Sizes)
      );

      resize(s);
      rebase(b);
    }

    protected:
    ////////////////////////////////////////////////////////////////////////////
    // Allocator access
    ////////////////////////////////////////////////////////////////////////////
    size_type szs_;
    difference_type bss_;
    Type* buffer_;
 

  };

  //============================================================================
  /**!
   * Swap the contents of two buffer of same type and allocator settings
   **/
  //============================================================================
  template<class T>
  void swap( pointer_buffer<T>& a, pointer_buffer<T>& b )
  {
    a.swap(b);
  }


} }
  


#endif
