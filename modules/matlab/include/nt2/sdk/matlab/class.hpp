#ifndef NT2_SDK_MATLAB_CLASS_HPP_INCLUDED
#define NT2_SDK_MATLAB_CLASS_HPP_INCLUDED

#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_signed.hpp>
#include <climits>

#include <boost/config.hpp>
#if !defined(BOOST_NO_CHAR16_T) && !defined(__STDC_UTF_16__)
#define __STDC_UTF_16__
#endif
#include <mat.h>

namespace nt2 { namespace matlab
{
  template<class T, class Dummy = void>
  struct class_;

  #define NT2_MATLAB_CLASS_DEF(size, signed, name)                             \
  template<typename T>                                                         \
  struct class_< T                                                             \
               , typename boost::                                              \
                 enable_if_c< sizeof(T)*CHAR_BIT == size                       \
                              && boost::is_signed<T>::value == signed          \
                            >::type                                            \
               >                                                               \
  {                                                                            \
      static const mxClassID value = name;                                     \
  };

  NT2_MATLAB_CLASS_DEF(8,  true,  mxINT8_CLASS  )
  NT2_MATLAB_CLASS_DEF(16, true,  mxINT16_CLASS )
  NT2_MATLAB_CLASS_DEF(32, true,  mxINT32_CLASS )
  NT2_MATLAB_CLASS_DEF(64, true,  mxINT64_CLASS )
  NT2_MATLAB_CLASS_DEF(8,  false, mxUINT8_CLASS )
  NT2_MATLAB_CLASS_DEF(16, false, mxUINT16_CLASS)
  NT2_MATLAB_CLASS_DEF(32, false, mxUINT32_CLASS)
  NT2_MATLAB_CLASS_DEF(64, false, mxUINT64_CLASS)

  #undef NT2_MATLAB_CLASS_DEF

  template<> struct class_<float>  { static const mxClassID value = mxSINGLE_CLASS; };
  template<> struct class_<double> { static const mxClassID value = mxDOUBLE_CLASS; };
} }

#endif
