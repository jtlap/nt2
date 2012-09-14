[ ## this file was manually modified by jt
    {
     'functor' : {
          'description':['Complete elliptic integrals of first and second kind',
                         '\\\\arg k = ellipke(m) returns the complete elliptic integral of the first kind of m.',
                         '\\\\arg tie(k,e) = ellipke(m) returns the complete elliptic integral of the first and second kinds.',
                         '\\\\arg tie(k,e) = ellipke(m,tol) computes the complete elliptic integral to accuracy tol.',
                         ' The default is Eps<A0>()',
                         'tol allows a compromise between less accurate but more quickly computed answer.','\par',
                         'the function also be called as indicated in the synopsis: ellipke(m,tol,k,e)'],
            'max_arity' : '4',
            'param_0' : ['outside of \f$[0,1]\f$ the result is nan'],
            'param_1' : ['optional tolerance'],
            'param_2' : ['if present, first kind result'],
            'param_3' : ['if present, second kind result'],
            'return'  : ['depends of the parameter number'],
          'special_synopsis' : [
                "template<class A0> inline",
                "typename boost::dispatch::meta::call<tag::ellipke_(A0 const&,A0 const&)",
                "                                    >::type",
                "ellipke(A0 const& m,A0 const& tol=Eps<A0>());",
                " ",
                "template<class A0> inline",
                "int ellipke(A0 const& m,A0 const& tol,A0& k,A0&e);",
                 ],
            'arity' : '1',
         'call_types' : ['T'],
         'ret_arity' : '2',
         'rturn' : {
             'default' : 'rtype',
            },
         'simd_types' : ['real_'],
         'type_defs' : 
            ['typedef typename boost::dispatch::meta::as_floating<T>::type etype;',
             'typedef boost::fusion::tuple<etype,etype> rtype;'],
         'types' : ['real_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'created  by jt the 21/02/2011',
             'included' : 
                ['extern "C" {long double cephes_ellikl(long double,long double);}',
                 '#include <nt2/toolbox/trigonometric/constants.hpp>'],
             'notes' : [],
             'stamp' : 'modified by jt the 21/02/2011',
            },
         'ranges' : {
             'real_' : [['T(0)', 'T(1)']],
            },
         'specific_values' : {
             'real_' : {
                 'nt2::One<T>()' : {'result' : ['nt2::Inf<r_t0>()','nt2::One<r_t1>()'],'ulp_thresh' : '0.5',},
                 'nt2::Zero<T>()' : {'result' : ['nt2::Pio_2<r_t0>()', 'nt2::Pio_2<r_t1>()'],'ulp_thresh' : '0.5',},
                },
            },
         'verif_test' : {
            },
        },
    },
    {
     'functor' : {
         'arity' : '2',
         'call_types' : ['T','scalar'],
         'ret_arity' : '2',
         'rturn' : {
             'default' : 'rtype',
            },
         'simd_types' : ['real_'],
         'type_defs' : 
            [   'typedef T scalar;',
                'typedef typename boost::dispatch::meta::as_floating<T>::type etype;',
             'typedef boost::fusion::tuple<etype,etype> rtype;'],
         'types' : ['real_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'created  by jt the 21/02/2011',
             'included' : 
                ['extern "C" {long double cephes_ellikl(long double,long double);}',
                 '#include <nt2/toolbox/trigonometric/constants.hpp>'],
             'notes' : [],
             'stamp' : 'modified by jt the 21/02/2011',
            },
         'ranges' : {
             'real_' : [['T(0)', 'T(1)'], ['T(0)', 'T(0.01)']],
            },
         'specific_values' : {
             'default' : {
                 'nt2::One<T>(),nt2::Eps<scalar>()' : {'result' : ['nt2::Inf<r_t0>()','nt2::One<r_t1>()'],'ulp_thresh' : '0.5',},
                 'nt2::Zero<T>(),nt2::Eps<scalar>()' : {'result' : ['nt2::Pio_2<r_t0>()', 'nt2::Pio_2<r_t1>()'],'ulp_thresh' : '0.5',},
                },
            },
         'verif_test' : {
            },
        },
    },
]
