//
//  WBOCRService.h
//  Pods
//
//  1. `WBOCRService` 是SDK的入口类，是一个单例类，是SDK的入口
//  2. SDK的具体调用请参考接入文档和SDK附带的demo
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "WBOCRConfig.h"

#import "WBIDCardInfoModel.h"
#import "WBBankCardInfoModel.h"
#import "WBDriverLicenseModel.h"
#import "WBVehicleLicenseModel.h"

/**
 * @brief WBOCRService类提供了SDK的入口,
 *        通过调用startService方法可以启动SDK,
 *        可以从几个不同的回调中获取相应的结果回调.
 */

///////////////////////////////////////////////////////////////////////////////
//////////////////                     ////////////////////////////////////////
//////////////////    WBOCRService     ////////////////////////////////////////
//////////////////                     ////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

@interface WBOCRService : NSObject

/**
 * @brief SDK启动成功回调，APP已经进入OCR识别界面
 */
typedef void(^WBOCRServiceStartSucceedBlock)(void);

/**
 * @brief SDK识别完成回调，SDK即将退出，回调中包含有包含有本次识别信息
 *
 * @param resultModel 识别到的OCR信息
 * @param extension   扩展字段，目前版本没有使用，为空
 */
typedef void(^WBOCRServiceRecognizeSuccessBlock)(id _Nonnull resultModel,id _Nullable extension);

/**
 * @brief SDK异常退出后回调，SDK即将退出，回调中包含有异常原因
 *
 * @param error     导致退出的Error信息，里面包含错误码和错误描述，具体错误码的对照请参考在线接入文档
 * @param extension 扩展字段，目前版本没有使用，为空
 */
typedef void(^WBOCRServiceFailedBlock) (NSError * _Nonnull error,id _Nullable extension);

/**
 * @brief WBOCRService 单例方法，通过调用该方法实例化 WBOCRService对象
 *
 * @return WBOCRService对象
 */
+ (nonnull instancetype) sharedService;

/**
 * @brief sdk版本号，readonly参数
 */
@property (nonatomic,readonly,nonnull) NSString *sdkVersion;

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
 *
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


@end

