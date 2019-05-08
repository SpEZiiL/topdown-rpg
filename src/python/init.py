# src/python/init.py
#
# Initial Python script that gets called from the C++ code before the main
# script gets called.
#
# Since:
#     2019-02-15
__version__ ="2019-02-15"
__author__ ="Michael Federczuk"

import sys
import game

if not hasattr(sys, 'argv'):
	sys.argv = [game.exe_path]
#end if

sys.path.append(game.scripts_path)

del sys
del game
