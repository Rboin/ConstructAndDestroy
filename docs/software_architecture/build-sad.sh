#!/bin/bash

# Go to this script directory
cd $(dirname ${BASH_SOURCE[0]})

# Build and clean proposal
latexmk -lualatex software_architecture.tex
if [ $? ]; then
  # Building executed with 0 thus we can clean working data
  latexmk -c software_architecture.tex
fi

