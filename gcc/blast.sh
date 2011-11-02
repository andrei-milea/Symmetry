#!/bin/bash



make 2>&1 | perl real_errors.pl;cat

