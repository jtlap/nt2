[ ## this file was manually modified by jt
    {
     'functor' : {
         'description' :['tangent of angle in \\\\f$\pi\\\\f$ multiples: \\\\f$\\\\tan(\pi a_0)\\\\f$.'] ,
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
             'included' : ['#include <nt2/toolbox/trigonometric/constants.hpp>',
                           'extern "C" {extern long double cephes_tanl(long double);}'],
             'scalar_included' : [  'static const long double long_pi = 3.141592653589793238462643383279502884197l;'],
             'notes' : [],
             'stamp' : 'modified by jt the 11/02/2011',
            },
         'ranges' : {
             'default' : [['T(-40)', 'T(40)']],
            },
         'specific_values' : {
             'default' : {
                 'nt2::One<T>()' : {'result' : 'nt2::Zero<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::Zero<T>()' : {'result' : 'nt2::Zero<r_t>()','ulp_thresh' : '0.5',},
                },
             'real_' : {
                 '-nt2::Quarter<T>()' : {'result' : 'nt2::Mone<r_t>()','ulp_thresh' : '1.0',},
                 'nt2::Half<T>()' : {'result' : 'nt2::Nan<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::Inf<T>()' : {'result' : 'nt2::Nan<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::Mhalf<T>()' : {'result' : 'nt2::Nan<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::Minf<T>()' : {'result' : 'nt2::Nan<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::Mone<T>()' : {'result' : 'nt2::Zero<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::Nan<T>()' : {'result' : 'nt2::Nan<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::One<T>()' : {'result' : 'nt2::Zero<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::Quarter<T>()' : {'result' : 'nt2::One<r_t>()','ulp_thresh' : '1.0',},
                 'nt2::Zero<T>()' : {'result' : 'nt2::Zero<r_t>()','ulp_thresh' : '0.5',},
                },
             'signed_int_' : {
                 'nt2::Mone<T>()' : {'result' : 'nt2::Zero<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::One<T>()' : {'result' : 'nt2::Zero<r_t>()','ulp_thresh' : '0.5',},
                 'nt2::Zero<T>()' : {'result' : 'nt2::Zero<r_t>()','ulp_thresh' : '0.5',},
                },
            },
         'verif_test' : {
             'property_call' : {
                 'real_' : ['nt2::tanpi(a0)'],
                },
             'property_value' : {
                 'real_' : ['::cephes_tanl(long_pi*a0)'],
                },
             'ulp_thresh' : {
                 'real_' : ['10.0'],
                },
            },
        },
    },
]
