#ifndef NT2_TOOLBOX_MATLAB_DETAILS_ARRAY_TRAITS_HPP_INCLUDED
#define NT2_TOOLBOX_MATLAB_DETAILS_ARRAY_TRAITS_HPP_INCLUDED

#include <nt2/sdk/meta/primitive_of.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <boost/mpl/bool.hpp>
#include <vector>
#include <numeric>
#include <cstring>
#include <functional>

#include <mat.h>

namespace nt2 { namespace matlab
{
    namespace details
    {
        template<typename T>
        typename meta::primitive_of<typename meta::strip<T>::type>::type* get_data(mxArray* p)
        {
            return (typename meta::primitive_of<typename meta::strip<T>::type>::type*)mxGetData(p);
        }
    }

    namespace traits
    {
        template<typename T, typename Dummy = void>
        struct class_;
        
        template<typename T, typename Dummy = void>
        struct get_buffer_impl;
        
        template<typename T>
        typename meta::primitive_of<T>::type* get_buffer(T& t)
        {
            return get_buffer_impl<T>::call(t);
        }
        
        template<typename T>
        typename meta::primitive_of<T>::type const* get_buffer(const T& t)
        {
            return get_buffer_impl<T>::call(const_cast<T&>(t));
        }
        
        template<typename T, typename Dummy = void>
        struct is_complex : boost::mpl::false_
        {
        };
        
        template<typename T, typename Dummy = void>
        struct size_impl;
        
        template<typename T>
        std::vector<std::size_t> size(const T& t)
        {
            return size_impl<T>::call(t);
        }

        template<typename T, typename Dummy = void>
        struct to_matlab_impl
        {
            static mxArray* call(const T& t)
            {
                std::vector<std::size_t> dims = size(t);
                
                typedef typename meta::primitive_of<typename meta::strip<T>::type>::type Primitive;
                mxArray* p = 
                    mxCreateNumericArray(
                        dims.size(),
                        dims.data(), 
                        class_<Primitive>::value,
                        is_complex<T>::value ? mxCOMPLEX : mxREAL
                    )
                ;
    
                std::size_t nb_elems =
                    std::accumulate(
                        dims.begin(),
                        dims.end(),
                        1,
                        std::multiplies<std::size_t>()
                    )
                ;
    
                std::memcpy(
                    details::get_data<T>(p),
                    get_buffer(t),
                    nb_elems*sizeof(Primitive)
                );
                
                return p;
            }
        };
        
        template<typename T>
        mxArray* to_matlab(const T& t)
        {
            return to_matlab_impl<T>::call(t);
        }
        
        template<typename T, typename Dummy = void>
        struct from_matlab_impl
        {
            static T call(mxArray* t)
            {
                typedef typename meta::primitive_of<typename meta::strip<T>::type>::type Primitive;
                
                const mwSize* dims = mxGetDimensions(t);
                mwSize dims_size = mxGetNumberOfDimensions(t);
                
                T out;
                
                mwSize nb_elems =
                    std::accumulate(
                        dims,
                        dims + dims_size,
                        1,
                        std::multiplies<mwSize>()
                    )
                ;
                
                std::memcpy(
                    get_buffer(out),
                    details::get_data<T>(t),
                    nb_elems*sizeof(Primitive)
                );
                
                return out;
            }
        };
        
        template<typename T>
        T from_matlab(mxArray* t)
        {
            return from_matlab_impl<T>::call(t);
        }
    }
    
}}

#endif
