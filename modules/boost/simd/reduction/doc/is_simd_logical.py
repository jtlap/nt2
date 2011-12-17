[ ## this file was manually modified by jt
    {
     'functor' : {
         'description' : ['returns true if all vector elements have all or no bit sets.'],
         'module' : 'boost',
         'arity' : '1',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'bool',
            },
         'simd_types' : ['real_'],
         'special' : ['reduction'],  
         'type_defs' : [],
         'types' : ['real_', 'signed_int_','unsigned_int_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'created  by jt the 24/02/2011',
             'included' : ['#include <boost/simd/sdk/simd/logical.hpp>'],
             'no_ulp' : 'True',
             'notes' : [],
             'stamp' : 'modified by jt the 24/02/2011',
            },
         'ranges' : {
             'default' : [['boost::simd::Valmin<T>()', 'boost::simd::Valmax<T>()']],
            },
         'specific_values' : {
             'signed_int_' : {
                 'boost::simd::One<T>()' : {'result' : 'false','ulp_thresh' : '0',},
                 'boost::simd::Zero<T>()' : {'result' : 'true','ulp_thresh' : '0',},
                 'boost::simd::Mone<T>()' : {'result' : 'true','ulp_thresh' : '0',},
                },
            'unsigned_int_' : {
                 'boost::simd::One<T>()' : {'result' : 'false','ulp_thresh' : '0',},
                 'boost::simd::Zero<T>()' : {'result' : 'true','ulp_thresh' : '0',},
                 'boost::simd::Mone<T>()' : {'result' : 'true','ulp_thresh' : '0',},
                },
             'real_' : {
                 'boost::simd::Inf<T>()' : {'result' : 'false','ulp_thresh' : '0',},
                 'boost::simd::Minf<T>()' : {'result' : 'false','ulp_thresh' : '0',},
                 'boost::simd::Mone<T>()' : {'result' : 'false','ulp_thresh' : '0',},
                 'boost::simd::Nan<T>()' : {'result' : 'true','ulp_thresh' : '0',},
                 '-boost::simd::Nan<T>()' : {'result' : 'false','ulp_thresh' : '0',},
                 'boost::simd::One<T>()' : {'result' : 'false','ulp_thresh' : '0',},
                 'boost::simd::Zero<T>()' : {'result' : 'true','ulp_thresh' : '0',},
                },
            },
         'verif_test' : {
            },
        },
    },
]
