#!/bin/bash

library_path="$(pwd)/library"
kactl_path="$(pwd)/kactl"

rm -rf "${kactl_path}"
rm -rf tmp_kactl_library

mkdir -p "${kactl_path}"
mkdir -p tmp_kactl_library

pushd tmp_kactl_library

    curl https://github.com/ajami1331/kactl/zipball/master -L -o kactl_library.zip

    unzip kactl_library.zip

    rm -rf kactl_library.zip

    pushd ./ajami1331-kactl-*

        pushd ./content
            sed -i 's/sz(/szx(/g' **/*.h
            cp -r . "${kactl_path}"

        popd
        
        cp README.md "${kactl_path}"

    popd

popd

pwd
rm -rf tmp_kactl_library
