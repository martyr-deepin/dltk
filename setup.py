#! /usr/bin/env python

from setuptools import setup, Extension
import os
import commands

def pkg_config_cflags(pkgs):
    '''List all include paths that output by `pkg-config --cflags pkgs`'''
    return map(lambda path: path[2::], commands.getoutput('pkg-config --cflags-only-I %s' % (' '.join(pkgs))).split())

calendar_mod = Extension('dltk_calendar',
                include_dirs = pkg_config_cflags(['dltk+-2.0', 'pygtk-2.0']),
                libraries = ['dltk-2.0'],
                sources = ['./binding/dltk_calendar_python.c'])

setup(name='dltk',
      version='0.1',
      ext_modules = [calendar_mod],
      description='Python Binding for Deepin Linux toolkit.',
      long_description ="""Python Binding for Deepin Linux toolkit.""",
      author='Linux Deepin Team',
      author_email='zhaixiang@linuxdeepin.com',
      license='GPL-3',
      url="https://github.com/linuxdeepin/dltk",
      download_url="git://github.com/linuxdeepin/dltk.git",
      platforms = ['Linux'],
      packages = ['dltk'],
      )

