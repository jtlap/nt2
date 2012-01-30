//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/sdk/config/details/detect.hpp>
#include <boost/simd/sdk/config/arch.hpp>
#include <boost/simd/sdk/config/os.hpp>

#if defined(BOOST_SIMD_ARCH_X86)
#include <boost/simd/sdk/config/details/cpuid.hpp>
#include <boost/simd/sdk/config/details/get_vendor.hpp>
#elif defined(BOOST_SIMD_OS_LINUX) && defined(BOOST_SIMD_ARCH_POWERPC)
#include <fcntl.h>
#include <linux/auxvec.h>
#include <asm/cputable.h>
#elif defined(BOOST_SIMD_OS_MAC_OS) && defined(BOOST_SIMD_ARCH_POWERPC)
#include <Gestalt.h>
#endif

#define BOOST_SIMD_DECLARE_X86_DETECTION_CALL(x, y, z)                         \
static const int bit = x, function = y, register_id = z;                       \
int regs_x86[4]; boost::simd::config::details::cpuid(regs_x86, function);      \
return boost::simd::config::details::has_bit_set(regs_x86[register_id-1], bit);\
/**/

namespace boost { namespace simd { namespace config { namespace details
{

#if defined(BOOST_SIMD_ARCH_X86)

  bool detect(tag::sse2_ const&   )
  {
    if(get_vendor() == intel || get_vendor() == amd) 
    { BOOST_SIMD_DECLARE_X86_DETECTION_CALL(26,0x00000001,4) }
    else return false;
  }

  bool detect(tag::sse3_ const&   )
  {
    if(get_vendor() == intel || get_vendor() == amd) 
    { BOOST_SIMD_DECLARE_X86_DETECTION_CALL(0,0x00000001,3) }
    else return false;
  }

  bool detect(tag::ssse3_ const&  )
  {
    if(get_vendor() == intel || get_vendor() == amd) 
    { BOOST_SIMD_DECLARE_X86_DETECTION_CALL(9,0x00000001,3) }
    else return false;
  }

  bool detect(tag::sse4a_ const&  )
  {
    if(get_vendor() == amd){ BOOST_SIMD_DECLARE_X86_DETECTION_CALL(6,0x80000001,3); }
    else return false;
  }

  bool detect(tag::sse4_1_ const& )
  {
    if(get_vendor() == intel || get_vendor() == amd) 
    { BOOST_SIMD_DECLARE_X86_DETECTION_CALL(19,0x00000001,3) }
    else return false;
  }

  bool detect(tag::sse4_2_ const& )
  {
    if(get_vendor() == intel || get_vendor() == amd) 
    { BOOST_SIMD_DECLARE_X86_DETECTION_CALL(20,0x00000001,3) }
    else return false;
  }

  bool detect(tag::avx_ const&    )
  {
    if(get_vendor() == intel || get_vendor() == amd) 
    { BOOST_SIMD_DECLARE_X86_DETECTION_CALL(28,0x00000001,3) }
    else return false;
  }

#endif

#if defined(BOOST_SIMD_ARCH_POWERPC)
  bool detect(tag::altivec_ const&)
  {

#if defined(BOOST_SIMD_OS_LINUX)
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

#elif defined(BOOST_SIMD_OS_MAC_OS)

    long cpuAttributes;
    bool hasAltiVec = false;
    OSErr err = Gestalt( gestaltPowerPCProcessorFeatures, &cpuAttributes );
    if( noErr == err ) { hasAltiVec = ( 1 << gestaltPowerPCHasVectorInstructions) & cpuAttributes; }
    return hasAltiVec;

#else
      return false;
#endif

  }

#endif

} } } }  
