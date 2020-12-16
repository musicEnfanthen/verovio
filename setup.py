#!/usr/bin/env python

"""
setup.py file for Verovio
"""

from glob import glob
import os
import platform
from setuptools import setup, Extension
from setuptools.command.sdist import sdist as _sdist
from setuptools.command.build_ext import build_ext as _build_ext


# Utility function to call tools/get_git_commit.sh on any platform
def get_commit():
    if os.path.exists("./tools"):
        print("Running tools/get_git_commit.sh")
        os.system("bash -c 'cd tools; ./get_git_commit.sh'")
        # if platform.system() == "Windows":
        #     os.system("bash -c 'cd tools; ./get_git_commit.sh'")
        # else:
        #     os.system("cd tools; ./get_git_commit.sh")
    else:
        print("Can't change to tools directory")

# There is no task common to both sdist and bdist_wheel, so we override both commands to
# generate the git version header file
class sdist(_sdist):
    def run(self):
        # generate the git commit include file
        get_commit()
        _sdist.run(self)

class build_ext(_build_ext):
    def run(self):
        # generate the git commit include file
        get_commit()
        _build_ext.run(self)

# Utility function to read the README file into the long_description.
with open('README.md', 'r') as fh:
    long_description = fh.read()

# extra compile arguments
EXTRA_COMPILE_ARGS = ['-DPYTHON_BINDING']
if platform.system() != 'Windows':
    EXTRA_COMPILE_ARGS += ['-std=c++17',
                           '-Wno-write-strings', '-Wno-overloaded-virtual']
else:
    EXTRA_COMPILE_ARGS += ['/std:c++17',
                           '-DNO_PAE_SUPPORT']

verovio_module = Extension('verovio._verovio',
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
                                       'bindings/python/verovio.i'],
                           swig_opts=['-c++', '-outdir', 'verovio'],
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
      cmdclass={'sdist': sdist, 'build_ext': build_ext},
      version='3.1.0-dev',
      url="https://www.verovio.org",
      description="""A library and toolkit for engraving MEI music notation into SVG""",
      long_description=long_description,
      long_description_content_type="text/markdown",
      ext_modules=[verovio_module],
      packages=['verovio',
                'verovio.data',
                'verovio.data.Bravura',
                'verovio.data.Gootville',
                'verovio.data.Leipzig',
                'verovio.data.Petaluma',
                'verovio.data.text'],
      package_dir={'verovio.data': 'data'},
      package_data={
          'verovio.data': [f for f in os.listdir('./data') if f.endswith(".xml")],
          'verovio.data.Bravura': os.listdir('./data/Bravura'),
          'verovio.data.Gootville': os.listdir('./data/Gootville'),
          'verovio.data.Leipzig': os.listdir('./data/Leipzig'),
          'verovio.data.Petaluma': os.listdir('./data/Petaluma'),
          'verovio.data.text': os.listdir('./data/text'),
      }
      )
