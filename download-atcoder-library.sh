#!/bin/bash

library_path="$(pwd)/library"
atcoder_path="$(pwd)/atcoder"

rm -rf "${atcoder_path}"

mkdir -p "${atcoder_path}"
mkdir -p tmp_atcoder_library

pushd tmp_atcoder_library

    curl https://github.com/ajami1331/ac-library/zipball/master -L -o ac-library.zip

    unzip ac-library.zip

    rm -rf ac-library.zip

    pushd ./ajami1331-ac-library-*

        pushd ./atcoder

            sed -i 's/#include \"atcoder\//#include \"/g' *

            cp -r . "${atcoder_path}"

        popd
        
        cp LICENSE "${atcoder_path}"
        cp README.md "${atcoder_path}"

    popd

popd

pwd
rm -rf tmp_atcoder_library
