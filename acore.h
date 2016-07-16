/*

Yuyue's Classes Library For Microsoft Visual C++

Copyright @2016 CDU INnoVation Studio
All rights reserved.

�ļ����ƣ�acore.h
ժҪ��
1.���ļ�����athena������һЩ�������ݵĶ��塣

��ǰ�汾��V1.0
���ߣ�����
e-mail��1397011447@qq.com
�������ڣ�2016��05��29��
�������ڣ�2016��07��11��

������־��

*/

#pragma once

#ifndef __cplusplus

#error You must use this file in C++ compiler, or you need filename with '.cpp' suffix

#endif

#pragma warning(disable:4290)
#pragma warning(disable:4996)

#define ATHENA_BEGIN namespace athena {
#define ATHENA_END }
#define MSGLEN 100

ATHENA_BEGIN

class AException
{
public:
	AException(const char *info)
	{
		int i;
		for (i = 0; i < MSGLEN; i++)
		{
			msg[i] = info[i];
			if (info[i] == 0)
			{
				break;
			}
		}
		msg[MSGLEN - 1] = 0;
	}
	virtual ~AException(){}
	virtual const char *what() const
	{
		return msg;
	}
protected:
	char msg[MSGLEN];
};

class AOutOfRange :public AException
{
public:
	AOutOfRange(const char *info) :AException(info){}
	AOutOfRange() :AException("Index Out Of Range"){}
	virtual ~AOutOfRange(){};
};

class ABadAlloc :public AException
{
public:
	ABadAlloc(const char *info) :AException(info){}
	ABadAlloc() :AException("Memory Allocation Failed"){}
	virtual ~ABadAlloc(){};
};

class AEmpty :public AException
{
public:
	AEmpty(const char *info) :AException(info){}
	AEmpty() :AException("Container Is Empty"){}
	virtual ~AEmpty(){};
};


//buffer�࣬�Ի������ķ�װ��new��delete�������û�͸��
template<class T>
class ABuffer
{
public:
	ABuffer() :ok(true)
	{
		try
		{
			origin = new T[size];
		}
		catch (std::bad_alloc &)
		{
			ok = false;
		}
	}
	ABuffer(int t) :ok(true)
	{
		try
		{
			origin = new T[t];
		}
		catch (std::bad_alloc &)
		{
			ok = false;
		}
	}
	virtual ~ABuffer()
	{
		delete[] origin;
	}
	T *data() 
	{
		return origin;
	}
	T &operator[](int index) 
	{
		return origin[index];
	}
	bool isOk() 
	{
		return ok;
	}
protected:
	static const int size = 256;
	bool ok;
	char *origin;
};

typedef ABuffer<char> cBuffer;
typedef ABuffer<int> iBuffer;

/*��κ���������*/
class arg final
{
public:
	template<class T>
	arg(T *p)
	{
		ptr = reinterpret_cast<char *>(p)+sizeof(T);
	}
	template<class T>
	void reSet(T *p)
	{
		ptr = reinterpret_cast<char *>(p)+sizeof(T);
	}
	char getCh()
	{
		int temp = *reinterpret_cast<int *>(ptr);
		ptr += sizeof(int);
		return static_cast<char>(temp);
	}
	int getInt()
	{
		int temp = *reinterpret_cast<int *>(ptr);
		ptr += sizeof(int);
		return temp;
	}
	double getFloat()
	{
		double temp = *reinterpret_cast<double *>(ptr);
		ptr += sizeof(double);
		return temp;
	}
	long long getLong()
	{
		long long temp = *reinterpret_cast<long long *>(ptr);
		ptr += sizeof(long long);
		return temp;
	}
	void * getPointer()
	{
		void * temp = *reinterpret_cast<void **>(ptr);
		ptr += sizeof(void *);
		return temp;
	}
private:
	char *ptr;
};

ATHENA_END
