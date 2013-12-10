#!/bin/sh
javac -d "${HYPERDEX_BUILDDIR}"/test/java "${HYPERDEX_SRCDIR}"/test/java/MultiAttribute.java

python "${HYPERDEX_SRCDIR}"/test/runner.py --space="space kv key k attributes v1, v2" --daemons=1 -- \
    java -Djava.library.path="${HYPERDEX_BUILDDIR}"/.libs MultiAttribute {HOST} {PORT}
