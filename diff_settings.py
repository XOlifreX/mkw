import os

def apply(config, args):
    config['mapfile'] = 'artifacts/target/pal/main.map'
    config['myimg'] = 'artifacts/target/pal/main.dol'
    config['baseimg'] = 'artifacts/orig/pal/main.dol'
    config['makeflags'] = []
    config['source_directories'] = ['source']
    config["arch"] = "ppc"
    config["map_format"] = "mw" # gnu or mw
    config["mw_build_dir"] = "out" # only needed for mw map format
    config["makeflags"] = []
    config["objdump_executable"] = os.environ['DEVKITPPC'] + "/bin/powerpc-eabi-objdump.exe"