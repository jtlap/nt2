[ ## this file was manually modified by jt
    {
     'functor' : {
         'arity' : '1',
         'call_types' : [],
         'ret_arity' : '2',
         'rturn' : {
              'default' : 'boost::fusion::vector<T,typename nt2::meta::as_integer<T,signed>::type>',
            },
         'simd_types' : [],
         'special' : ['libc'],
         'type_defs' : [],
         'types' : ['real_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'created  by jt the 05/03/2011',
             'included' :
                ['#include <boost/fusion/tuple.hpp>',
                 '#include <nt2/include/functions/mantissa.hpp>',
                 '#include <nt2/include/functions/exponent.hpp>'],
             'notes' : [],
             'stamp' : 'modified by jt the 05/03/2011',
            },
         'ranges' : {
             'default' : [['T(-100)', 'T(100)']],
            },
         'specific_values' : {
            },
         'verif_test' : {
             'property_call' : {
                 'default' : ['nt2::libc::frexp(a0)'],
                },
             'property_value' : {
                 'default' : [['nt2::mantissa(a0)/2', 'nt2::exponent(a0)+1']],
                },
             'simd' : {
                },
             'ulp_thresh' : {
                 'default' : ['1'],
                },
            },
        },
    },
]
