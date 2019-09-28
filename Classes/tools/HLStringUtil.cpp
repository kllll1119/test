//
//  HLStringUtil.cpp
//  HoolaiEngine
//
//  Created by zhao shuan on 13-2-26.
//

#include "HLStringUtil.h"
#include "stdlib.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"

using namespace std;
USING_NS_CC;

// Helper function. I included it here so that you can compile the whole file
// it returns a random value between min and max included
float fgRangeRand(float min, float max)
{
	float rnd = ((float)rand() / (float)RAND_MAX);
	return rnd * (max - min) + min;
}

// map<int,ST_EventInfo> g_eventInfo;	//这个来控制所有逻辑，初始化一次即可
// 
// void AddEventWithJson(int event,std::string json)
// {
// 	CCLOG("AddEventWithJson[%d]:%s\n", event, json.c_str());
// 	rapidjson::Document readdoc;
// 	bool bRet = false;
// 	ssize_t size = 0;
// 	readdoc.Parse<0>(json.c_str());
// 	if (readdoc.HasParseError())
// 	{
// 		CCLOG("GetParseError%s\n", readdoc.GetParseError());
// 	}
// 
// 	if (!readdoc.IsObject())
// 		return;
// 
// 	int role = 0;
// 	if(readdoc.HasMember("role"))
// 		role = readdoc["role"].GetInt();
// 	std::string ico = "";
// 	if (readdoc.HasMember("ico"))
// 		ico = readdoc["ico"].GetString();
// 
// 	std::string bk = "";
// 	if (readdoc.HasMember("bk"))
// 		bk = readdoc["bk"].GetString();
// 	
// 	std::string music = "";
// 	if (readdoc.HasMember("music"))
// 		music = readdoc["music"].GetString();
// 
// 	std::string wav = "";
// 	if (readdoc.HasMember("wav"))
// 		wav = readdoc["wav"].GetString();
// 
// 	std::string item = "";
// 	if (readdoc.HasMember("item"))
// 		item = readdoc["item"].GetString();
// 
// 	float shark = 0.0f;
// 	if (readdoc.HasMember("shark"))
// 		shark = (float)readdoc["shark"].GetInt();
// 
// 	float bktime = 1.0f;
// 	if (readdoc.HasMember("bktime"))
// 		bktime = readdoc["bktime"].GetDouble();
// 
// 	float mv = 0.0f;
// 	if (readdoc.HasMember("mv"))
// 		mv = readdoc["mv"].GetDouble();
// 
// 	int bkx = 0;
// 	if (readdoc.HasMember("bkx"))
// 		bkx = readdoc["bkx"].GetInt();
// 
// 	int bky = 0;
// 	if (readdoc.HasMember("bky"))
// 		bky = readdoc["bky"].GetInt();
// 
// 	int save = 0;
// 	if (readdoc.HasMember("save"))
// 		save = readdoc["save"].GetInt();
// 
// 	int gotoEvent = 0;
// 	if (readdoc.HasMember("goto"))
// 		gotoEvent = readdoc["goto"].GetInt();
// 
// 	std::vector<ST_ChooseInfo> vecChoose;
// 	if (readdoc.HasMember("choose"))
// 	{
// 		rapidjson::Value& _array = readdoc["choose"];
// 		if (_array.IsArray())
// 		{
// 			for (int i = 0; i < _array.Capacity(); i++)
// 			{
// 				ST_ChooseInfo info;
// 				rapidjson::Value& arraydoc = _array[i];
// 				if (arraydoc.HasMember("goto"))
// 				{
// 					info.gotoEvent = arraydoc["goto"].GetInt();
// 				}
// 				if (arraydoc.HasMember("bk"))
// 				{
// 					info.bk = arraydoc["bk"].GetString();
// 				}
// 				if (arraydoc.HasMember("key"))
// 				{
// 					info.key = arraydoc["key"].GetString();
// 				}
// 				vecChoose.push_back(info);
// 			}
// 		}
// 	}
// 	ST_EventInfo info;
// 	info.role = (EM_ROLE)role;
// 	info.ico = ico;
// 	info.bk = bk;
// 	info.muisc = music;
// 	info.wav = wav;
// 	info.vecChoose = vecChoose;
// 	info.item = item;
// 	info.shark = shark;
// 	info.bktime = bktime;
// 	info.bkx = bkx;
// 	info.bky = bky;
// 	info.save = save;
// 	info.mv = mv;
// 	info.gotoEvent = gotoEvent;
// 	g_eventInfo.emplace(event, info);
// }

void InitEvent()
{
// 	char buf[20] = { 0 };
// 	int event_id = 1;
// 	while (true)
// 	{
// 		snprintf(buf, 20 - 1, "event_%d", event_id);
// 		string str = Tips::GetCHString(buf);	//读取事件配置逻辑
// 		if (str.empty())
// 			break;
// 		AddEventWithJson(event_id, str);
// 		++ event_id;
// 	}

	//下面是手动写事件逻辑
// 	std::vector<ST_ChooseInfo> vecNull;
// 	AddEvent(1, vecNull, ROLE_NOMAL,"","bk1.png", "snd/scxd.mp3");
// 	std::vector<ST_ChooseInfo> vecChoose;
// 	ST_ChooseInfo st;
// 	st.gotoEvent = 0;
// 	st.key = "chs15_0";
// 	vecChoose.push_back(st);
// 	st.gotoEvent = 0;
// 	st.key = "chs15_1";
// 	vecChoose.push_back(st);
// 	AddEvent(15, vecChoose, ROLE_CHOOSE);
}

// bool GetEventInfo(int event, ST_EventInfo& info)
// {
// 	if (g_eventInfo.find(event) != g_eventInfo.end())
// 	{
// 		info = g_eventInfo[event];
// 		return true;
// 	}
// 	return false;
// }

bool GetEventInfoEx(int event, ST_EventInfo& info)
{
	if (event <= 0)
		return false;
	char buf[20] = { 0 };
	snprintf(buf, 20 - 1, "event_%d", event);
	string json = Tips::GetCHString(buf);	//读取事件配置逻辑
	if (json.empty())
		return false;

	CCLOG("GetEventInfoEx[%d]:%s\n", event, json.c_str());
	rapidjson::Document readdoc;
	bool bRet = false;
	ssize_t size = 0;
	readdoc.Parse<0>(json.c_str());
	if (readdoc.HasParseError())
	{
		CCLOG("HasParseError\n");
		return false;
	}
	if (!readdoc.IsObject())
		return false;

	int role = 0;
	if (readdoc.HasMember("role"))
		role = readdoc["role"].GetInt();
	std::string ico = "";
	if (readdoc.HasMember("ico"))
		ico = readdoc["ico"].GetString();

	std::string bk = "";
	if (readdoc.HasMember("bk"))
		bk = readdoc["bk"].GetString();

	std::string music = "";
	if (readdoc.HasMember("music"))
		music = readdoc["music"].GetString();

	std::string wav = "";
	if (readdoc.HasMember("wav"))
		wav = readdoc["wav"].GetString();

	std::string item = "";
	if (readdoc.HasMember("item"))
		item = readdoc["item"].GetString();

	std::string mask = "";
	if (readdoc.HasMember("mask"))
		mask = readdoc["mask"].GetString();

	float shark = 0.0f;
	if (readdoc.HasMember("shark"))
		shark = (float)readdoc["shark"].GetInt();

	float bktime = 1.0f;
	if (readdoc.HasMember("bktime"))
		bktime = readdoc["bktime"].GetDouble();

	float mv = 0.0f;
	if (readdoc.HasMember("mv"))
		mv = readdoc["mv"].GetDouble();

	int bkx = 0;
	if (readdoc.HasMember("bkx"))
		bkx = readdoc["bkx"].GetInt();

	int bky = 0;
	if (readdoc.HasMember("bky"))
		bky = readdoc["bky"].GetInt();

	int save = 0;
	if (readdoc.HasMember("save"))
		save = readdoc["save"].GetInt();

	int gotoEvent = 0;
	if (readdoc.HasMember("goto"))
		gotoEvent = readdoc["goto"].GetInt();

	std::vector<ST_ChooseInfo> vecChoose;
	if (readdoc.HasMember("choose"))
	{
		rapidjson::Value& _array = readdoc["choose"];
		if (_array.IsArray())
		{
			for (int i = 0; i < _array.Capacity(); i++)
			{
				ST_ChooseInfo info;
				rapidjson::Value& arraydoc = _array[i];
				if (arraydoc.HasMember("goto"))
				{
					info.gotoEvent = arraydoc["goto"].GetInt();
				}
				if (arraydoc.HasMember("bk"))
				{
					info.bk = arraydoc["bk"].GetString();
				}
				if (arraydoc.HasMember("key"))
				{
					info.key = arraydoc["key"].GetString();
				}
				vecChoose.push_back(info);
			}
		}
	}
	info.role = (EM_ROLE)role;
	info.ico = ico;
	info.bk = bk;
	info.muisc = music;
	info.wav = wav;
	info.mask = mask;
	info.vecChoose = vecChoose;
	info.item = item;
	info.shark = shark;
	info.bktime = bktime;
	info.bkx = bkx;
	info.bky = bky;
	info.save = save;
	info.mv = mv;
	info.gotoEvent = gotoEvent;
	return true;
}

std::string GetCurTime()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	struct timeval now;
	struct tm* time;

	gettimeofday(&now, NULL);

	time = localtime(&now.tv_sec);

	char date[32] = { 0 };
	//格式化 使用需要的日期格式
	snprintf(date,31, "%d/%02d/%02d  %02d:%02d:%02d",
		(int)time->tm_year + 1900,
		(int)time->tm_mon + 1,
		(int)time->tm_mday,
		(int)time->tm_hour,
		(int)time->tm_min,
		(int)time->tm_sec);
	return date;
#elif ( CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 )
	struct tm* tm;
	time_t timep;
	time(&timep);
	tm = localtime(&timep);
	char date[32] = { 0 };
	snprintf(date,31, "%d/%02d/%02d  %02d:%02d:%02d", (int)tm->tm_year + 1900, (int)tm->tm_mon + 1, (int)tm->tm_mday,
		tm->tm_hour,tm->tm_min,tm->tm_sec);
	return date;
#endif
	return "";
}

// namespace StringUtil
// {
// //     std::string MD5(const char* str)
// //     {
// //         ::MD5 md5;
// //         md5.GenerateMD5((unsigned char*)str, strlen(str));
// //         return md5.ToString();
// //     }
//     
//     std::string Base64Encode(const unsigned char* data, int len)
//     {
//         const static char EncodeTable[]= {
//             0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48,
//             0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50,
//             0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58,
//             0x59, 0x5A, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66,
//             0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E,
//             0x6F, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76,
//             0x77, 0x78, 0x79, 0x7A, 0x30, 0x31, 0x32, 0x33,
//             0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x2B, 0x2F
//         };
//         
//         string strEncode;
//         const unsigned maxInputBufferSize = UINT_MAX / 77 * 76 / 4 * 3 - 2;
//         if (len > maxInputBufferSize)
//             return strEncode;
//         
//         unsigned sidx = 0;
//         unsigned didx = 0;
//         
//         unsigned outLength = ((len + 2) / 3) * 4;
//         
//         // Deal with the 76 character per line limit specified in RFC 2045.
//         bool insertLFs = false;
//         if (insertLFs)
//             outLength += ((outLength - 1) / 76);
//         
//         int count = 0;
//         strEncode.resize(outLength, 0);
//         // 3-byte to 4-byte conversion + 0-63 to ascii printable conversion
//         if (len > 1)
//         {
//             while (sidx < len - 2)
//             {
//                 if (insertLFs)
//                 {
//                     if (count && !(count % 76))
//                         strEncode[didx++] = '\n';
//                     count += 4;
//                 }
//                 strEncode[didx++] = EncodeTable[(data[sidx] >> 2) & 077];
//                 strEncode[didx++] = EncodeTable[((data[sidx + 1] >> 4) & 017) | ((data[sidx] << 4) & 077)];
//                 strEncode[didx++] = EncodeTable[((data[sidx + 2] >> 6) & 003) | ((data[sidx + 1] << 2) & 077)];
//                 strEncode[didx++] = EncodeTable[data[sidx + 2] & 077];
//                 sidx += 3;
//             }
//         }
//         
//         if (sidx < len)
//         {
//             if (insertLFs && (count > 0) && !(count % 76))
//                 strEncode[didx++] = '\n';
//             
//             strEncode[didx++] = EncodeTable[(data[sidx] >> 2) & 077];
//             if (sidx < len - 1)
//             {
//                 strEncode[didx++] = EncodeTable[((data[sidx + 1] >> 4) & 017) | ((data[sidx] << 4) & 077)];
//                 strEncode[didx++] = EncodeTable[(data[sidx + 1] << 2) & 077];
//             } else
//                 strEncode[didx++] = EncodeTable[(data[sidx] << 4) & 077];
//         }
//         
//         // Add padding
//         while (didx < strEncode.size())
//         {
//             strEncode[didx++] = '=';
//             ++didx;
//         }
//         
//         return strEncode;
//     }
//     
//     std::vector<unsigned char> Base64Decode(const char* data)
//     {
//         int outLen;
//         // decode table
//         const static char DecodeTable[] =
//         {
//             0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//             0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//             0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//             0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//             0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//             0x00, 0x00, 0x00, 0x3E, 0x00, 0x00, 0x00, 0x3F,
//             0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B,
//             0x3C, 0x3D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//             0x00, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06,
//             0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E,
//             0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16,
//             0x17, 0x18, 0x19, 0x00, 0x00, 0x00, 0x00, 0x00,
//             0x00, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20,
//             0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28,
//             0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30,
//             0x31, 0x32, 0x33, 0x00, 0x00, 0x00, 0x00, 0x00
//         };
//         
//         std::vector<unsigned char> dataDecode;
//         outLen = 0;
//         bool sawEqualsSign = false;
//         size_t len = strlen(data);
//         dataDecode.resize(len);
// 
//         for (unsigned idx = 0; idx < len; ++idx) {
//             unsigned ch = data[idx];
//             if (ch == '=')
//                 sawEqualsSign = true;
//             else if (('0' <= ch && ch <= '9') || ('A' <= ch && ch <= 'Z') || ('a' <= ch && ch <= 'z') || ch == '+' || ch == '/') {
//                 if (sawEqualsSign)
//                 {
//                     dataDecode.clear();
//                     return dataDecode;
//                 }
//                 dataDecode[outLen] = DecodeTable[ch];
//                 ++outLen;
//             }
//         }
//         
//         if (!outLen)
//             return dataDecode;
//         
//         // Valid data is (n * 4 + [0,2,3]) characters long.
//         if ((outLen % 4) == 1)
//         {
//             dataDecode.clear();
//             return dataDecode;
//         }
//         
//         // 4-byte to 3-byte conversion
//         outLen -= (outLen + 3) / 4;
//         if (!outLen)
//         {
//             dataDecode.clear();
//             return dataDecode;
//         }
//         
//         unsigned sidx = 0;
//         unsigned didx = 0;
//         if (outLen > 1) {
//             while (didx < outLen - 2) {
//                 dataDecode[didx] = (((dataDecode[sidx] << 2) & 255) | ((dataDecode[sidx + 1] >> 4) & 003));
//                 dataDecode[didx + 1] = (((dataDecode[sidx + 1] << 4) & 255) | ((dataDecode[sidx + 2] >> 2) & 017));
//                 dataDecode[didx + 2] = (((dataDecode[sidx + 2] << 6) & 255) | (dataDecode[sidx + 3] & 077));
//                 sidx += 4;
//                 didx += 3;
//             }
//         }
//         
//         if (didx < outLen)
//             dataDecode[didx] = (((dataDecode[sidx] << 2) & 255) | ((dataDecode[sidx + 1] >> 4) & 003));
//         
//         if (++didx < outLen)
//             dataDecode[didx] = (((dataDecode[sidx + 1] << 4) & 255) | ((dataDecode[sidx + 2] >> 2) & 017));
//         
//         if (outLen < dataDecode.size())
//             dataDecode.resize(outLen);
//         return dataDecode;
//     }
//     
//     std::string UrlEncode(const std::string& str)
//     {
//         std::string src = str;
//         char hex[] = "0123456789abcdef";
//         string dst;
//         for (size_t i = 0; i < src.size(); ++i)
//         {
//             unsigned char cc = src[i];
//             if (cc == ' ')
//             {
//                 dst += "+";
//             }
//             else if (isalnum(cc) || strchr("-_.!~*'()", cc))
//             {
//                 dst += cc;
//             }
//             else
//             {
//                 unsigned char c = static_cast<unsigned char>(src[i]);
//                 dst += '%';
//                 dst += hex[c>>4];
//                 dst += hex[c&0xf];
//             }
//         }
//         return dst;
//     }
//     
//     std::string UrlDecode(const std::string& str)
//     {
//         std::string result;
//         int hex = 0;
//         for (size_t i = 0; i < str.length(); ++i)
//         {
//             switch (str[i])
//             {
//                 case '+':
//                     result += ' ';
//                     break;
//                 case '%':
//                     if (isxdigit(str[i + 1]) && isxdigit(str[i + 2]))
//                     {
//                         std::string hexStr = str.substr(i + 1, 2);
//                         hex = (int)strtol(hexStr.c_str(), 0, 16);
// //                        if (!((hex >= 48 && hex <= 57) || //0-9
// //                              (hex >=97 && hex <= 122) || //a-z
// //                              (hex >=65 && hex <= 90) || //A-Z
// //                              //[$-_.+!*'(),] [$&+,/:;=?@]
// //                              hex == 0x21 || hex == 0x23 || hex == 0x24 || hex == 0x26 || hex == 0x27 || hex == 0x28
// //                              || hex == 0x29 || hex == 0x2a || hex == 0x2b|| hex == 0x2c || hex == 0x2d || hex == 0x2e
// //                              || hex == 0x2f || hex == 0x3A || hex == 0x3B|| hex == 0x3D || hex == 0x3f || hex == 0x40
// //                              || hex == 0x5f
// //                              ))
// //                        {
//                             result += char(hex);
//                             i += 2;
// //                        }
// //                        else result += '%';
//                     }else {
//                         result += '%';
//                     }
//                     break;
//                 default:
//                     result += str[i];
//                     break;
//             }
//         }
//         return result;
//  
//     }
// }
