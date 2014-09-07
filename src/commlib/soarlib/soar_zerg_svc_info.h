#ifndef SOARING_LIB_SERVICES_INFO_H_
#define SOARING_LIB_SERVICES_INFO_H_

#include "soar_enum_define.h"

#pragma pack (1)
/****************************************************************************************************
class  SERVICES_ID 　服务编号信息,
****************************************************************************************************/
struct SOARING_EXPORT SERVICES_ID
{

public:

    ///构造,析构函数,默认为0
    explicit SERVICES_ID(uint16_t svrtype = INVALID_SERVICES_TYPE, uint32_t svrno = INVALID_SERVICES_ID);
    //
    ~SERVICES_ID();

    void  clear()
    {
        services_type_ = 0;
        services_id_ = 0;
    }

    ///设置
    void set_svcid(uint16_t svrtype, uint32_t svrid);

    ///比较函数,services_type_,services_id_
    bool operator ==(const SERVICES_ID &others) const;
    ///比较不同函数,
    bool operator !=(const SERVICES_ID &others) const;
    ///有个排序需求,
    bool operator <(const SERVICES_ID &others) const;

public:

    ///无效的SERVICE 类型
    static const uint16_t INVALID_SERVICES_TYPE = 0;

    ///无效的SERVICE ID
    static const uint32_t INVALID_SERVICES_ID   = 0;

    ///
    static const uint32_t BROADCAST_SERVICES_ID = (uint32_t)-2;

    ///表示是动态分片的SERVICE ID
    static const uint32_t DYNAMIC_ALLOC_SERVICES_ID = static_cast<uint32_t>(-1);

public:

    ///服务的类型,参考枚举值SERVICES_TYPE，无效时用INVALID_SERVICES_TYPE
    uint16_t           services_type_;

    ///服务的编号,采用两种表现方式,服务编号可以是一个服务器定义值,也可以是一个UIN.
    uint32_t           services_id_;


};

#pragma pack ()

//HASH函数,用于得到HASH Key

struct SOARING_EXPORT HASH_OF_SVCID
{
public:
    size_t operator()(const SERVICES_ID &svrinfo) const
    {
        return (size_t (svrinfo.services_type_) << 16) + svrinfo.services_id_ ;
    }
};

/******************************************************************************************
struct SERVICES_IP_INFO 服务ID信息 + IP信息
******************************************************************************************/
struct SOARING_EXPORT SERVICES_INFO
{
public:

    ///服务ID信息
    SERVICES_ID      svc_id_ = SERVICES_ID(0, 0);


    ///服务IP,服务端口
    ZCE_Sockaddr_In  ip_address_;

    ///服务器所属 IDC的编号
    unsigned int     idc_no_ = 0;

    ///业务ID
    unsigned int     business_id_ = 0;

};

//得到KEY的HASH函数
struct SOARING_EXPORT HASH_OF_SVCINFO
{
public:
    size_t operator()(const SERVICES_INFO &svripinfo) const
    {
        return (size_t (svripinfo.svc_id_.services_type_) << 16) + svripinfo.svc_id_.services_id_ ;
    }
};

struct SOARING_EXPORT EQUAL_OF_SVCINFO
{
public:
    //注意判断条件不是所有的变量
    bool operator()(const SERVICES_INFO &right, const SERVICES_INFO &left) const
    {
        //检查SVC INFO的相等,就认为相等
        if (right.svc_id_ == left.svc_id_ )
        {
            return true;
        }

        return false;
    }
};

#endif //#ifndef SOARING_LIB_SERVICES_INFO_H_

