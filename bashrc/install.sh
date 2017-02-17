#!/bin/bash

# CentOS release 6.4 (Final)

# ==============================================================================
USER_NAME=redrock
SPATH=$(cd "$(dirname "$0")" && pwd)

# ==============================================================================
create_user()
{
    useradd $USER_NAME
    passwd $USER_NAME
    sed -i "s/${USER_NAME}:x:.:.:/${USER_NAME}:x:0:0:/g" /etc/passwd
}

bash_syn()
{
    su ?USER_NAME

    ln -s $SPATH/bashrc ~/.bashrc

    mkdir -p install && cd install

    yum install vim
    yum install svn
    yum install git
}

vim_syn()
{
    git clone https://github.com/ccredrock/rock_vim
    cd rock_vim && sh install.sh

    yum -y install cmake-devel python-devel
    cd ~/.vim/bundle/YouCompleteMe && ./install.py
}

erlang()
{
    # erlang
    yum -y install make gcc gcc-c++ kernel-devel m4 ncurses-devel openssl-devel

    tar -xzvf otp_src_17.0.tar.gz

    ./configure --with-ssl \
        --enable-threads --enable-smp-support \
        --enable-kernel-poll --enable-hipe --without-javac

    # erlang doc
    # cp /usr/share/locale/en/LC_MESSAGES/man /usr/share/locale
    tar -xzvf otp_doc_man_17.0.tar.gz
    cp -r man /usr/local/lib/erlang/

    # rebar
    cd /usr/local/lib && svn co svn://192.168.1.217:10010/u3d/server/erl_deps/rebar
    cd rebar && rm -rf ebin/* && ./bootstrap
    ln -s /usr/local/lib/rebar/rebar /usr/local/bin/rebar
}

create_user
bash_syn
vim_syn
erlang

