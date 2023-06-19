#!/usr/bin/env bash

set -e

# the nanopb tool seems to require that the .options file be in the current directory!

./nanopb/nanopb-0.4.7-macosx-x86/generator-bin/protoc --nanopb_out=-v:../src/net/generated/ -I=../protobufs ../protobufs/*.proto --experimental_allow_proto3_optional

