# Mysql

#[优化](http://coolshell.cn/articles/1846.html)
* 推荐查询缓存
* 调试explain explain select * from t_user
* 推荐limit
* 推荐索引
* 优化jion(字段是索引&&相同类型&&相同字符集)
* 避免order by rand
* 避免select *
* 推荐每张表数值ID为Key
* 推荐enum代替varchar
* 建议procedure analyse() select * from t_user procedure analyse()
* 推荐not null
* 推荐prepared statements
* 推荐ip地址存为unsigned int 配合inet_ntoa inet_aton
* 推荐固定长度表(static || fixed-length)
* 推荐垂直分割(分表 小表,功能隔离性能高) 需要不经常jion
* 拆分大的delete insert语句(会锁表较长时间)
* 推荐小列(数据紧凑性能高)
* 选择引擎([MyISAM|InnoDB](http://coolshell.cn/articles/652.html))
