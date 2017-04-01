# 跳板机传输

## 环境
* 本地机器mac
* 目标机器centos 6.5

## ssh 多次跳转一次密码
        Host jumper.xx.com
            HostName jumper.xx.com
            User name

        Host *
            ServerAliveInterval 300
            ControlMaster auto
            ControlPath ~/.ssh/master-%r@%h:%p
            ControlPersist yes

## 传输
* [brew](https://brew.sh/)
* brew install lrzsz
* [zssh](http://zssh.sourceforge.net/)
*       rz
        crtl+@
        zssh > sz test.md
