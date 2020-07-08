#!/usr/bin/env python
#-*- coding: utf-8 -*-

import os
import sys
import subprocess
import inspect
import multiprocessing
import shutil
import getpass

config = {
    'display_name': 'audiobook',
    'logToFile': False,
    'path': {
        'cwd': os.path.abspath(os.getcwd()),
        'bin': os.path.abspath('./build/src/audiobook'),
        'build': os.path.abspath('./build/'),
        'binary': os.path.abspath('audiobook'),
    },
}


def main():
    menu = {}
    menu['1'] = ['Build release', 'build_release']
    menu['2'] = ['Build debug', 'build_debug']
    menu['3'] = ['Run desktop', 'run_desktop']
    menu['4'] = ['Run mobile', 'run_mobile']
    menu['5'] = ['Debug (GDB)', 'debug']
    menu['p'] = ['pkgbuild', 'pkgbuild']
    menu['0'] = ['Requirements', 'requirements']

    print('\n********************')
    print ('    {}'.format(config['display_name']))
    print('********************')
    for item in menu:
        print (' ' + item + '. ' + menu[item][0])
        
    selection = input('> ')
    # check if in menu
    if selection in menu:
        eval(menu[selection][1] + '()')

    # exec function
    if '()' in selection:
        eval(selection)

    main()
    return


def pkgbuild():
    log('create .srcinfo')
    run('makepkg --printsrcinfo > .SRCINFO')
    log('install')
    run('makepkg -f')
    return


def run_desktop():
    try:
        run('''
        cd build/src
        ./qweather
        ''')
    except KeyboardInterrupt:
        log('exit')
    
    return


def run_mobile():
    try:
        run('''
        cd build/src
        QT_QUICK_CONTROLS_MOBILE=true QT_QUICK_CONTROLS_STYLE=Plasma ./qweather
        ''')
    except KeyboardInterrupt:
        log('exit')
    
    return


def debug():
    run('''
    cd build/src
    gdb qweather
    ''')
    return


def build_debug():
    run('''
    mkdir -p build
    cd build
    cmake .. -DDEFINE_DEBUG=ON -DCMAKE_BUILD_TYPE=Debug
    make
    cd ..
    ''')
    return
    

def build_release():
    run('''
    mkdir -p build
    cd build
    cmake .. -DCMAKE_INSTALL_PREFIX=/usr -DCMAKE_BUILD_TYPE=Release
    make
    sudo make install
    ''')
    return


def requirements():
    run('''
    yay -S --noconfirm --needed cmake extra-cmake-modules gdb
    ''')
    return


def log(str=''):
    print(str)
    if not config['logToFile']:
        return

    with open("log.txt", "a") as f:
        f.write(str + '\n')
    return
    

# run commands
# params:
# cwd
# show cmd
def run(command, params = {}):
    # clean command
    cmd = inspect.cleandoc(command)
    
    # show output
    show_cmd = False
    if 'show_cmd' in params:
        show_cmd = params['show_cmd']

    if show_cmd:
        print(cmd + '\n')
        
    working_dir = os.getcwd()
    if 'cwd' in params:
        working_dir = params['cwd']
        
    # exec
    subprocess.run(cmd, shell=True, cwd=working_dir)
    return


def run_sudo(command, params = {}):
    cmd = inspect.cleandoc(command)
    password = getpass.getpass('[sudo] password: ')
    cmd = 'echo {}|sudo -S {}'.format(password, cmd)
    run(cmd, params)
    return


if __name__ == '__main__':
    os.system('cls||clear')
    main()
