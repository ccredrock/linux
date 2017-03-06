#[markdown学习](http://wowubuntu.com/markdown/)

##标题
    This is an H1
    =============
    This is an H2
    -------------

    # 这是 H1
    ## 这是 H2
    ###### 这是 H6
show:  
This is an H1
=============
This is an H2
-------------

# 这是 H1
## 这是 H2
###### 这是 H6

##区块
    > first line
    second line.

    > first line
    > second line.
show:  
> first line  
second line.

> first line  
> second line.

##列表
    * list1
    * list2
    + list1
    + list1
    - list2
    - list2
    1. list2
    2. list2
    *    retract_list1  
         retract_list2
    *    retract_list1  
    retract_list2
show:  
* list1
* list2
+ list1
+ list1
- list2
- list2
1. list1
2. list2
*    retract_list1  
     retract_list2
*    retract_list1  
retract_list2

##代码
        code1
        code2
show:  

    code1
    code2

##分割线
    ***
    ---
    -------------------------
show:  
***
---
-------------------------

##链接
    [This link](http://example.net/, "title")
    [This link](./example)

    This is [an example][id] reference-style link.
    [id]: http://example.com/  "Optional Title Here"

    [Google][]
    [Google]: http://google.com/

show:  
[This link](http://example.net/, "title")  
[This link](./example)
This is [an example][id] reference-style link.
[id]: http://example.com/  "Optional Title Here"
[Google][]
[Google]: http://google.com/

##强调
    *single asterisks*
    _single asterisks_
    **single asterisks**
    __single asterisks__
show:  
*single asterisks*  
_single asterisks_  
**single asterisks**  
__single asterisks__

##代码
    Use the `printf()` function.
    ``There is a literal backtick (`) here.``
show:  
Use the `printf()` function.  
``There is a literal backtick (`) here.``

##图片
    ![Alt text](/path/to/img.jpg "Optional title")
    ![Alt text][id]
    [id]: url/to/image  "Optional title attribute"
show:  
![Alt text](/path/to/img.jpg "Optional title")  
![Alt text][id]  
[id]: url/to/image  "Optional title attribute"

##自动链接
    http://example.com/
    <http://example.com/>
    address@example.com
    <address@example.com>
show:  
http://example.com/  
<http://example.com/>  
address@example.com  
<address@example.com>

##其他
* 换行 行尾两个空格
* 转义 反斜杠

##github
    * []
    * [x]
* []
* [x]

