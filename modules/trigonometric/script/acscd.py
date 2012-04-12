[ ## this file was manually modified by jt
    {
     'functor' : {
         'description' :['inverse cosecant in degree.'] ,
         'arity' : '1',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'typename boost::dispatch::meta::as_floating<T>::type',
            },
         'simd_types' : ['real_','int_convert_','uint_convert_'],
         'special' : ['trigonometric'],
         'type_defs' : [],
         'types' : ['real_', 'unsigned_int_', 'signed_int_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'created  by jt the 11/02/2011',
             'included' : 
                ['#include <nt2/toolbox/trigonometric/constants.hpp>',
                 'extern "C" {extern long double cephes_asinl(long double);}'],
             'notes' : ['asin(1/a0)*Radindeg'],
             'stamp' : 'modified by jt the 11/02/2011',
            },
         'ranges' : {
             'default' : [['nt2::One<T>()', 'nt2::Ten<T>()']],
             'real_' : [['nt2::One<T>()', 'nt2::Ten<T>()']],
             'signed_int_' : [['T(1)', 'T(10)']],
            },
         'specific_values' : {
             'default' : {
                 'nt2::One<T>()' : {'result' : '90','ulp_thresh' : '0.5',},
                 'nt2::Two<T>()' : {'result' : '30','ulp_thresh' : '0.5',},
                 'nt2::Zero<T>()' : {'result' : 'nt2::Nan<r_t>()','ulp_thresh' : '0.5',},
                },
             'real_' : {
                 '-nt2::Two<T>()' : {'result' : '-30','ulp_thresh' : '0.5',},
                 'nt2::Inf<T>()' : {'result' : 'nt2::Zero<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::Minf<T>()' : {'result' : 'nt2::Zero<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::Mone<T>()' : {'result' : '-90','ulp_thresh' : '0.5',},
                 'nt2::Nan<T>()' : {'result' : 'nt2::Nan<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::One<T>()' : {'result' : '90','ulp_thresh' : '0.5',},
                 'nt2::Two<T>()' : {'result' : '30','ulp_thresh' : '0.5',},
                 'nt2::Zero<T>()' : {'result' : 'nt2::Nan<r_t>()','ulp_thresh' : '0.5',},
                },
             'signed_int_' : {
                 '-nt2::Two<T>()' : {'result' : '-30','ulp_thresh' : '0.5',},
                 'nt2::Mone<T>()' : {'result' : '-90','ulp_thresh' : '0.5',},
                 'nt2::One<T>()' : {'result' : '90','ulp_thresh' : '0.5',},
                 'nt2::Two<T>()' : {'result' : '30','ulp_thresh' : '0.5',},
                 'nt2::Zero<T>()' : {'result' : 'nt2::Nan<r_t>()','ulp_thresh' : '0.5',},
                },
            },
         'verif_test' : {
             'property_call' : {
                 'real_' : ['nt2::acscd(a0)'],
                },
             'property_value' : {
                 'real_' : ['::cephes_asinl(1.0l/(a0))*nt2::long_radindeg'],
                },
             'ulp_thresh' : {
                 'real_' : ['7.0'],
                },
            },
        },
    },
]
