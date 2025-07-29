#!/usr/bin/env bash

set -e

# the nanopb tool seems to require that the .options file be in the current directory!

echo "Generating protobufs for Nova Core"
cd protobufs
../bin/nanopb/nanopb-0.4.7-macosx-x86/generator-bin/protoc --nanopb_out=-v:../nova\ core/src/net/generated/ -I=../protobufs ../protobufs/*.proto --experimental_allow_proto3_optional


echo "Copying protobufs to Nova Core"
cp ../nova\ core/src/net/generated/* ../nova\ star/src/net/generated/
