# Qemu RISC-V virt 教程

## 1. 简介
`riscv32_virt/` 子目录包含部分Qemu RISC-V虚拟化平台验证的OpenHarmony kernel\_liteos\_m的代码，目录名为*riscv32_virt*。
RISC-V 虚拟化平台是一个 `qemu-system-riscv32` 的目标设备，通过它来模拟一个通用的、基于RISC-V架构的单板。

这次模拟的配置是：RISC-V架构，1个CPU，128M内存。

提示: 系统内存硬编码为128MB。

## 2. 环境搭建

[环境搭建](https://gitee.com/openharmony/docs/blob/master/zh-cn/device-dev/porting/Readme-CN.md)

[编译器安装:gcc_riscv32](https://gitee.com/openharmony/docs/blob/master/zh-cn/device-dev/quick-start/quickstart-pkg-3861-tool.md),
提示: [可直接下载](https://repo.huaweicloud.com/harmonyos/compiler/gcc_riscv32/7.3.0/linux/gcc_riscv32-linux-7.3.0.tar.gz)

## 3. 获取源码

[代码获取](https://gitee.com/openharmony/docs/blob/HEAD/zh-cn/device-dev/get-code/sourcecode-acquire.md)

提示: 可以使用 `repo` 命令来获取源码。

## 4. 源码构建

在已经获取的源码根目录，请输入：

```
hb set
```

选择ohemu下的`qemu_riscv_mini_system_demo`选项。


然后执行构建命令如下：

```
hb build
```

这个命令构建会产生 `OHOS_Image` 的镜像文件。

在构建完成之后，对应的镜像文件在如下目录：
```
out/riscv32_virt/qemu_riscv_mini_system_demo/
```

## 5. 在Qemu中运行镜像

a) 如果没有安装 `qemu-system-riscv32` ，安装请参考链接:[Qemu安装指导](https://gitee.com/openharmony/device_qemu/blob/HEAD/README_zh.md)

b) 运行

(1). qemu 版本 < 5.0.0

```
cd device/qemu/riscv32_virt
qemu-system-riscv32 -machine virt -m 128M -kernel ../../../out/riscv32_virt/qemu_riscv_mini_system_demo/OHOS_Image -nographic -append "root=dev/vda or console=ttyS0"
```

(2). qemu 版本 >= 5.0.0

执行`./qemu-run --help`提示如下：

```
Usage: qemu-run [OPTION]...
Run a OHOS image in qemu according to the options.

    Options:

    -e, --exec file_name     kernel exec file name
    -n, --net-enable         enable net
    -l, --local-desktop      no VNC
    -g, --gdb                enable gdb for kernel
    -t, --test               test mode, exclusive with -g
    -h, --help               print help info

    By default, the kernel exec file is: out/riscv32_virt/qemu_riscv_mini_system_demo/OHOS_Image,
    and net will not be enabled, gpu enabled and waiting for VNC connection at port 5920.
```
默认不加参数的情况下，网络不会自动配置，并使用默认镜像文件，若需更改默认镜像文件，可以利用 `./qemu-run -e [file_name]` 指定

## 6. gdb调试

```
cd device/qemu/riscv32_virt
vim liteos_m/config.gni
```

将 `board_opt_flags` 中的

```
board_opt_flags = []
```

编译选项修改为:

```
board_opt_flags = [ "-g" ]
```

保存并退出，在OHOS根目录重新编译:

```
hb build -f
```

在一个窗口中输入命令：

```
./qemu-run -g
```

在另一个窗口中输入命令：

```
riscv32-unknown-elf-gdb out/riscv32_virt/qemu_riscv_mini_system_demo/OHOS_Image
(gdb) target remote localhost:1234
(gdb) b main
```

更多gdb相关的调试可以查阅：[gdb指导手册](https://sourceware.org/gdb/current/onlinedocs/gdb)。

## 7. 用法示例

- [用FAT映像传递文件](example.md#sectionfatfs)
