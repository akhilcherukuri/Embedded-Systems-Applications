from __future__ import print_function
from argparse import ArgumentParser
import os
import subprocess
import sys

from nxpprog import NXPPROG_PY

SELF_DIRPATH = os.path.dirname(__file__)
REPO_ROOT_DIRPATH = os.path.join(SELF_DIRPATH, "..")
DEFAULT_BIN_FILEPATH = os.path.join(REPO_ROOT_DIRPATH, "_build_lpc40xx_freertos", "lpc40xx_freertos.bin")

FAILURE = r"""
_____ _    ___ _    _   _ ____  _____
|  ___/ \  |_ _| |  | | | |  _ \| ____|
| |_ / _ \  | || |  | | | | |_) |  _|
|  _/ ___ \ | || |__| |_| |  _ <| |___
|_|/_/   \_\___|_____\___/|_| \_\_____|
"""

SUCCESS = r"""
 ____  _   _  ____ ____ _____ ____ ____
/ ___|| | | |/ ___/ ___| ____/ ___/ ___|
\___ \| | | | |  | |   |  _| \___ \___ \
 ___) | |_| | |__| |___| |___ ___) |__) |
|____/ \___/ \____\____|_____|____/____/
"""


def get_args():
    arg_parser = ArgumentParser(description=r"Example usage: python flash.py -p COM6 -i ..\_build\sjtwo-c.bin")
    arg_parser.add_argument(
        "-i", "--input",
        metavar="<FILE>",
        type=str,
        help="File path of firmware (.bin) to flash onto target",
        default=None,
    )
    # This argument is an optional argument. You may or may not pass
    # If you are not sure on what COM port your LPC40xx controller is connected to,
    # do not pass any argument. It shall then consider the default argument
    # and the script shall automatically detect the controller i.e. LPC40xx
    # How to use : 
    # python flash.py -i ../_build_lpc40xx_freertos/lpc40xx_freertos.bin
    #                               OR
    # python flash.py -p /dev/ttyUSB0 -i ../_build_lpc40xx_freertos/lpc40xx_freertos.bin
    arg_parser.add_argument(
        "-p", "--port",             
        metavar="<COM PORT>",
        type=str,
        help="USB to Serial COM port (i.e. COM6 or /dev/ttyUSB0 or /dev/cu.SLAB_USBtoUART)",
        default="",         
    )
    arg_parser.add_argument(
        "-v", "--verbose",
        action="store_true"
    )

    args = arg_parser.parse_args()

    """
    Perform sanity checks against arguments
    """
    if args.input is None:
        args.input = DEFAULT_BIN_FILEPATH
        if not os.path.isfile(args.input):
            print("Default firmware file [{}] does not exist! Specify firmware file path using `-i` option.".format(os.path.abspath(args.input)))
            sys.exit(1)  # Exit early

    if not args.input.endswith(".bin"):
        print("The input firmware file [{}] must be in .bin format!".format(os.path.abspath(args.input)))
        sys.exit(1)  # Exit early

    return args


def main():
    args = get_args()
    input_filepath = os.path.abspath(args.input)
    com_port = args.port
    verbose = args.verbose

    print("Flashing file [{}] using COM port [{}]".format(input_filepath, com_port))
    sys.stdout.flush()

    cmd = [
        "python",
        NXPPROG_PY,
        "--binary={}".format(input_filepath),
        "--device={}".format(com_port),
    ]
    if verbose:
        print("Using command:\n{}".format(" ".join(cmd)))
        sys.stdout.flush()

    error = subprocess.call(cmd)
    return error


if __name__ == "__main__":
    _error = main()
    if not _error:
        print(SUCCESS)
    else:
        print(FAILURE)
    sys.exit(_error)
