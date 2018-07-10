# t2sdkEx
恒生电子周边接口sdk二次封装,C++版本通用版本

# 编译动态库 
g++ -shared -o t2sdkEx.dll  t2sdkEx.cpp -L. -lt2sdk

# 恒生t2sdk介绍
英文全称TCP 2 Software Development Kit。T2SDK是接入金融基础件2.0的客户端开发包，因为该开发包底层采用TCP协议，取名为“T2SDK”。T2SDK以dll（Windows下）或so（Linux下）的形式提供给开发者，通过使用T2SDK开发程序可以轻松实现和CRES2.0（金融基础件2.0）平台的对接，使用T2_SDK开发的程序在本文档中也称为“客户端”