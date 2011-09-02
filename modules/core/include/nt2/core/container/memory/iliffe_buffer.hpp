//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_MEMORY_ILIFFE_BUFFER_HPP
#define NT2_CORE_CONTAINER_MEMORY_ILIFFE_BUFFER_HPP

#include <nt2/sdk/memory/slice.hpp>
#include <boost/fusion/include/at.hpp>
#include <nt2/sdk/memory/no_padding.hpp>
#include <nt2/sdk/meta/add_pointers.hpp>
#include <nt2/sdk/meta/add_const_reference.hpp>

namespace nt2 { namespace memory
{  //============================================================================
  /**
   * \brief Memory buffer allocated as a Iliffe vector
   **/
  //============================================================================
  template< unsigned Dimensions
          , typename Type
          , typename Padding
          , typename Allocator          
          >
  struct iliffe_buffer
  {  
    typedef typename Allocator::template rebind<memory::byte>::other  allocator;
    typedef typename Allocator::value_type                      value_type;
    typedef typename Allocator::pointer                         pointer;
    typedef typename Allocator::const_pointer                   const_pointer;
    typedef typename Allocator::reference                       reference;
    typedef typename Allocator::const_reference                 const_reference;
    typedef typename Allocator::size_type                       size_type;
    typedef typename Allocator::difference_type                 difference_type;
    typedef typename meta::add_pointers<Type,Dimensions>::type  data_type;      
    
    //==========================================================================
    /**
     **/
    //==========================================================================
    template<typename Sizes, typename Bases> 
    iliffe_buffer ( Sizes const&      szs
                  , Bases const&      bss
                  , Padding const&    p
                  , Allocator const&  a = Allocator() 
                  )
    : data_(0), begin_(0), end_(0), idx_(boost::fusion::at_c<0>(bss)), alloc_(a)
    {      
      size_type numel = slice<1>(szs,p);
      if(numel != 0)
      {
        // how many bytes for the data and  the indexing
        size_type data_size = numel * sizeof(value_type);
        size_type idx_size  = index_size(szs,p);
        
        // allocate that much bytes
        memory::byte* ptr = alloc_.allocate(idx_size+data_size);
        
        // points to the begining of the data block
        begin_ = reinterpret_cast<value_type*>(ptr+idx_size);
        
        // Recursively fills out the index
        data_ = link(ptr,begin_ - idx_,szs,bss,p,boost::mpl::int_<Dimensions>());
        
        // Find out end_
        end_ = begin_ + numel;
      }
    }    
    
    //==========================================================================
    /**
     **/
    //==========================================================================
    template<typename Sizes, typename Bases> 
    iliffe_buffer ( Sizes const&      szs
                  , Bases const&      bss
                  , value_type*       shared
                  , Allocator const&  a = Allocator() 
                  )
    : alloc_(a), data_(0), idx_(boost::fusion::at_c<0>(bss))
    {      
      if(shared != 0)
      {
        // Only allocate the index
        size_type idx_size = index_size(szs,p);
        memory::byte* ptr = alloc_.allocate(idx_size);
        
        // Recursively fills out the index
        data_ = link(ptr,shared-idx_,szs,bss,p,boost::mpl::int_<Dimensions>());
      }
    }
    
    ~iliffe_buffer() 
    { 
      if(data_) 
      {
        // Restore the actual allocated pointer before deallocating it
        memory::byte* ptr;
        ptr = reinterpret_cast<memory::byte*>(data_ + idx_);
        
        alloc_.deallocate( ptr );
      }
    }

    data_type     data()  const { return data_; }
    pointer       begin()       { return base_; }
    const_pointer begin() const { return base_; }
    
    protected:

    //==========================================================================
    /*
     * index_size computes the number of bytes required to store the index table
     * of the Iliffe vector
     */
    //==========================================================================
    template<class Seq> inline std::size_t
    index_size(Seq const& s, Padding const& p) const
    {
      // The index section is the sum of all required index aligned
      // globally on the boundary value provided by p
      return align_on( index_size(szs,boost::mpl::size_t<2>()), p.value() );  
    }
    
    template<class Seq,unsigned Index> inline std::size_t     
    index_size(Seq const& s, boost::mpl::size_t<Index> const&) const
    {
        return  slice<Index>(s,no_padding()) * sizeof(void*) 
              + index_size(s,boost::mpl::size_t<Index+1>());
    }

    template<class Seq> inline std::size_t     
    index_size(Seq const& s, boost::mpl::size_t<Dimensions> const&) const
    {
      return slice<Dimensions>(s,no_padding()) * sizeof(void*)
    }

    //==========================================================================
    /*
     * link performs the indexing of the Iliffe vector 
     */
    //==========================================================================
    template<typename Sizes, typename Bases, int D>
    typename meta::add_pointers<Type,D>::type
    link( memory::byte*   p
        , value_type*     base
        , Sizes const&    szs
        , Bases const&    bss
        , Padding const&  pd
        , boost::mpl::int_<D> const&
        )
    {
      // Retrieve the current pointer in the index
      typedef typename meta::add_pointers<Type,D>::type ptr_type;      
      ptr_type ptr = reinterpret_cast<ptr_type>(p);
      
      // Retrieve the underlying indexed part
      size_type offset = slice<D>(szs,no_padding())*sizeof(void*));
      ptr[0] = link(p+offset,base,szs,bss,pd,boost::mpl::int_<D-1>());
        
      // Fill out the remaining indices
      size_type local_size = boost::fusion::at_c<D-2>(szs);
      for(int i=1; i < slice<D>(szs,no_padding());++i)
        ptr[i] = ptr[i-1] + local_size;
        
      // Rebase the index        
      ptr -= boost::fusion::at_c<D-1>(bss);
      return ptr;
    }
    
    template<typename Sizes, typename Bases>
    typename meta::add_pointers<Type,2>::type
    link( memory::byte*   p
        , value_type*     base
        , Sizes const&    szs 
        , Bases const&    bss        
        , Padding const&  pd
        , boost::mpl::int_<2> const&
        )
    {
      // Retrieve the current pointer in the index           
      typedef typename meta::add_pointers<Type,2>::type ptr_type;     
      ptr_type ptr = reinterpret_cast<ptr_type>(p);
      
      // Points to the beginning of the data block
      ptr[0] = base;
      
      // Fill out the remaining indices
      std::size_t local_size = align_on(boost::fusion::at_c<0>(szs),pd.value());
      for(int i=1; i < slice<2>(szs,no_padding());++i)
        ptr[i] = ptr[i-1] + local_size;
        
      // Rebase the index
      ptr -= boost::fusion::at_c<1>(bss);
      return ptr;    
    }
    
    private:
    data_type data_;
    pointer   begin_, end_;
    int       idx_;
    allocator alloc_;
  };
  
  //============================================================================
  /**
   * iliffe_buffer is specialized for 1D case to not allocate any indexing zone
   **/
  //============================================================================
  template< typename Type
          , typename Padding
          , typename Allocator          
          >
  struct iliffe_buffer<1,Type,Padding,Allocator>
  {  
    typedef typename Allocator::template rebind<memory::byte>::other  allocator;
    typedef typename Allocator::value_type      value_type;
    typedef typename Allocator::pointer         pointer;
    typedef typename Allocator::const_pointer   const_pointer;
    typedef typename Allocator::reference       reference;
    typedef typename Allocator::const_reference const_reference;
    typedef typename Allocator::size_type       size_type;
    typedef typename Allocator::difference_type difference_type;
    typedef value_type*                         data_type;         

    //==========================================================================
    /**
     **/
    //==========================================================================
    template<typename Sizes, typename Bases> 
    iliffe_buffer ( Sizes const&      szs
                  , Bases const&      bss
                  , Padding const&    p
                  , Allocator const&  a = Allocator() 
                  )
    : alloc_(a), data_(0), shared_(false)
    {
      size_type numel = slice<1>(sizes_,p);
      if(numel != 0) 
      {
        data_ = alloc_.allocate( numel );
        data_ -= boost::fusion::at_c<0>(bss);
      }
    }
    
    //==========================================================================
    /**
     **/
    //==========================================================================
    template<typename Sizes, typename Bases> 
    iliffe_buffer ( Sizes const&      szs
                  , Bases const&      bss
                  , value_type*       shared
                  , Allocator const&  a = Allocator() 
                  )
    : alloc_(a), data_(0), shared_(true), idx_(boost::fusion::at_c<0>(bss))
    {      
      if(shared != 0) data_ = shared - idx_;
    }
    
    ~iliffe_buffer() { if(!shared_ && data_) alloc_.deallocate(data_ + idx_); }
  
    data_type     data() const { return data_; }

    pointer       begin()       { return data_; }
    const_pointer begin() const { return data_; }

    private:
    data_type   data_;
    int         idx_;
    Allocator   alloc_;
    bool        shared_;
  }
} }

#endif 
