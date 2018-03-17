# Root SConstruct
import os

platform = ARGUMENTS.get('OS', Platform())
# execute with "scons -Q OS=linux"

# libdir = "#build/$PLATFORM/lib"

incdir = "#build/inc"
libdir = "#build/lib"
bindir = "#build/bin"

cpppath = os.environ['FFTW_INC']
libpath = os.environ['FFTW_LIB']
cc = os.environ['CC']
cflags = (
        " -O3 -std=c99 -fPIC -DHAVE_INLINE "
        " -Wall -Wextra "
        " -msse2 -msse "
        " -fopenmp -DSF_HAS_FFTW -DSF_HAS_FFTW_OMP "
        )

AddOption('--prefix',
          dest='prefix',
          type='string',
          nargs=1,
          action='store',
          metavar='DIR',
          help='installation prefix')

env = Environment(PREFIX = GetOption('prefix'),
                  PLATFORM = platform,
                  BINDIR = bindir,
                  INCDIR = incdir,
                  LIBDIR = libdir,
                  CPPPATH = cpppath,
                  LIBPATH = libpath,
                  CC = cc,
                  CFLAGS = cflags)
env['SHLIBPREFIX'] = ''
env.Append(CPPPATH=Glob('inc'))
env.Append(LIBPATH=[libdir])

# build library
libs = SConscript('src/SConscript', exports='env', variant_dir='build/lib', duplicate=0)

# build testing programs
exes = SConscript('tests/SConscript', exports='env', variant_dir='build/tests', duplicate=0)

env.Alias("install_libs", env.Install('$PREFIX/lib', libs))
env.Alias("install_exes", env.Install('$PREFIX/bin', exes))
env.Alias('install_header', env.Command('$PREFIX/inc/hilbertf.h','./inc/hilbertf.h',Copy("$TARGET","$SOURCE")))
env.Alias('install', ['install_libs', 'install_exes', 'install_header'])

