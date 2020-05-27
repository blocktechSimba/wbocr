//
//  WBVehicleLicenseModel.h
//  FBRetainCycleDetector
//
//  Created by tank on 2019/8/27.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface WBVehicleLicenseModel : NSObject

/// 正本内容
/// - plateNo                                 车牌号码
/// - vehicleType                          车辆类型
/// - owner                                    所有人
/// - address                                地址
/// - useCharacter                       使用性质
/// - model                                   品牌型号
/// - vin                                        识别代码
/// - engineNo                            发动机号
/// - registeDate                         注册日期
/// - issueDate                           发证日期
/// - licenseStamp                     红章
///
/// - authorizedCarryCapacity    核定载人数
/// - authorizedLoadQuality        核定载质量
/// - fileNumber                            档案编号
/// - total                                      总质量
/// - inspectionRecord               检验记录
/// - externalDimensions           外廓尺寸
/// - totalQuasiTractionMass    准牵引总质量
/// - curbWeright                        整备质量
/// - licensePlateNum                车牌号码
///
@property (nonnull, strong, nonatomic) UIImage  *homePageFullImage;
@property (nonnull, strong, nonatomic) NSString *plateNo;
@property (nonnull, strong, nonatomic) NSString *vehicleType;
@property (nonnull, strong, nonatomic) NSString *owner;
@property (nonnull, strong, nonatomic) NSString *address;
@property (nonnull, strong, nonatomic) NSString *useCharacter;
@property (nonnull, strong, nonatomic) NSString *model;
@property (nonnull, strong, nonatomic) NSString *vin;
@property (nonnull, strong, nonatomic) NSString *engineNo;
@property (nonnull, strong, nonatomic) NSString *registeDate;
@property (nonnull, strong, nonatomic) NSString *issueDate;
@property (nonnull, strong, nonatomic) NSString *licenseStamp;

@property (nonnull, strong, nonatomic) UIImage  *secondaryPageFullImage;
@property (nonnull, strong, nonatomic) NSString *authorizedCarryCapacity;
@property (nonnull, strong, nonatomic) NSString *authorizedLoadQuality;
@property (nonnull, strong, nonatomic) NSString *fileNumber;
@property (nonnull, strong, nonatomic) NSString *total;
@property (nonnull, strong, nonatomic) NSString *inspectionRecord;
@property (nonnull, strong, nonatomic) NSString *externalDimensions;
@property (nonnull, strong, nonatomic) NSString *totalQuasiTractionMass;
@property (nonnull, strong, nonatomic) NSString *curbWeright;
@property (nonnull, strong, nonatomic) NSString *licensePlateNum;


/// - hasWarning 当使用 SDK 类型为 WBOCRSDKTypeVehicleLicenseNormal 时候，如果正本和副本车牌号识别不一致，这个字段会返回 YES.
@property (nonatomic,assign) BOOL hasWarning;

- (instancetype _Nullable )initWithModel:(WBVehicleLicenseModel *_Nullable)model dictionary:(NSDictionary *_Nullable)dic;

@end

NS_ASSUME_NONNULL_END
