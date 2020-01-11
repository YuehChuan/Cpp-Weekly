#!/usr/bin/env bash

declare -a build_stages=( clean fmt compile execute )

function main() {
  local -r stages=${!1}

  function show_stage_name() {
    local -r color_green='\033[0;32m'
    local -r color_reset='\033[0;0m' 
    printf "${color_green}[${1}]${color_reset}\n"
  }

  function run_stages() {
    for fun in ${stages[@]}; do 
      show_stage_name ${fun}
      make ${fun}
    done
  }

  clear
  run_stages stages[@]
}

main build_stages[@]
