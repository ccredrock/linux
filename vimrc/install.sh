#!/usr/bin/env bash

# Copyright 2014 Steve Francia

# ==============================================================================
debug_mode='0'

APP_PATH=$(cd "$(dirname "$0")" && pwd)
[ -z "$REPO_URI" ] && REPO_URI='https://github.com/ccredrock/rock_vim.git'
[ -z "$VUNDLE_URI" ] && VUNDLE_URI="https://github.com/gmarik/vundle.git"

# ==============================================================================
msg() {
    printf '%b\n' "$1" >&2
}

success() {
    if [ "$ret" -eq '0' ]; then
        msg "\33[32m[✔]\33[0m ${1}${2}"
    fi
}

error() {
    msg "\33[31m[✘]\33[0m ${1}${2}"
    exit 1
}

debug() {
    if [ "$debug_mode" -eq '1' ] && [ "$ret" -gt '1' ]; then
        msg "An error occurred in function \"${FUNCNAME[$i+1]}\" on line ${BASH_LINENO[$i+1]}, we're sorry for that."
    fi
}

program_exists() {
    local ret='0'
    type $1 >/dev/null 2>&1 || { local ret='1'; }

    # throw error on non-zero return value
    if [ ! "$ret" -eq '0' ]; then
        error "You must have '$1' installed to continue."
    fi
}

variable_set() {
    if [ -z "$1" ]; then
        error "You must have your HOME environmental variable set to continue."
    fi
}

lnif() {
    if [ -e "$1" ]; then
        ln -sf "$1" "$2"
    fi
    ret="$?"
    debug
}

# ==============================================================================
do_backup() {
    if [ -e "$1" ] || [ -e "$2" ] || [ -e "$3" ]; then
        msg "Attempting to back up your original vim configuration."
        today=`date +%Y%m%d_%s`
        for i in "$1" "$2" "$3"; do
            [ -e "$i" ] && [ ! -L "$i" ] && mv -v "$i" "$i.$today";
        done
        ret="$?"
        success "Your original vim configuration has been backed up."
        debug
   fi
}

sync_repo() {
    local repo_path="$1"
    local repo_uri="$2"
    local repo_branch="$3"
    local repo_name="$4"

    msg "Trying to update $repo_name"

    if [ ! -e "$repo_path" ]; then
        mkdir -p "$repo_path"
        git clone -b "$repo_branch" "$repo_uri" "$repo_path"
        ret="$?"
        success "Successfully cloned $repo_name."
    else
        cd "$repo_path" && git pull origin "$repo_branch"
        ret="$?"
        success "Successfully updated $repo_name"
    fi

    debug
}

create_symlinks() {
    local source_path="$1"
    local target_path="$2"

    lnif "$source_path/vimrc"         "$target_path/.vimrc"
    lnif "$source_path/vimrc.before"  "$target_path/.vimrc.before"
    lnif "$source_path/vimrc.bundles" "$target_path/.vimrc.bundles"

    ret="$?"
    success "Setting up vim symlinks."
    debug
}

setup_vundle() {
    vim "+BundleInstall!" \
        "+BundleClean"

    success "Now updating/installing plugins using Vundle"
    debug
}

# ==============================================================================
variable_set "$HOME"
program_exists  "vim"
program_exists  "git"

do_backup       "$HOME/.vim" \
                "$HOME/.vimrc" 

create_symlinks "$APP_PATH" \
                "$HOME"

sync_repo       "$HOME/.vim/bundle/vundle" \
                "$VUNDLE_URI" \
                "master" \
                "vundle"

setup_vundle    "$HOME/.vimrc.bundles"

msg             "\nThanks for installing $app_name."
