[ ## this file was manually modified by jt
    {
     'functor' : {
         'description' :['inverse cotangent.'] ,
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
             'included' : ['#include <nt2/toolbox/trigonometric/constants.hpp>'],
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
                 'nt2::One<T>()' : {'result' : '7.853981633974483e-01','ulp_thresh' : '1.5',},
                 'nt2::Zero<T>()' : {'result' : '1.570796326794897e+00','ulp_thresh' : '1.5',},
                },
             'real_' : {
                 'nt2::Half<T>()' : {'result' : '1.107148717794090e+00','ulp_thresh' : '1.5',},
                 'nt2::Inf<T>()' : {'result' : '0','ulp_thresh' : '1.5',},
                 'nt2::Mhalf<T>()' : {'result' : '-1.107148717794090e+00','ulp_thresh' : '1.5',},
                 'nt2::Minf<T>()' : {'result' : '0','ulp_thresh' : '1.5',},
                 'nt2::Mone<T>()' : {'result' : '-7.853981633974483e-01','ulp_thresh' : '1.5',},
                 'nt2::Nan<T>()' : {'result' : 'nt2::Nan<r_t>()','ulp_thresh' : '1.5',},
                 'nt2::One<T>()' : {'result' : '7.853981633974483e-01','ulp_thresh' : '1.5',},
                 'nt2::Zero<T>()' : {'result' : '1.570796326794897e+00','ulp_thresh' : '1.5',},
                },
             'signed_int_' : {
                 'nt2::Mone<T>()' : {'result' : '-7.853981633974483e-01','ulp_thresh' : '1.5',},
                 'nt2::One<T>()' : {'result' : '7.853981633974483e-01','ulp_thresh' : '1.5',},
                 'nt2::Zero<T>()' : {'result' : '1.570796326794897e+00','ulp_thresh' : '1.5',},
                },
            },
         'verif_test' : {
             'property_call' : {
                },
             'property_value' : {
                },
             'ulp_thresh' : {
                },
            },
        },
    },
]
