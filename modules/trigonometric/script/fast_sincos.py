[ ## this file was manually modified by jt
    {
     'functor' : {
         'description' :['simultaneous sine and cosine in the interval \\\\f$[-\pi/4, \pi/4]\\\\f$, nan outside.',
                         '\\\\arg tie(si,co) = fast_sincos(a) returns the sine and cosine of a.',
                         '\\\\arg si = fast_sincos(a,co) returns the sine of a and put the cosine of a in co.',
                         '\\\\arg fast_sincos(a,si,co) returns 0 and and put the sine of a in si and the cosine cosine of a in co.',
                         ],
         'param_0' : ['angle in radian'],   
          'special_synopsis' : [
                "template<class A0> inline",
                "typename boost::dispatch::meta::call<tag::fast_sincos(A0 const&,A0 const&)",
                "                                    >::type",
                "fast_sincos(A0 const& a);",
                " ",
                "template<class A0> inline",
                "A0 fast_sincos(A0 const& a,A0,A0& si);",
                " ",
                "template<class A0> inline",
                "int fast_sincos(A0 const& a,A0,A0& si,A0& co);",
                 ],
         'arity' : '1',
         'call_types' : [],
         'ret_arity' : '2',
         'rturn' : {
             'default' : 'boost::fusion::tuple<ftype,ftype>',
            },
         'simd_types' : ['real_'],
         'special' : ['trigonometric'],
         'type_defs' : ['typedef typename boost::dispatch::meta::as_floating<T>::type ftype;'],
         'types' : ['real_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'created  by jt the 11/02/2011',
             'included' : 
                ['#include <nt2/toolbox/trigonometric/constants.hpp>',
                 'extern "C" {extern long double cephes_sinl(long double);}',
                 'extern "C" {extern long double cephes_cosl(long double);}'],
             'notes' : [],
             'stamp' : 'modified by jt the 11/02/2011',
            },
         'ranges' : {
             'real_' : [['nt2::Pi<T>()/4', 'nt2::Pi<T>()/4']],
             'default' : [['nt2::Pi<T>()/4', 'nt2::Pi<T>()/4']],
            },
         'specific_values' : {
             'default' : {
                 'nt2::Zero<T>()' : {'result' : ['nt2::Zero<r_t0>()', 'nt2::One<r_t0>()'],'ulp_thresh' : '0.75',},
                },
             'real_' : {
                 '-nt2::Pi<T>()/T(2)' : {'result' : ['nt2::Nan<r_t0>()', 'nt2::Nan<r_t1>()'],'ulp_thresh' : '0.75',},
                 '-nt2::Pi<T>()/T(4)' : {'result' : ['-nt2::Sqrt_2o_2<r_t0>()', 'nt2::Sqrt_2o_2<r_t0>()'],'ulp_thresh' : '0.75',},
                 'nt2::Inf<T>()' : {'result' : ['nt2::Nan<r_t0>()', 'nt2::Nan<r_t0>()'],'ulp_thresh' : '0.75',},
                 'nt2::Minf<T>()' : {'result' : ['nt2::Nan<r_t0>()', 'nt2::Nan<r_t0>()'],'ulp_thresh' : '0.75',},
                 'nt2::Nan<T>()' : {'result' : ['nt2::Nan<r_t0>()', 'nt2::Nan<r_t0>()'],'ulp_thresh' : '0.75',},
                 'nt2::Pi<T>()/T(2)' : {'result' : ['nt2::Nan<r_t0>()', 'nt2::Nan<r_t0>()'],'ulp_thresh' : '0.75',},
                 'nt2::Pi<T>()/T(4)' : {'result' : ['nt2::Sqrt_2o_2<r_t0>()', 'nt2::Sqrt_2o_2<r_t0>()'],'ulp_thresh' : '0.75',},
                 'nt2::Zero<T>()' : {'result' : ['nt2::Zero<r_t0>()', 'nt2::One<r_t0>()'],'ulp_thresh' : '0.75',},
                },
             'signed_int_' : {
                 'nt2::Zero<T>()' : {'result' : ['nt2::Zero<r_t0>()', 'nt2::One<r_t0>()'],'ulp_thresh' : '0.75',},
                },
            },
         'verif_test' : {
             'property_call' : {
                 'real_' : ['nt2::fast_sincos(a0)'],
                },
             'property_value' : {
                 'real_' : [['(r_t0)::cephes_sinl(a0)', '(r_t1)::cephes_cosl(a0)']],
                },
             'ulp_thresh' : {
                 'real_' : ['0.5'],
                },
            },
        },
    },
]
