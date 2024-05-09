#!/bin/bash

library_path="$(pwd)/library"
cp_algorithms_path="$(pwd)/cp_algorithms"

rm -rf "${cp_algorithms_path}"
rm -rf tmp_cp_algorithms_library

mkdir -p "${cp_algorithms_path}"
mkdir -p tmp_cp_algorithms_library

pushd tmp_cp_algorithms_library

    curl https://github.com/ajami1331/cp-algorithms-aux/zipball/master -L -o cp_algorithms_library.zip

    unzip cp_algorithms_library.zip

    rm -rf cp_algorithms_library.zip

    pushd ./ajami1331-cp-algorithms-aux-*

        pushd ./cp-algo
            
            cp -r . "${cp_algorithms_path}"

        popd
        
        cp LICENSE "${cp_algorithms_path}"
        cp README.md "${cp_algorithms_path}"

    popd

popd

pwd
rm -rf tmp_cp_algorithms_library
