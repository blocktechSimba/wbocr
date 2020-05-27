//
//  WBOCRConfig.h
//  Pods
//
//  WBOCRConfig类定义了SDK的配置信息，可以通过 WBOCRConfig 单例进行读取、配置，
//  配置是可选的，如果外部没有配置信息传入，将使用默认的配置参数。
//

#import <Foundation/Foundation.h>

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
///
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

@interface WBOCRConfig : NSObject

+ (instancetype _Nonnull )sharedConfig;

/**
 * @brief 选择SDK接入模式，default WBOCRSDKTypeIDCardNormal
 */
@property (nonatomic) WBOCRSDKType SDKType;

/**
 * @brief needBothSidesRecognized 参数当 SDKType 为 `WBOCRSDKTypeIDCardNormal`  / `WBOCRSDKTypeVehicleLicenseNormal` 时候起作用，default NO
 *
 * @detail 当参数设置为 YES 时，SDK需要将证件两面都识别成功之后，才能点击“完成”按钮退出SDK
 *       当参数设置为 NO   时，SDK只需要身份证人像面/行驶证正本识别成功，就可以点击“完成”按钮退出SDK
 */
@property (nonatomic) BOOL needBothSidesRecognized;


/// 适配 iOS13  ViewController Presentation Style 的变化
/// SDK 默认使用 `UIModalPresentationFullScreen`
@property (nonatomic) UIModalPresentationStyle presentationStyle;

/**
 * @brief 设置身份证照片预览页面上的水印信息，default @"仅供本次业务使用"
 */
@property (nonatomic, copy) NSString * _Nullable waterMarking;

/**
 * @brief 设置识别超时时间，默认是20.0s
 */
@property (nonatomic) NSTimeInterval timeoutInterval;

/**
 * @brief 是否需要录制视频。此功能目前仅适用于身份证识别，默认为NO，即不录制；设置为 YES，识别成功之后，会返回长度不超过 3s 的视频地址
 */
@property (nonatomic) BOOL needRecordVideo ;

/**
 * @brief 获取SDK的登录接口的baseUrl，readonly
 */
@property (nonatomic, copy, readonly) NSString* _Nonnull baseUrl;

/**
 * @brief 获取本次业务的orderNo，readonly
 */
@property (nonatomic, strong, readonly) NSString *_Nonnull orderNo;

/**
 * @brief 获取本次业务的ocrId，readonly
 */
@property (nonatomic, strong, readonly) NSString *_Nonnull ocrId;

/**
 * @brief 获取本次业务的appId，readonly
 */
@property (nonatomic, strong, readonly) NSString *_Nonnull appId;

/**
 * @brief 获取本次业务的nonce，readonly
 */
@property (nonatomic, strong, readonly) NSString *_Nonnull nonce;

/**
 * @brief 获取本次业务的sign，readonly
 */
@property (nonatomic, strong, readonly) NSString *_Nonnull sign;

/**
 * @brief 获取本次业务的userId，readonly
 */
@property (nonatomic, strong, readonly) NSString *_Nonnull userId;

/**
 * @brief 获取cdn配置参数信息，readonly
 */
@property (nonatomic, strong, readonly) NSDictionary *_Nonnull cdnParam;

@end
