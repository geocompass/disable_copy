# disable_copy
Disable the PostgreSQL copy command
# How to use
1. 进入PostgreSQL源码目录的contrib文件夹下
2. 创建disable_copy文件夹
3. 复制`disable_copy.c`与`Makefile`文件至disable_copy下
4. `make && make install`
5. `/usr/bin/install -c -m 755 disable_copy.so /usr/local/pgsql/11/lib`
6. 修改`/usr/local/pgsql/11/data/postgres.conf`文件，增加`shared_preload_libraries = 'disable_copy'`
7. 重启数据库
