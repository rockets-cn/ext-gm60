/*!
 *@file DFRobot_GM60.h
 *@brief Define the basic structure of class DFRobot_GM60, the implementation of basic methods.
 *@copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 *@licence     The MIT License (MIT)
 *@author [fengli](li.feng@dfrobot.com)
 *@version  V1.0
 *@date  2021-6-28
 *@get from https://www.dfrobot.com
 *@https://github.com/DFRobot/DFRobot_GM60
*/


#ifndef DFRobot_GM60_H
#define DFRobot_GM60_H

#include <Arduino.h>
#include <string.h>
#include <Wire.h>
//#define ENABLE_DBG

#ifdef ENABLE_DBG
#define DBG(...) {Serial.print("[");Serial.print(__FUNCTION__); Serial.print("(): "); Serial.print(__LINE__); Serial.print(" ] "); Serial.println(__VA_ARGS__);}
#else
#define DBG(...)
#endif
//extern Stream *dbg;
class DFRobot_GM60
{
public:

#define REG_SETUP_CODE_CONFIG     0X0003  //设置码配置
#define REG_ENCODE_SET            0x000D  //输出编码配置
typedef enum{
  eGBK,  //gbk编码
  eUTF8, //utf8编码
}eEncode_t;
#define REG_DATA_WITH_PACKET      0X001A //协议包头数据
typedef enum{
 e3 = 0, //包头数据为0x03
 e4 = 1, //包头数据为0x04
 eNone = 3, // 无包头数据 
}eHead_t;
#define REG_IDENTIFY_CONFIG      0x002C  //二维码识别开关
typedef enum{
  eForbidAllBarcode, //禁止所有的二维码识别
  eEnableAllBarcode, // 使能所有的二维码识别
  eEnableDefaultcode, // 使能默认的二维码识别
}eBarCode_t;


#define REG_IDENTIFY_EAN13       0X002E  

#define REG_IDENTIFY_EAN13-2     0X002F
#define REG_IDENTIFY_EAN13-5     0X0030
#define REG_IDENTIFY_EAN8        0X0031
#define REG_IDENTIFY_EAN8-2      0X0032
#define REG_IDENTIFY_EAN8-5      0X0033
#define REG_IDENTIFY_UPCA        0X0034
#define REG_IDENTIFY_UPCA-2        0X0035
#define REG_IDENTIFY_UPCA-5        0X0036
#define REG_IDENTIFY_UPCE0        0X0037
#define REG_IDENTIFY_UPCE1        0X0038
#define REG_IDENTIFY_UPCE1-2        0X0039
#define REG_IDENTIFY_UPCE1-5        0X003A
#define REG_IDENTIFY_CODE128        0X003B

#define REG_CODE128_MIN_LEN_SET        0X003C
#define REG_CODE128_MAX_LEN_SET        0X003D 
#define REG_IDENTIFY_CODE39        0X003E
#define REG_IDENTIFY_CODE32        0X003F
#define REG_IDENTIFY_CODE39_FULL_ASCII   0X0040


#define REG_CODE39_MIN_LEN_SET        0X0041
#define REG_CODE39_MAX_LEN_SET        0X0042
#define REG_IDENTIFY_CODE93           0X0043
#define REG_CODE93_MIN_LEN_SET        0X0044
#define REG_CODE93_MAX_LEN_SET        0X0045
#define REG_IDENTIFY_CODEBAR           0X0046
#define REG_CODEBAR_MIN_LEN_SET        0X0047
#define REG_CODEBAR_MAX_LEN_SET        0X0048
#define REG_IDENTIFY_QR                0X0049
#define REG_IDENTIFY_INT25               0X004A
#define REG_INT25_MIN_LEN_SET            0X004B
#define REG_INT25_MAX_LEN_SET            0X004C
#define REG_IDENTIFY_PDF417              0X004D
#define REG_IDENTIFY_DM                  0X004E

#define REG_OUTPUT_PROTOCOL_CONFIG       0X0060 //协议配置寄存器
#define REG_RECOVER_FACTORY_SET          0X00D9 //恢复出厂设置寄存器

public:

  /*!
   * @brief Constructor 
   */
  DFRobot_GM60();
  
  /**
   * @brief 初始化芯片
   * @return true(初始化成功)/false
   */
  bool begin();
  
  /**
   * @brief 读出数据的编码方式
   * @param encode 编码方式
                   eGBK,  //gbk编码
                   eUTF8, //utf8编码
   * @return true(设置成功)/false(设置失败)
   */
  bool encode(eEncode_t encode);
  
  /**
   * @brief 设置码配置,可以通过使用模块扫描二维码,更改芯片寄存器的值
   * @param on true(打开设置码)/false(关闭设置码)
   * @param content true(输出设置码内容)/false(不输出设置码内容)
   * @return true(设置成功)/false(设置失败)
   */
  bool setupCode(bool on,bool content);
  
  /**
   * @brief 设置二维码识别的种类设置
   * @param berCode 
            eForbidAllBarcode, //禁止所有的二维码识别
            eEnableAllBarcode, // 使能所有的二维码识别
            eEnableDefaultcode, // 使能默认的二维码识别
   * @return true(设置成功)/false(设置失败)
   */
  bool setIdentify(eBarCode_t berCode);
  
  /**
   * @brief 恢复出厂设置
   * @return true(设置成功)/false(设置失败)
   */
  bool reset();
  
  /**
   * @brief 检测扫描到的二维码包含的数据
   * @return  以字符串的方式返回扫描到的数据
   */
  String detection();

  uint8_t communication;
private:

  String responsePayload();
  uint8_t readPrefix();

  /**
   * @brief 在输出的数据中增加包头数据
   * @param head 包头的具体数据 e3(0x03)/e4(0x04)
   * @return true(设置成功)/false(设置失败)
   */
  bool setHeadData(eHead_t head);
  
  /**
   * @brief Write data to sensor register 
   * @param reg register
   * @param data  buf for store data to write 
   * @param lenght  The number of the data in pBuf
   * @return The number of successfully sent data
   */
  virtual uint8_t writeReg(uint16_t reg,uint8_t data[],uint8_t lenght)=0;
  
  /**
   * @brief read data from sensor chip register
   * @param reg chip register 
   * @param data  buf for store data to read 
   * @param length  number of data to read
   * @return The number of successfully read data
   */
  virtual uint8_t readReg(uint16_t reg,uint8_t data[],uint8_t length)=0;
  
  /**
   * @brief read data from sensor
   * @param data  buf for store data to read 
   * @param length  number of data to read
   * @return The number of successfully read data
   */
  virtual size_t read(uint8_t* buf_, size_t len)=0; 
   
  TwoWire *_pWire;

  uint8_t _address;
  
};

class DFRobot_GM60_IIC : public DFRobot_GM60{
public: 
  /*!
   * @brief Constructor 
   * @param pWire I2c controller
   * @param addr  I2C address(0x1A)
   */
   DFRobot_GM60_IIC(TwoWire *pWire = &Wire, uint8_t address = 0x1A);
   
  /**
   * @brief Init communication port
   * @return true or false
   */
   bool begin();
protected:

  /**
   * @brief Write data to sensor register 
   * @param reg register
   * @param data  buf for store data to write 
   * @param lenght  The number of the data in pBuf
   * @return The number of successfully sent data
   */
   virtual uint8_t writeReg(uint16_t reg,uint8_t data[],uint8_t lenght);

  /**
   * @brief read data from sensor chip register
   * @param reg chip register 
   * @param data  buf for store data to read 
   * @param length  number of data to read
   * @return The number of successfully read data
   */
   virtual uint8_t readReg(uint16_t reg,uint8_t data[],uint8_t length);
   
  /**
   * @brief read data from sensor
   * @param data  buf for store data to read 
   * @param length  number of data to read
   * @return The number of successfully read data
   */
   virtual size_t read(uint8_t* buf, size_t len);
private:
  TwoWire *_pWire;
  uint8_t _deviceAddr;
};

class DFRobot_GM60_UART : public DFRobot_GM60{

public: 

  /*!
   * @brief Constructor 
   */
  DFRobot_GM60_UART();
  /**
   * @brief Init communication port
   * @param Software serial or hardware serial 
   * @return true or false
   */
  bool begin(Stream &s_);
protected:

  /**
   * @brief Write data to sensor register 
   * @param reg register
   * @param data  buf for store data to write 
   * @param lenght  The number of the data in pBuf
   * @return The number of successfully sent data
   */
  virtual uint8_t writeReg(uint16_t reg,uint8_t data[],uint8_t lenght);

  /**
   * @brief read data from sensor chip register
   * @param reg chip register 
   * @param data  buf for store data to read 
   * @param length  number of data to read
   * @return The number of successfully read data
   */
  virtual uint8_t readReg(uint16_t reg,uint8_t data[],uint8_t length);
   
  /**
   * @brief read data from sensor
   * @param data  buf for store data to read 
   * @param length  number of data to read
   * @return The number of successfully read data
   */
  virtual size_t read(uint8_t* buf_, size_t len);
private:

  Stream *s;
};
#endif
