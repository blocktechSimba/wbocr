# OCR SDK v3.0 接入文档 （for iOS）



[TOC]

## 1. SDK 集成

SDK 支持 cocoapods 和手动两种方式集成。

### 1.1 SDK pod 集成

如果你的项目已经支持 cocopods ，可以使用本方式集成 SDK，本示例使用的 cocoapods 为 **1.7.2**。

下载的 OCR SDK 文件夹目录结构如下：

```
├── OCR_private_pod
│   ├── LICENSE
│   ├── Libs
│   └── WBOCRService.podspec
├── README
├── WBOCRDemo
│   ├── Podfile
│   ├── Podfile.lock
│   ├── Pods
│   ├── WBOCRDemo
│   ├── WBOCRDemo.xcodeproj
│   └── WBOCRDemo.xcworkspace
└── 接入指引.md
```

`OCR_private_pod` 文件夹下面是 OCR SDK 的 pod 仓库，这个仓库名称为 `WBOCRService` ，WBOCRDemo 文件夹下是示例 demo，通过 pod 方式集成，需要完成以下 3 个步骤：

1. 将 OCR_private_pod 文件夹移动到指定的位置（这个位置可以依据你项目文件的布局而定）
2. 在 podfile 中引用 pod
3. 执行 pod install 完成安装

### 1.2 SDK 手动集成

- 下载 OCR SDK，找到 OCR_private_pod/Lib 文件夹，SDK 文件在这个文件夹下
- 拖拽 SDK 文件到 Xcode 工程内 (请勾选Copy items if needed选项) ，其中包括`WBOCRService.bundle`、`WBOCRService.framework`、`include文件夹`、`librecdetect.a` 以及 `opencv2.framework`、`liblibjpeg.a`

```
.
├── WBOCRService.bundle
├── WBOCRService.framework
├── include
├── librecdetect.a
└── opencv2.framework
```

- Build Setting --> Build Options --> Enable Bitcode   设置为NO.
- 在Build Phases -> link with libraries 下加入如下依赖.

```
CoreTelephony.framework
CoreServices.framework
CoreMedia.framework
AssetsLibrary.framework
AVFoundation.framework
SystemConfiguration.framework
WebKit.framework
libc++.tbd
```

- Build Setting --> Linking --> Other Linker Flag 设置 增加 `-ObjC` 和 `-lz` linker flag

### 1.3 集成过程中注意事项

#### cocoapods 集成时 `:path` 参数说明

使用 `:path` 参数，在指定路径下加载 pods ，这个路径是本质上是 WBOCRService.podspec 相对 podfile 的路径。在示例 WBOCRDemo 中，如下：

```ruby
target 'WBOCRDemo' do
  pod 'WBOCRService',:path => '../OCR_private_pod'
end
```

#### opencv 冲突问题

OCR SDK 中涉及图像处理部分内容，有用到 opencv 这个库，如果 APP 的其它模块也有用到 opencv.framework ，OCR SDK直接集成会报冲突错误，解决方案如下：

- 查看 APP 中使用的 opencv 的版本号，查看方式是，找到 `opencv2.framework/Versions/A/Resources/Info.plist` 文件，plist 中的 Bundle version 对应的 value，就是 opencv 的版本号，确定 opencv 是 2.x 还是 3.x
- 联系技术支持，下载 opencv 版本对应的的 OCR SDK
- OCR SDK 和 APP 中使用的 opencv.framework 二选一，删除其中一个，按照接入文档接入 OCR SDK

## 2. SDK调用

SDK中需要使用 camera，需要在 Info.plist中为 `NSCameraUsageDescription` 添加描述信息。

### 2.1 概述

OCR SDK 对外提供以下四类证件的识别能力：

- 身份证识别
- 银行卡识别
- 驾驶证识别
- 行驶证识别

### 2.2 SDK 头文件说明

SDK 一共对外暴露了 6 个头文件，如下所示：

```
├── Headers
│   ├── WBBankCardInfoModel.h
│   ├── WBDriverLicenseModel.h
│   ├── WBIDCardInfoModel.h
│   ├── WBOCRConfig.h
│   ├── WBOCRService.h
│   ├── WBVehicleLicenseModel.h
```

这些头文件可以大致分为三类：

- 模型类（WBBankCardInfoModel、WBDriverLicenseModel、WBIDCardInfoModel 和 WBVehicleLicenseModel），这些模型类分别对应银行卡、驾驶证、身份证和行驶证的识别结果字段
- 配置类（WBOCRConfig），这个类提供了 SDK 的配置选项
- 入口类（WBOCRService），这个类提供 SDK 的入口和回调

#### 2.2.1 模型类说明

模型类对外暴露识别结果，以身份证识别为例，WBIDCardInfoModel 类的实例返回身份证识别结果，结果中包含如下字段：

- idcard        公民身份号码
- name          姓名
- sex           性别
- nation        民族
- address       住址
- birth         出生
- authority     签发机关
- validDate     有效期限
- frontFullImg  国徽面截图
- backFullImg   人像面截图
- orderNo       订单号，和本次业务相关
- sign          签名信息
- warning       识别结果警告信息
- multiWarning  多重告警码，人像面是frontMultiWarning，国徽面对应backMultiWarning
- clarity       图片清晰度，人像面是frontClarity，国徽面对应backClarity

开发者按需获取需要的信息。

其余证件识别与之类似，详情参考类头文件的字段注释。

#### 2.2.2 配置类说明

WBOCRConfig 对外提供配置接口，下面的内容逐一介绍其核心接口。

WBOCRConfig 是一个单例，开发者必须通过制定的初始化方法 `sharedConfig` 初始化。

SDK一共支持四类证件识别，提供 8 种识别模式，通过 SDKType 这个参数配置 ：

```objc
/// * @brief  OCR SDK 提供三大类证件的识别能力：身份证、银行卡、行驶证 和 驾驶证。
///
/// WBOCRSDKType 定义 SDK 不同的识别模式，下面分为四大类来描述这些模式：
/// 1. 身份证识别（识别身份证人像面和国徽面）
///     - WBOCRSDKTypeNoraml  : 身份证识别标准模式，在 SDK 中完成人像面 + 国徽面识别，识别完成之后，将本次识别结果返回第三方APP
///     - WBOCRSDKTypeFontSide: 身份证人像面识别模式，在 SDK 中完成人像面识别，识别完成之后，将本次识别结果返回第三方APP
///     - WBOCRSDKTypeBackSide: 身份证国徽面识别模式，在 SDK 中完成国徽面识别，识别完成之后，将本次识别结果返回第三方APP
///
/// 2. 银行卡识别（识别银行卡卡号面）
///     - WBOCRSDKTypeBankCard：银行卡识别模式，SDK调起成功后，直接进入银行卡识别，识别完成之后，将本次识别结果返回第三方APP
///
/// 3. 行驶证识别（识别行驶证的主页和副页）
///     - WBOCRSDKTypeVehicleLicenseNormal：行驶证标准模式，在 SDK 中完成主页 + 副页识别，识别完成之后，将本次识别结果返回第三方APP
///     - WBOCRSDKTypeVehicleLicenseHomePage：行驶证主页识别模式，在 SDK 中完成行驶证主页识别，识别完成之后，将本次识别结果返回第三方APP
///     - WBOCRSDKTypeVehicleLicenseSecondaryPage：行驶证副页识别模式，在 SDK 中完成行驶证主页识别，识别完成之后，将本次识别结果返回第三方APP
///
/// 4. 驾驶证识别 （驾驶证主页）
/// - WBOCRSDKTypeDriverLicense：驾驶证识别模式，SDK调起成功后，直接进入驾驶证识别，识别完成之后，将本次识别结果返回第三方APP
typedef NS_ENUM(NSInteger, WBOCRSDKType) {
    WBOCRSDKTypeIDCardNormal, 
    WBOCRSDKTypeIDCardFrontSide,
    WBOCRSDKTypeIDCardBackSide,
    WBOCRSDKTypeBankCard,
    WBOCRSDKTypeVehicleLicenseNormal,
    WBOCRSDKTypeVehicleLicenseHomePage,
    WBOCRSDKTypeVehicleLicenseSecondaryPage,
    WBOCRSDKTypeDriverLicense
};
```

当 SDKType 为 `WBOCRSDKTypeIDCardNormal`  / `WBOCRSDKTypeVehicleLicenseNormal` 的时候，可以通过 `needBothSidesRecognized` 参数进一步配置 SDK。

```objc
 * @brief needBothSidesRecognized 参数当 SDKType 为 `WBOCRSDKTypeIDCardNormal`  / `WBOCRSDKTypeVehicleLicenseNormal` 时候起作用，default NO
 *
 * @detail 当参数设置为 YES 时，SDK需要将证件两面都识别成功之后，才能点击“完成”按钮退出SDK
 *         当参数设置为 NO  时，SDK只需要身份证人像面/行驶证正本识别成功，就可以点击“完成”按钮退出SDK
 */
@property (nonatomic) BOOL needBothSidesRecognized;
```

#### 2.2.3 入口类说明

WBOCRService 是 SDK 的入口类，需要通过制定的初始化方法 `sharedService` 进行初始化。

```objc
/**
 * @brief WBOCRService 单例方法，通过调用该方法实例化 WBOCRService对象
 *
 * @return WBOCRService对象
 */
+ (nonnull instancetype) sharedService;
```

初始化完成之后，传入指定的参数，可以调起SDK，入口方法如下：

```objc
/**
 * @brief 调起SDK入口方法
 
 * @param config            配置参数
 * @param version           openAPI接口版本号,由腾讯服务统一分配
 * @param appId             appId，由腾讯服务分配的
 * @param nonce             每次请求需要的一次性nonce，一次有效
 * @param userId            每个用户唯一的标识
 * @param sign              签名信息，有接入方后台提供，一次有效
 * @param orderNo           订单号，长度不能超过32位的字符串
 * @param startSucceed      SDK启动成功回调
 * @param recognizeSucceed  识别成功回调，即将退出SDK
 * @param failed            SDK发生异常退出后回调，即将退出SDK
 */
- (void)startOCRServiceWithConfig:(nullable WBOCRConfig *)config
                          version:(nonnull NSString *)version
                            appId:(nonnull NSString *)appId
                            nonce:(nonnull NSString *)nonce
                           userId:(nonnull NSString *)userId
                             sign:(nonnull NSString *)sign
                          orderNo:(nonnull NSString *)orderNo
                     startSucceed:(nonnull WBOCRServiceStartSucceedBlock)startSucceed
                 recognizeSucceed:(nonnull WBOCRServiceRecognizeSuccessBlock)recognizeSucceed
                           failed:(nonnull WBOCRServiceFailedBlock)failed;

```

该类还提供了一个 readonly 字段，用来读取当前 SDK 的版本号。

```objc
/**
 * @brief sdk版本号，readonly参数
 */
@property (nonatomic,readonly,nonnull) NSString *sdkVersion;

```



### 2.3 接入示例

具体接入示例，请参考 demo 工程。

### 2.4 识别结果处理

SDK入口方法提供了三个回调 block： startSucceed、recognizeSucceed 和 failed ，通过这几个 block 来捕获识别结果或者异常状况。

#### 2.4.1 startSucceed（成功进入SDK回调）

进入这个回调，说明当前用户已经通过SDK鉴权，应用成功进入SDK界面了。

#### 2.4.2 recognizeSucceed（识别成功，即将退出SDK回调）

进入这个回调，说明SDK已经识别成功，即将退出，回到APP中的界面，这里面有两个参数 resultModel 和 extension。

- resultModel 是对识别结果的封装，如果当前识别的是**身份证**，就会返回一个`WBIDCardInfoModel`类型的实例；如果当前识别的是**银行卡**，返回的是一个`WBBankCardInfoModel`类型的实例。关于每个字段的详细含义，请参考`WBOCRService.h头文件`。
- extension 是一个扩展字段，备用，目前版本为空，不需要处理！

#### 2.4.3 failed（SDK异常，即将退出SDK回调）

进入这个回调，说明SDK发生异常，SDK即将退出，可以通过这个回调获取失败信息，这里面有两个参数 error 和 extension。

- error 是一个NSError类型的实例，里面会封装错误码和错误描述，下面代码展示了一条错误码为200101的error信息，具体的错误码对照表，**请参考《金融级远程身份认证开放平台接入指南》对应错误码章节**。

```
NSError *error = [NSError errorWithDomain:@"com.webank.ocr.error" code:200101 userInfo:@{NSLocalizedDescriptionKey:@"用户取消操作"}];

```

- extension 是一个扩展字段，备用，目前版本为空，不需要处理！

## 3. 其它

更多关于接入方面的问题请参考《金融级远程身份验证开放平台接入指南》文档和iOS 接入 demo。