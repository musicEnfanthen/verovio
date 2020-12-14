#!/usr/bin/env python

"""
setup.py file for Verovio
"""

from glob import glob
import os
import platform
from setuptools import setup, Extension

# Utility function to read the README file into the long_description.
with open('README.md', 'r') as fh:
     long_description = fh.read()

# generate the git commit include file
os.system("cd tools; ./get_git_commit.sh")

EXTRA_COMPILE_ARGS = ['-DPYTHON_BINDING']
if platform.system() != 'Windows':
    EXTRA_COMPILE_ARGS += ['-std=c++17',
                           '-Wno-write-strings', '-Wno-overloaded-virtual']
else:
    EXTRA_COMPILE_ARGS += ['/std:c++17',
                           '-DNO_PAE_SUPPORT']

verovio_module = Extension('_verovio',
                           sources=glob('./src/*.cpp') + glob('./src/hum/*.cpp') +
                           [
                               './src/json/jsonxx.cc',
                               './src/pugi/pugixml.cpp',
                               './src/midi/Binasc.cpp',
                               './src/midi/MidiEvent.cpp',
                               './src/midi/MidiEventList.cpp',
                               './src/midi/MidiFile.cpp',
                               './src/midi/MidiMessage.cpp',
                               './libmei/attconverter.cpp',
                               './libmei/atts_analytical.cpp',
                               './libmei/atts_cmn.cpp',
                               './libmei/atts_cmnornaments.cpp',
                               './libmei/atts_critapp.cpp',
                               './libmei/atts_gestural.cpp',
                               './libmei/atts_externalsymbols.cpp',
                               './libmei/atts_facsimile.cpp',
                               './libmei/atts_mei.cpp',
                               './libmei/atts_mensural.cpp',
                               './libmei/atts_midi.cpp',
                               './libmei/atts_neumes.cpp',
                               './libmei/atts_pagebased.cpp',
                               './libmei/atts_shared.cpp',
                               './libmei/atts_visual.cpp',
                               './bindings/python/verovio.i'],
                           swig_opts=['-c++', '-outdir', '.'],
                           include_dirs=['/usr/local/include',
                                         './include',
                                         './include/vrv',
                                         './include/json',
                                         './include/midi',
                                         './include/hum',
                                         './include/pugi',
                                         './include/utf8',
                                         './include/win32',
                                         './libmei'],
                           extra_compile_args=EXTRA_COMPILE_ARGS
                           )

setup(name='verovio',
      version='3.1.0-dev',
      url="https://www.verovio.org",
      description="""A library and toolkit for engraving MEI music notation into SVG""",
      long_description=long_description,
      long_description_content_type="text/markdown",
      ext_modules=[verovio_module],
      py_modules=["verovio"],
      include_package_data=True,
      packages=['data']
      )
