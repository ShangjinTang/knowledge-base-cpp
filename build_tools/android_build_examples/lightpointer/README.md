# Android build example: lightpointer

```bash
$ source build/envsetup.sh
```

## 1. Build executables for aarch64

Lunch target for remote android device with arch amd64 (ARM aarch64).

```bash
$ lunch aosp_arm64-eng
```

We can build executables on host and run on remote:

- adb push and adb shell execute
- lldb remote debug (not covered in this doc)

### 1.1 Build lightpointer-bp-dynamic for aarch64

#### build executable

```bash
$ cd ~/aosp
$ mmm build_examples/lightpointer/androidbp_dynamic

...
[100% 1763/1763] Install out/target/product/generic_x86_64/system/bin/lightpointer-bp-dynamic

#### build completed successfully (02:44 (mm:ss)) 
```

#### adb push

```bash
adb push out/target/product/generic_arm64/system/bin/lightpointer-bp-dynamic /system/bin/
out/target/product/generic_arm64/system/bin/lightpointer-bp-dynamic: 1 file pushed. 0.9 MB/s (11224 bytes in 0.012s)
```

#### adb shell execute

```bash
$ adb shell
xxxx/: # /system/bin/lightpointer-bp-dynamic
Construct LightClass Object.
Light Ref Count: 1.
Light Ref Count: 2.
Light Ref Count: 1.
Destory LightClass Object.
```

### 1.2 Build lightpointer-bp-static for aarch64

Similar to steps in `1.1`.

Not recommend because we can build and run dynamic executable as in `1.1`.

### 1.3 Build lightpointer-mk-dynamic for aarch64

Similar to steps in `1.1`.

### 1.4 Build lightpointer-mk-static for aarch64

Similar to steps in `1.1`.

Not recommend because we can build and run dynamic executable as in `1.3`.

## 2. Build static linked executable for x86_64

We can also build target same as host (x86_64), then we can run/debug the executable without android device.

```bash
lunch aosp_x86_64-eng
```

### 2.1 Build lightpointer-bp-static for x86_64

We do not use dynamic linked executable because the libraries are not default included in host link path.

Now we build static linked executable using Android.bp. (Android.mk would fail in this situation.)

#### build static executable

```bash
$ cd ~/aosp
$ mmm build_examples/lightpointer/androidbp_dynamic

...
[100% 22/22] Install out/target/product/generic_x86_64/system/bin/lightpointer-bp-static

#### build completed successfully (01:07 (mm:ss)) 
```

#### execute on host

```bash
$ ~/aosp % out/target/product/generic_x86_64/system/bin/lightpointer-bp-static
Construct LightClass Object.
Light Ref Count: 1.
Light Ref Count: 2.
Light Ref Count: 1.
Destory LightClass Object.
```
