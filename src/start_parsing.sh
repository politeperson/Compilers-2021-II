#!/usr/bin/env bash

cd sintax_analysis
source S_lang/bin/activate
python3 -m pip install pygraphviz
python3 compile.py "$1" "$2" "$3"
deactivate

# echoing
echo "Parsing done..."
echo "Enter [sintax_analysis/results] folder"
echo "Check file [$2] and [$3] to see the results :)"

