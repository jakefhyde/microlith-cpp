# Configuration file for the Sphinx documentation builder.
#
# This file only contains a selection of the most common options. For a full
# list see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Path setup --------------------------------------------------------------


# -- Project information -----------------------------------------------------

project = 'Microlith'
copyright = '2021, dragozir'
author = 'dragozir'

release = '0.0.5'

# -- General configuration ---------------------------------------------------

extensions = [
    'breathe',
    'exhale'
]

# Setup the breathe extension
breathe_projects = {
    "Microlith": "../build/doxyoutput/xml"
}
breathe_default_project = "Microlith"

exhale_args = {
    # These arguments are required
    "containmentFolder":     "./api",
    "rootFileName":          "library_root.rst",
    "rootFileTitle":         "Library API",
    "doxygenStripFromPath":  "../../include",
    "createTreeView":        True,
    "exhaleExecutesDoxygen": True,
    "exhaleUseDoxyfile": True
}

primary_domain = 'cpp'

highlight_language = 'cpp'

templates_path = ['_templates']

exclude_patterns = []

# -- Options for HTML output -------------------------------------------------

html_theme = 'sphinx_rtd_theme'

html_static_path = ['_static']
