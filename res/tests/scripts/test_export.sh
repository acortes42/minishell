#!/bin/bash

echo "Executing script test_export.sh"
env | grep TEST_EXPORT 
export INTERNAL_VARIABLE="Must not be shown"
