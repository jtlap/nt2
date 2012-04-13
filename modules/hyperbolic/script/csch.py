[ ## this file was manually modified by jt
    {
     'functor' : {
          'description' :['hyperbolic cosecant: \\\\f$\frac1{\\\\sinh(a_0)}\\\\f$.'] ,
         'arity' : '1',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'typename boost::dispatch::meta::as_floating<T>::type',
            },
         'simd_types' : ['real_'],
         'simd_ulp_thresh' : ['1.5'],   
         'type_defs' : [],
         'types' : ['real_', 'unsigned_int_', 'signed_int_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'created  by jt the 20/02/2011',
             'included' : 
                ['#include <nt2/toolbox/exponential/constants.hpp>',
                 '#include <nt2/include/functions/rec.hpp>',
                 'extern "C" { long double cephes_sinhl(long double); }'],
             'notes' : [],
             'stamp' : 'modified by jt the 20/02/2011',
            },
         'ranges' : {
             'default' : [['T(-10)', 'T(10)']],
            },
         'specific_values' : {
             'default' : {
                 'nt2::Zero<T>()' : {'result' : 'nt2::Nan<r_t>()','ulp_thresh' : '0.5',},
                },
             'real_' : {
                 '-nt2::Zero<T>()' : {'result' : '-nt2::Inf<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::Inf<T>()' : {'result' : 'nt2::Zero<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::Minf<T>()' : {'result' : 'nt2::Zero<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::Nan<T>()' : {'result' : 'nt2::Nan<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::Zero<T>()' : {'result' : 'nt2::Inf<r_t>()','ulp_thresh' : '0.5',},
                },
             'signed_int_' : {
                 'nt2::Zero<T>()' : {'result' : 'nt2::Nan<r_t>()','ulp_thresh' : '0.5',},
                },
            },
         'verif_test' : {
             'property_call' : {
                 'real_' : ['nt2::csch(a0)'],
                },
             'property_value' : {
                 'real_' : ['1.0l/(::cephes_sinhl(a0))'],
                },
             'ulp_thresh' : {
                 'real_' : ['1.0'],
                },
            },
        },
    },
]
