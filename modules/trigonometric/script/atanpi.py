[ ## this file was manually modified by jt
    {
     'functor' : {
         'description' :['inverse tangent in \\\\f$\pi\\\\f$ multiples.'] ,
         'arity' : '1',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'typename boost::dispatch::meta::as_floating<T>::type',
            },
         'simd_types' : ['real_','int_convert_','uint_convert_'],
         'special' : ['trigonometric'],
         'types' : ['real_', 'unsigned_int_', 'signed_int_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'created  by jt the 11/02/2011',
             'scalar_included' : ['static const long double long_pi = 3.141592653589793238462643383279502884197l;'],
             'included' : ['#include <nt2/toolbox/trigonometric/constants.hpp>',
                           'extern "C" {extern long double cephes_atanl(long double);}'],
            'notes' : [],
             'stamp' : 'modified by jt the 11/02/2011',
            },
         'ranges' : {
             'default' : [['nt2::Zero<T>()', 'nt2::One<T>()']],
             'real_' : [['nt2::Mone<T>()', 'nt2::One<T>()']],
             'signed_int_' : [['T(-1)', 'T(1)']],
            },
         'specific_values' : {
             'default' : {
                 'nt2::One<T>()' : {'result' : '0.25','ulp_thresh' : '0.5',},
                 'nt2::Zero<T>()' : {'result' : 'nt2::Zero<r_t>()','ulp_thresh' : '0.5',},
                },
             'real_' : {
                 'nt2::Inf<T>()' : {'result' : '0.5','ulp_thresh' : '0.5',},
                 'nt2::Minf<T>()' : {'result' : '-0.5','ulp_thresh' : '0.5',},
                 'nt2::Mone<T>()' : {'result' : '-0.25','ulp_thresh' : '0.5',},
                 'nt2::Nan<T>()' : {'result' : 'nt2::Nan<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::One<T>()' : {'result' : '0.25','ulp_thresh' : '0.5',},
                 'nt2::Zero<T>()' : {'result' : 'nt2::Zero<r_t>()','ulp_thresh' : '0.5',},
                },
             'signed_int_' : {
                 'nt2::Mone<T>()' : {'result' : '-0.25','ulp_thresh' : '0.5',},
                 'nt2::One<T>()' : {'result' : '0.25','ulp_thresh' : '0.5',},
                 'nt2::Zero<T>()' : {'result' : 'nt2::Zero<r_t>()','ulp_thresh' : '0.5',},
                },
            },
         'verif_test' : {
             'property_call' : {
                 'real_' : ['nt2::atanpi(a0)'],
                },
             'property_value' : {
                 'real_' : ['::cephes_atanl(a0)/long_pi'],
                },
             'ulp_thresh' : {
                 'real_' : '1.0',
                },
            },
        },
    },
]
