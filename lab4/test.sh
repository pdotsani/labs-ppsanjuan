#!/usr/bin/env bash

./lookup badkey ': ' /proc/meminfo
./lookup MemAvailable 'baddelim' /proc/meminfo
./lookup MemAvailable ': ' /proc/meminfo 
./lookup Percpu ': ' /proc/meminfo 