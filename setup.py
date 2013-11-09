#!/usr/bin/env python2
# -*- coding: utf-8 -*-

from distutils.core import setup
from distutils.extension import Extension
from Cython.Distutils import build_ext
import os

setup (
    cmdclass = {'build_ext': build_ext } ,
    ext_modules = [Extension ("fester.integrate", ["fester/integrate.pyx", "fester/qeo_types.c", "fester/main2.c", "fester/QGauge_NetStatMessage.c"],
    extra_compile_args=['-g', '-Wall',  '-I%s/c/include' % os.environ['QEO_HOME']],
    libraries=['rt','qeo', 'qeoutil', 'pthread'],
    library_dirs=['%s/c/lib/arm-linux-gnueabihf' % os.environ['QEO_HOME']])]
)
