#!/bin/bash
export LD_LIBRARY_PATH=.:${LD_LIBRARY_PATH}

# calling the binary with the apropriate parameters
./xmfc $@