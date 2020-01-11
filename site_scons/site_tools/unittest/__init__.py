"""
Unit test using Unity + CMock
"""

import os
import subprocess

from SCons.Script import *

import fsops
import osops

SELF_DIRNODE = Dir(os.path.dirname(__file__))

UNITTEST_SOURCE_FILE = SELF_DIRNODE.File("throw_the_switch/unity/src/unity.c")

UNITTEST_INCLUDE_DIRS = [
    SELF_DIRNODE.Dir("throw_the_switch/unity/src")
]

OBJ_DIRNAME = "obj"
EXE_DIRNAME = "exe"


"""
SCons tools functions
"""


def generate(env):
    env.AddMethod(unittest_method, "Test")


def exists():
    return True


"""
Environment functions
"""

def unittest_method(env, source, target, verbose=False):
    # if isinstance(node, Dir):
    env_ut = get_unittest_env(env)
    env_ut_coverage = get_unittest_coverage_env(env)

    env_ut_coverage["CPPPATH"].append(Dir("{}/..".format(os.path.dirname(source.abspath))))

    obj_filenodes = []
    obj_filenodes += env_ut_coverage.Object(source=source, target=fsops.ch_target_filenode(source, target.Dir(OBJ_DIRNAME), "o"))
    obj_filenodes += env_ut.Object(source=fsops.suffix_filenode_name(source, "_runner"), target=fsops.ch_target_filenode(fsops.suffix_filenode_name(source, "_runner"), target.Dir(OBJ_DIRNAME), "o"))
    obj_filenodes += env_ut.Object(source=UNITTEST_SOURCE_FILE, target=fsops.ch_target_filenode(UNITTEST_SOURCE_FILE, target.Dir(OBJ_DIRNAME), "o"))
    exe_filenodes = env_ut_coverage.Program(source=obj_filenodes, target=fsops.ch_target_filenode(source, target.Dir(EXE_DIRNAME), "exe"))
    return exe_filenodes


"""
Helper methods
"""


def get_unittest_env(source_env):
    env_ut = source_env.Clone()

    # Define custom macro
    env_ut["CPPDEFINES"].append("UNIT_TEST=1")

    # Add include paths
    env_ut["CPPPATH"].extend(UNITTEST_INCLUDE_DIRS)

    return env_ut

def get_unittest_coverage_env(source_env):
    env_ut = get_unittest_env(source_env)

    # Add compiler flags
    c_flags = [
        "-fprofile-arcs",
        "-ftest-coverage",
        "-g",
        "-O0",
    ]
    env_ut["CFLAGS"].extend(c_flags)
    env_ut["CXXFLAGS"].extend(c_flags)

    # Link other libraries
    env_ut["LIBS"].append("gcov")

    return env_ut


# def search_for_tests(dirnode):
#     for dirpath, dirnames, filenames in os.walk(os.path.relpath(dirnode.abspath)):


