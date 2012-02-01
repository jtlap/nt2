#include <boost/simd/sdk/config/is_supported.hpp>
#include <iostream>
#include <cstddef>
#include <cstring>

using boost::simd::is_supported;
using namespace boost::simd::tag;

struct pair
{
  const char* name;
  bool(*function)();
};

static pair data[] =
{
  { "sse",    &is_supported<sse_>     },
  { "sse2",   &is_supported<sse2_>    },
  { "sse3",   &is_supported<sse3_>    },
  { "ssse3",  &is_supported<ssse3_>   },
  { "sse4a",  &is_supported<sse4a_>   },
  { "sse4.1", &is_supported<sse4_1_>  },
  { "sse4.2", &is_supported<sse4_2_>  },
  { "avx",    &is_supported<avx_>     },
  { "xop",    &is_supported<xop_>     },
  { "fma4",   &is_supported<fma4_>    },
  { "avx",    &is_supported<avx_>     },
  { "lrb",    &is_supported<lrb_>     },
  { "vmx",    &is_supported<altivec_> },
  { "vmx",    &is_supported<neon_>    }
};

int main(int argc, char* argv[])
{
  if(argc != 2)
  {
    std::cerr << "usage: " << argv[0] << " <instruction_set>" << std::endl;
    return 1;
  }
  
  for(std::size_t i=0; i!=sizeof data/sizeof *data; ++i)
  {
    if(!std::strcmp(argv[1], data[i].name))
    {
      bool b = data[i].function();
      std::cout << argv[1] << ": " << (b ? "supported" : "not supported") << std::endl;
      return !b;
    }
  }
      
  std::cerr << argv[1] << ": unknown instruction set" << std::endl;
  return 1;
}
