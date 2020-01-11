"""
SCons command line interface
"""

from SCons.Script import *


def cli_init():
    AddOption("--project", metavar="<directory path>", default="lpc40xx_freertos", help="Specify a target project directory to build")
    AddOption("--verbose", dest="verbose", action="store_true", default=False)
    AddOption("--no-format", dest="no_format", action="store_true", default=False)
    AddOption("--no-unittest", "--no-ut", dest="no_unittest", action="store_true", default=False)
