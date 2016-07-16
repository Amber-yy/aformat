/*

Yuyue's Classes Library For Microsoft Visual C++

Copyright @2016 CDU INnoVation Studio
All rights reserved.

�ļ����ƣ�aformat.h
ժҪ��
1.���ļ����и�ʽ������AFormat��������ʵ����aformat.cpp�С�
2.AFormat��Ķ�����ʵ�ָ�������֮���ת�������ַ������������ȡ�
3.����std::array��û�е����κα�׼�⺯����ȫ������Ϊ�Լ�ʵ�֡�
4.�ṩstrLen��memCpy�Ⱦ�̬�������÷����׼���еĶ�Ӧ����һ�¡�
5.pow����ֻ���ڼ���10���ݣ�����������������������Ϊ˽�г�Ա�������⹫����

��ǰ�汾��V1.0
���ߣ����á������
e-mail��1397011447@qq.com
�������ڣ�2016��07��10��
�������ڣ�2016��07��15��

������־��

*/
#include <array>
#include "acore.h"

ATHENA_BEGIN

class AFormat final
{
public:
	typedef unsigned long long bigInt;
	AFormat();
	~AFormat();

	int printf(char *,const char *,...);

	/*�ַ������*/
	const char *iToStr(int, char *container = nullptr);
	const char *lToStr(long long, char *container = nullptr);
	const char *uiToStr(unsigned int, char *container = nullptr);
	const char *ulToStr(bigInt, char *container = nullptr);
	const char *fToText(double, int digit = 6, char *container = nullptr);
	const char *fToStr(double, int digit = 6, char *container = nullptr);
	const char *fToE(double, int digit = 6, char *container = nullptr, bool isLower = true);
	long long strToInt(const char *);
	double strToDouble(const char*);

	/*���������*/
	template<class T>
	const char* numToBin(T, char *container = nullptr);
	char binToChar(const char *);
	short binToShort(const char *);
	int binToInt(const char *);
	float binToFloat(const char *);
	double binToDouble(const char *);
	long long binToBigInt(const char *);

	/*ʮ���������*/
	template<class T>
	const char* numToHex(T, char *container = nullptr, bool isLower = false);
	const char* ptrToAddress(void *, char *container = nullptr, bool isLower = false);
	char hexToChar(const char *);
	short hexToShort(const char *);
	int hexToInt(const char *);
	float hexToFloat(const char *);
	double hexToDouble(const char *);
	long long hexToBigInt(const char *);

	/*�˽������*/
	const char *numToOct(bigInt, char *container = nullptr);
	bigInt octToNum(const char*);

	/*ϵͳ���*/
	bool isLittle();
	bool isX64();

	/*��̬����*/
	static bool isNum(char);
	static char *strUpr(char *);
	static char *strLwr(char *);
	static int strLen(const char *);
	static void *memSet(void *, char, size_t);
	static void *memCpy(void *, const void *, size_t);
private:
	enum dataType
	{
		null,ch,str,inte,floa,e,g,hex,oct,bin,mod,ptr
	};
	struct formatInfo
	{
		dataType type;//��ʽ����
		int digit;//����
		int len;//����
		char fillChar;//����ַ� 0 �ո� �������հײ���
		bool isLeftAlign;//�Ƿ����Ҷ��룬ȱʡΪ��
		bool isPreFix;//�Ƿ�ʹ��0x	 0ǰ׺
		bool isPlus;//�Ƿ�ʹ��+ǰ׺
		bool isLong;//�Ƿ��ǳ���
		bool isUp;//�Ƿ��д
		bool isUnsigned;//�Ƿ��޷���
		void reSet()
		{
			type = null;
			digit = 6;
			len = -1;
			fillChar = ' ';
			isUnsigned=isLeftAlign = isPreFix = isPlus = isLong = isUp = false;
		}
	};
	bool islittle;
	bool isx64;
	template <class T>
	const char * integerToStr(T, int, char *container);
	template<class T>
	T binToNum(T, int, const char *);
	template<class T>
	T hexToNum(T, int, const char*);
	void strHandle(char *&, char *&, char *&);
	void flagHandle(char *&, formatInfo &);
	void digitHandle(char *&,int &,int &);
	void typeHandle(char *&, formatInfo &);
	void integerHandle(char *&,formatInfo &,arg &,cBuffer &);
	void floatHandle(char *&, formatInfo &, arg &, cBuffer &);
	void chHandle(char *&, formatInfo &, arg &, cBuffer &);
	void hexHandle(char *&, formatInfo &, arg &, cBuffer &);
	void octHandle(char *&, formatInfo &, arg &, cBuffer &);
	void binHandle(char *&, formatInfo &, arg &, cBuffer &);
	void ptrHandle(char *&, formatInfo &, arg &, cBuffer &);
	void strHandle(char *&, formatInfo &, arg &);
	double pow( double);
	std::array<char, 16> hexChar;
	std::array<bigInt, 20> powNum;
	std::array<char, 256> buffer;
};

extern AFormat format;

ATHENA_END