# BuildClover
Build_Clover.command 来自https://github.com/Micky1979 作者:Micky1979
```shell
================================================== ==============================
Build_Clover脚本v5.1.8无可用更新。
                             <------------------------------------------------- - 
================================================== ==============================
由Micky1979基于Slice，apianti，vit9696，下载Fritz，Zenith432，
STLVNUB，JrCs，cecekpawon，Needy，cvad，Rehabman，philip_petev，ErmaC

支持的操作系统：macOS X，Ubuntu（16.04 / 16.10），Debian Jessie和Stretch
                             <------------------------------------------------- - 
CLOVER远程版本：5058本地版本：5057
EDK2远程版本：29574本地版本：28976

当前的本地EDK2修订版是建议修订版（28976）。
使用的设置：/Users/weisiyuan/BuildCloverConfig.txt
                             <------------------------------------------------- - 
使用XCODE8构建
请输入您的选择：
 1）更新“buildclover”符号链接
 2）仅更新三叶草（无建筑物）
 3）更新Clover + force edk2更新（无建筑）
 4）在源代码上运行我的脚本
 5）构建现有修订版（无更新，仅用于测试）
 6）构建现有的发布版本（无更新，标准版本）
 7）在启用自定义宏的情况下构建现有修订版
 8）进入开发者模式（仅限开发者）
 9）尝试Clover Configurator Pro.app
 10）编辑配置文件
 11）退出
```
源代码来自 https://sourceforge.net/projects/cloverefiboot/

###安装相关环境

 Xcode

Mac App Store商店安装Xcode
终端下输入如下命令并按提示安装
复制
```bash
xcode-select --install
```

 准备编译脚本Build_Clover.command
```
git clone https://github.com/a13134455667/BuildClover.git
```

给予执行权限 Build_Clover.command
```
chmod u+x Build_Clover.command
```



 复制 SRC 到 ~/ 下:
```bash
cp -r /BuildClover/src ~/
```
 运行 Build_Clover.command 编译 Clover.
