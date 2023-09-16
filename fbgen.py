#!/usr/bin/env python
# encoding: utf-8

"""
Utility script to generate/modify Firebreath plug-in projects.
...
"""

import os
import sys
import time
from fbgen.gen_templates import *
import argparse

try:
    from configparser import SafeConfigParser
except ImportError:
    from ConfigParser import SafeConfigParser


def get_template_files(base_path):
    """
    Obtains the location to the template files. Discovers any newly added files
    automatically.
    """
    files = []
    for filename in os.listdir(base_path):
        tmp_name = os.path.join(base_path, filename)
        if os.path.isdir(tmp_name):
            files.extend(get_template_files(tmp_name))
        else:
            files.append(tmp_name.replace(base_path + os.path.sep, ''))
    return files


def create_dir(dir_name):
    """
    Creates a directory, even if it has to create parent directories to do so
    """
    os.makedirs(dir_name, exist_ok=True)


def main():
    """
    Parse the commandline and execute the appropriate actions.
    """

    # Define the command-line interface via argparse
    parser = argparse.ArgumentParser()
    parser.add_argument("-p", "--plugin-name", dest="plugin_name")
    parser.add_argument("-i", "--plugin-identifier", dest="plugin_ident")
    parser.add_argument("-c", "--company-name", dest="company_name")
    parser.add_argument("-d", "--company-domain", dest="company_domain")
    parser.add_argument("-g", "--disable-gui", dest="disable_gui", action="store_true")
    options = parser.parse_args()

    options.interactive = not all([options.plugin_name, options.plugin_ident, options.company_name, options.company_domain])

    script_dir = os.path.dirname(os.path.abspath(__file__))
    cfg_filename = os.path.join(script_dir, ".fbgen.cfg")
    cfg_file = SafeConfigParser()
    cfg_file.read(cfg_filename)

    # Instantiate the appropriate classes
    plugin = Plugin(name=options.plugin_name, ident=options.plugin_ident, disable_gui=options.disable_gui)
    plugin.read_cfg(cfg_file)
    company = Company(name=options.company_name)
    company.read_cfg(cfg_file)

    if options.interactive:
        try:
            plugin.prompt_values()
            company.prompt_values()
        except KeyboardInterrupt:
            print("\nInterrupted by user.")
            sys.exit(0)

    plugin.update_cfg(cfg_file)
    company.update_cfg(cfg_file)
    guid = GUID(ident=plugin.ident, domain=company.domain)

    # Generate the guids needed by the templates
    generated_guids = AttrDictSimple()
    generated_guids.GUIDS_TYPELIB = guid.generate("TYPELIB")
    generated_guids.GUIDS_CONTROLIF = guid.generate("CONTROLIF")
    generatedGuids.GUIDS_CONTROL = guid.generate("CONTROL")
    generatedGuids.GUIDS_JSIF = guid.generate("JSIF")
    generatedGuids.GUIDS_JSOBJ = guid.generate("JSOBJ")
    generatedGuids.GUIDS_EVTSRC = guid.generate("EVTSRC")
    generatedGuids.GUIDS_INSTPROD = guid.generate("INSTPROD")
    generatedGuids.GUIDS_INSTUPGR = guid.generate("INSTUPGR")
    generatedGuids.GUIDS_INSTUPGR64 = guid.generate("INSTUPGR64")
    generatedGuids.GUIDS_companydircomp = guid.generate("companydircomp")
    generatedGuids.GUIDS_installdircomp = guid.generate("installdircomp")

    template_time = AttrDictSimple(YEAR=time.strftime("%Y"))

    with open(cfg_filename, "w") as f:
        cfg_file.write(f)

    base_path = os.path.join(script_dir, "projects")
    if not os.path.isdir(base_path):
        create_dir(base_path)

    proj_path = os.path.abspath(os.path.join(base_path, f"{plugin.ident}"))
    if os.path.isdir(proj_path):
        try:
            overwrite = input("\nDirectory already exists. Continue anyway? [y/N]")
        except KeyboardInterrupt:
            print("\nInterrupted by user.")
            sys.exit(0)
        if not overwrite or overwrite[0].lower() != "y":
            print("\nAborting")
            sys.exit(1)
    else:
        create_dir(proj_path)

    print("\nProcessing templates")
    src_dir = os.path.join(script_dir, "fbgen", "src")
    template_files = get_template_files(src_dir)
    for tpl in template_files:
        try:
            tpl_path, tpl_filename = os.path.split(tpl)
            if tpl_filename.startswith("Template"):
                tpl_filename = tpl_filename.replace("Template", plugin.ident, 1)
            filename = os.path.join(proj_path, tpl_path, tpl_filename)
            if not os.path.isdir(os.path.dirname(filename)):
                create_dir(os.path.dirname(filename))
            tpl_file = os.path.join("fbgen", "src", tpl)
            print(tpl_file)
            # Special case for binary files
            if tpl_filename == "background.png":
                with open(tpl_file, "rb") as input_file, open(filename, "wb") as output:
                    output.write(input_file.read())
            else:
                template = Template(tpl_file)
                with open(filename, "w") as f:
                    f.write(template.process(plugin, company, guid, generated_guids, template_time))
            print(f"  Processed {tpl}")
        except Exception as e:
            print(f"  Error processing {tpl}: {e}")
            raise
    print(f"Done. Files placed in {proj_path}")

if __name__ == "__main__":
    main()
