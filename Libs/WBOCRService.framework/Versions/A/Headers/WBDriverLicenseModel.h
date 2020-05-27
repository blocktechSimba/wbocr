//
//  WBDriverLicenseModel.h
//  FBRetainCycleDetector
//
//  Created by tank on 2019/8/29.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// name 证件姓名
/// sex    性别
/// nationality    国籍
/// birth    出生日期
/// address    地址
/// fetchDate    领证日期
/// driveClass    准驾车型
/// validDateFrom    起始日期
/// validDateTo    有效日期
/// licenseStamp    证件红章
/// licenseNo   驾驶证号码

@interface WBDriverLicenseModel : NSObject

@property (nonatomic, copy) UIImage  *fullImage;
@property (nonatomic, copy) NSString *name;
@property (nonatomic, copy) NSString *sex;
@property (nonatomic, copy) NSString *nationality;
@property (nonatomic, copy) NSString *birth;
@property (nonatomic, copy) NSString *address;
@property (nonatomic, copy) NSString *fetchDate;
@property (nonatomic, copy) NSString *driveClass;
@property (nonatomic, copy) NSString *validDateFrom;
@property (nonatomic, copy) NSString *validDateTo;
@property (nonatomic, copy) NSString *licenseStamp;
@property (nonatomic, copy) NSString *licenseNo;



- (instancetype _Nullable )initWithModel:(WBDriverLicenseModel *_Nullable)model dictionary:(NSDictionary *_Nullable)dic;
@end

NS_ASSUME_NONNULL_END
