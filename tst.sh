#!/bin/bash
# tst.sh

ASSRT() {
  eval "test $1"

  if [ $? -ne 0 ]; then
    echo "ASSRT ERROR `basename ${BASH_SOURCE[1]}`:${BASH_LINENO[0]}, not true: '$1'" >&2
    exit 1
  fi
}  # ASSRT


./bld.sh ; ASSRT "$? -eq 0"

# "DRO timestamp. E.g. 2024-04-04 12:28:41.254418"
./timefmt -f "L%F %T......."

# "DRO with timezone offset."
./timefmt -f "L%F %T.......%z"

# "DRO UTC."
./timefmt -f "U%F %T.......%z"

# "Store timestamp. E.g. Thu Apr 04 12:28:43 2024"
./timefmt -f "L%a %b %d %T %Y"

