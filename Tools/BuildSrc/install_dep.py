import sys
from importlib import import_module
import subprocess
import site
import os
import platform
import sysconfig


def get_local_site_packages(prefix):
    local_deps_path = os.path.join(prefix, 'Lib', 'site-packages')
    # Only default Windows Python installation (not including MinGW installation) install Python module under Lib\site-packages.
    if platform.system() != "Windows" or sysconfig.get_platform() == "mingw":
        local_deps_path = os.path.join(prefix, 'lib', 'python{major}.{minor}'.format(
            major=platform.python_version_tuple(
            )[0], minor=platform.python_version_tuple()[1]
        ), 'site-packages')
    return local_deps_path


def add_local_site_packages_to_path(prefix):
    local_deps_path = get_local_site_packages(prefix)
    if not os.path.exists(local_deps_path):
        os.makedirs(local_deps_path)
    if local_deps_path not in sys.path:
        sys.path.insert(0, local_deps_path)


def install_pip(prefix, verbose=False):
    try:
        add_local_site_packages_to_path(prefix)
        import_module('pip')
        return True
    except (ModuleNotFoundError, ImportError):
        install_location_args = ['--prefix', prefix]
        script_dir = os.path.dirname(os.path.abspath(__file__))
        cmd = [sys.executable, os.path.join(
            script_dir, 'get-pip.py'), '--ignore-installed'] + install_location_args
        ret = 0
        if not verbose:
            with open(os.devnull, "w") as f:
                ret = subprocess.call(cmd, stdout=f, stderr=subprocess.STDOUT)
        else:
            ret = subprocess.call(cmd)
        if ret != 0:
            raise subprocess.CalledProcessError(ret, cmd)
        add_local_site_packages_to_path(prefix)
        return False


def install_package(package, prefix, verbose=False):
    try:
        add_local_site_packages_to_path(prefix)
        import_module(package)
        return True
    except (ModuleNotFoundError, ImportError):
        install_pip(prefix, verbose=verbose)
        new_env = os.environ.copy()
        if "PYTHONPATH" in new_env:
            new_env["PYTHONPATH"] += os.pathsep + \
                get_local_site_packages(prefix)
        else:
            new_env["PYTHONPATH"] = get_local_site_packages(prefix)
        install_location_args = ['--prefix', prefix]
        cmd = [sys.executable, '-m', 'pip', 'install',
               '--ignore-installed'] + install_location_args + [package]
        ret = 0
        if not verbose:
            with open(os.devnull, "w") as f:
                p = subprocess.Popen(
                    cmd, stdout=f, stderr=subprocess.STDOUT, env=new_env)
                ret = p.wait()
        else:
            p = subprocess.Popen(cmd, env=new_env)
            ret = p.wait()
        if ret != 0:
            raise subprocess.CalledProcessError(ret, cmd)
        add_local_site_packages_to_path(prefix)
        return False
