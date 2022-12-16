## shell常用命令
    cat /etc/shells             查看linux系统支持的shell    
    echo $SHELL                 查看linux当前使用的shell          
    ctrl + a                    命令行移动光标到开头                
    ctrl + e                    命令行移动光标到结尾                
    ctrl + u                    清除命令行已输入的内容              

## linux系统的目录结构
    bin                         存放可执行文件
    boot                        存放开机启动例程
    dev                         存放设备对应的文件
    etc                         存放用户相关的配置信息
    lib                         库路径
    mnt media                   存放磁盘挂载文件, 默认挂载在media
    opt proc                    linux系统编程相关
    usr                         存放第三方库
    
## linux文件类型
    -       -->         普通文件
    -       -->         目录文件
    c       -->         字符设备文件
    b       -->         块设备
    l       -->         软连接
    p       -->         管道文件
    s       -->         套件字

## 软链接和硬链接
**软链接**

    ln -s /home/hui/aa.txt  aa       // 使用绝对路径创建软链接aa, 确保移动链接后也能访问到
        // 软链接值存了一个地址, 访问是替换为存储的地址
**硬链接**

    ln ./aa.txt aa                  // 使用绝对/相对路径创建硬链接, 移动链接后也能访问
        // 每一个硬链接都是一个独立的文件
        // 操作系统为相同指向的硬链接赋予相同的inode, 当有相同的inode文件存在是, 彼此同步
        // 修改硬链接会同时修改原文件和其所有的硬链接
        // 删除硬链接时, 只将硬链接inode-1, 只有当inde

## 文件权限修改
    权限指代的三种用户(-rwxrwxrwx):  
        u:      表示文件拥有者, 第一个rwx特指它的权限
        g:      表示同组用户, 第二个rwx特指它的权限
        o:      表示其他用户, 第三个rwx特指它的权限
    
    权限对应数字(-rwxrwxrwx):
        4:      对应r
        2:      对应w
        1:      对应x

**文字修改权限**

    chmod u+rwx g+rwx o+r a.c       // 赋予权限 -rwxrwxr--

**数字修改权限**
    
    chmod 754                       // 赋予权限 -rwxr-xr--

**修改文件所属用户**
    
    chown hui:hui                   // 修改文件拥有者hui, 用户组hui

## 找文件内容_grep
    grep -rn "aaa"                  // 在当前目录下的所有文件内容中搜索aaa