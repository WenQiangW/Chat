# Chat
实现一个基于UDP的群聊服务器Server

版本1
Server负责把客户端的数据接收放在数据池中，
负责从数据池中取出数据群发给所有的客户端。

Client端：负责从标准输入读取数据，发送给Server端
          负责接收Server群发的信息。
