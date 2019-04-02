//
//  IMSThingElement.h
//  IMSThingCapability
//
//  Created by ZhuYongli on 2018/1/31.
//  Copyright © 2018年 ZhuYongli. All rights reserved.
//

#import <Foundation/Foundation.h>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wnon-modular-include-in-framework-module"
#import <TBJSONModel/TBJSONModel.h>
#pragma clang diagnostic pop

NS_ASSUME_NONNULL_BEGIN

/**
 TSL概念：
 物模型是对设备「是什么,能做什么] 的描述,包括设备身份标识、连接状态、描述信息,
 以及设备的属性(properties)、服务(services)、事件(events),后三者构成了设备的功能定义,即为 物的三要素 。
 阿里云IoT平台通过定义一种物的描述语言来描述物模型,称之为 TSL(即 Thing Specification Language)。对产品的功能定义完成后,平台将自动生成 JSON 格式的 TSL。
 
 物的模型中三要素类的基类，对于此类中的 property，请参见 IoT-TSL 模板
 */
@interface IMSThingTslElement : TBJSONModel
@property(nonatomic, copy, nullable) NSString * identifier; ///< 要素唯一标识符(产品下唯一)
@property(nonatomic, copy, nullable) NSString * name;  ///< 要素名称
@property(nonatomic, copy, nullable) NSString * required; ///< 要素是否为必须
@property(nonatomic, copy, nullable) NSString * desc; ///< 要素的描述
@end



/**
物的模型中三要素之属性类,对于此类中的 property，请参见 IoT-TSL 模板
 */
@interface IMSThingTslProperty : IMSThingTslElement
@property(nonatomic, copy, nullable) NSString * accessMode; ///< 属性读写类型，只读 (r)，只写 (w)，读写 (rw)
@property(nonatomic, copy, nullable) id  dataType; ///< 属性类型: int (原生)，float (原生)，double (原生), text (原生)，date (String 类型 UTC 毫秒)，bool (0或1的 int 类型)，enum (int类型), struct(结构体类型，可包含前面6种类型)，array(数组类型，支持int/double/float/text)。 具体内容请参见 IoT-TSL 模板
@end


/**
 物的模型中三要素之事件类,对于此类中的 property，请参见 IoT-TSL 模板
 */
@interface IMSThingTslEvent : IMSThingTslElement
@property(nonatomic, copy, nullable) NSString * type; ///< 事件类型 (info,alert,error)
@property(nonatomic, copy, nullable) NSString * method; ///< 事件对应的方法名称(根据 identifier 生成)
@property(nonatomic, copy, nullable) NSArray *  outputData; ///< 事件输出参数详细描述
@end


/**
物的模型中三要素之服务类,对于此类中的 property，请参见 IoT-TSL 模板
 */
@interface IMSThingTslService : IMSThingTslElement
@property(nonatomic, copy, nullable) NSString * method; ///< 服务对应的方法名称(根据 identifier 生成)
@property(nonatomic, copy, nullable) NSArray *  inputData; ///< 服务调用时的入参详细描述
@property(nonatomic, copy, nullable) NSArray *  outputData; ///< 服务调用时的出参详细描述
@end

NS_ASSUME_NONNULL_END
