/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_SDK_CONFIG_DETAILS_MASKS_ALTIVEC_HPP_INCLUDED
#define BOOST_SIMD_SDK_CONFIG_DETAILS_MASKS_ALTIVEC_HPP_INCLUDED

#include <boost/simd/sdk/config/details/masks/forward.hpp>
#include <boost/simd/sdk/config/details/masks/vendor.hpp>
#include <boost/simd/sdk/config/os.hpp>
#include <boost/simd/sdk/config/arch.hpp>
#include <boost/simd/sdk/simd/extensions.hpp>

#if defined(BOOST_SIMD_OS_LINUX) && defined(BOOST_SIMD_ARCH_POWERPC)
#include <fcntl.h>
#include <linux/auxvec.h>
#include <asm/cputable.h>
#elif defined(BOOST_SIMD_OS_MAC_OS) && defined(BOOST_SIMD_ARCH_POWERPC)
#include <Gestalt.h>
#endif

////////////////////////////////////////////////////////////////////////////////                                                                     
// Masks for altivec detection                                                                                        
////////////////////////////////////////////////////////////////////////////////

namespace boost{ namespace simd{ namespace config{ namespace details{

  template<class Vendor>
  struct cpuid_mask<tag::altivec_, Vendor>
  {
    inline bool get_support(){ return false; }
  };

  template<>
  struct cpuid_mask<tag::altivec_, ibm_>
  {
    inline bool get_support()
    {

#if defined(BOOST_SIMD_OS_LINUX) && defined(BOOST_SIMD_ARCH_POWERPC)

      bool hasAltiVec = false;
      unsigned long buf[64];
      ssize_t count;
      int fd, i;
      fd = open("/proc/self/auxv", O_RDONLY);
      if (fd < 0) { return false; }
      do 
      {
	count = read(fd, buf, sizeof(buf));
	if (count < 0) { break; }
	for (i=0; i < (count / sizeof(unsigned long)); i += 2) 
	{
	  if (buf[i] == AT_HWCAP) 
	  {
	    hasAltiVec = !!(buf[i+1] & PPC_FEATURE_HAS_ALTIVEC);
            close(fd);
	    return hasAltiVec;
	  } 
	  else if (buf[i] == AT_NULL)
	  {
            close(fd);
	    return hasAltiVec;
	  }
	}
      } while (count == sizeof(buf));
      return hasAltiVec;

#elif defined(BOOST_SIMD_OS_MAC_OS) && defined(BOOST_SIMD_ARCH_POWERPC)

      long cpuAttributes;
      Boolean hasAltiVec = false;
      OSErr err = Gestalt( gestaltPowerPCProcessorFeatures, &cpuAttributes );
      if( noErr == err ) { hasAltiVec = ( 1 << gestaltPowerPCHasVectorInstructions) & cpuAttributes; }
      return hasAltiVec;

#else
      return false;
#endif

    }
  };

} } } }

#endif

