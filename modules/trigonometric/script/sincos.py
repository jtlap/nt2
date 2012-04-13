[ ## this file was manually modified by jt
    {
     'functor' : {
         'description' :['simultaneous sine and cosine.',
                         '\\\\arg tie(si,co) = sincos(a) returns the sine and cosine of a.',
                         '\\\\arg si = sincos(a,co) returns the sine of a and put the cosine of a in co.',
                         '\\\\arg sincos(a,si,co) returns 0 and and put the sine of a in si and the cosine cosine of a in co.',
                         ],
         'param_0' : ['angle in radian'],   
          'special_synopsis' : [
                "template<class A0> inline",
                "typename boost::dispatch::meta::call<tag::sincos(A0 const&,A0 const&)",
                "                                    >::type",
                "sincos(A0 const& a);",
                " ",
                "template<class A0> inline",
                "A0 sincos(A0 const& a,A0,A0& si);",
                " ",
                "template<class A0> inline",
                "int sincos(A0 const& a,A0,A0& si,A0& co);",
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
                 'extern "C" {extern long double cephes_asinl(long double);}',
                 'extern "C" {extern long double cephes_acosl(long double);}'],
             'notes' : [],
             'stamp' : 'modified by jt the 11/02/2011',
            },
         'ranges' : {
             'default' : [['T(-60)', 'T(60)']],
             'real_' : [['-20*nt2::Pi<T>()', '20*nt2::Pi<T>()']],
             'signed_int_' : [['T(-40)', 'T(40)']],
             'unsigned_int_' : [['T(0)', 'T(40)']],
            },
         'specific_values' : {
             'default' : {
                 'nt2::Zero<T>()' : {'result' : ['nt2::Zero<r_t0>()', 'nt2::One<r_t0>()'],'ulp_thresh' : '0.75',},
                },
             'real_' : {
                 '-nt2::Pi<T>()' : {'result' : ['nt2::Zero<r_t0>()', 'nt2::Mone<r_t1>()'],'ulp_thresh' : '0.75',},
                 '-nt2::Pi<T>()/T(2)' : {'result' : ['nt2::Mone<r_t0>()', 'nt2::Zero<r_t1>()'],'ulp_thresh' : '0.75',},
                 '-nt2::Pi<T>()/T(4)' : {'result' : ['-nt2::Sqrt_2o_2<r_t0>()', 'nt2::Sqrt_2o_2<r_t0>()'],'ulp_thresh' : '0.75',},
                 'nt2::Inf<T>()' : {'result' : ['nt2::Nan<r_t0>()', 'nt2::Nan<r_t0>()'],'ulp_thresh' : '0.75',},
                 'nt2::Minf<T>()' : {'result' : ['nt2::Nan<r_t0>()', 'nt2::Nan<r_t0>()'],'ulp_thresh' : '0.75',},
                 'nt2::Nan<T>()' : {'result' : ['nt2::Nan<r_t0>()', 'nt2::Nan<r_t0>()'],'ulp_thresh' : '0.75',},
                 'nt2::Pi<T>()' : {'result' : ['nt2::Zero<r_t0>()', 'nt2::Mone<r_t1>()'],'ulp_thresh' : '0.75',},
                 'nt2::Pi<T>()/T(2)' : {'result' : ['nt2::One<r_t0>()', 'nt2::Zero<r_t0>()'],'ulp_thresh' : '0.75',},
                 'nt2::Pi<T>()/T(4)' : {'result' : ['nt2::Sqrt_2o_2<r_t0>()', 'nt2::Sqrt_2o_2<r_t0>()'],'ulp_thresh' : '0.75',},
                 'nt2::Zero<T>()' : {'result' : ['nt2::Zero<r_t0>()', 'nt2::One<r_t0>()'],'ulp_thresh' : '0.75',},
                },
             'signed_int_' : {
                 'nt2::Zero<T>()' : {'result' : ['nt2::Zero<r_t0>()', 'nt2::One<r_t0>()'],'ulp_thresh' : '0.75',},
                },
            },
         'verif_test' : {
             'property_call' : {
                 'real_' : ['nt2::sincos(a0)'],
                },
             'property_value' : {
                 'real_' : [['(T)::sinl(a0)', '(T)::cosl(a0)']],
                },
             'ulp_thresh' : {
                 'real_' : ['0.5'],
                },
            },
        },
    },
]
