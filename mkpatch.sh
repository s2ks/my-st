#!/bin/bash

FILES="Makefile config.mk config.def.h arg.h st.1 st.c st.desktop \
	st.h st.info x.c win.h exception.h"
DIFF=$(git diff 0.8.4 master $FILES)

echo "$(sha256sum <<< $DIFF)" 1>&2
echo "$DIFF"
